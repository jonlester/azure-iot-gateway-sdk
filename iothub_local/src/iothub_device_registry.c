// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <stdbool.h>
#include "iothub_local/iothub_device_registry.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/singlylinkedlist.h"
#include "azure_c_shared_utility/crt_abstractions.h"

typedef struct DEVICE_INSTANCE_TAG
{
    char* device_id;
    char* primary_key;
    char* secondary_key;
} DEVICE_INSTANCE;

typedef struct IOTHUB_DEVICE_REGISTRY_INSTANCE_TAG
{
    SINGLYLINKEDLIST_HANDLE device_list;
} IOTHUB_DEVICE_REGISTRY_INSTANCE;

IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry_create(void)
{
    IOTHUB_DEVICE_REGISTRY_INSTANCE* result = (IOTHUB_DEVICE_REGISTRY_INSTANCE*)malloc(sizeof(IOTHUB_DEVICE_REGISTRY_INSTANCE));

    if (result == NULL)
    {
        LogError("Could not allocate memory for iothub device registry instance");
    }
    else
    {
        result->device_list = singlylinkedlist_create();
        if (result->device_list == NULL)
        {
            LogError("Could not create device list");
            free(result);
            result = NULL;
        }
    }

    return (IOTHUB_DEVICE_REGISTRY_HANDLE)result;
}

void iothub_device_registry_destroy(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry)
{
    if (iothub_device_registry == NULL)
    {
        LogError("NULL IoTHub device registry handle");
    }
    else
    {
        singlylinkedlist_destroy(iothub_device_registry->device_list);
        free(iothub_device_registry);
    }
}

int iothub_device_registry_add_device(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const char* device_id, const char* primary_key, const char* secondary_key)
{
    int result;

    if ((iothub_device_registry == NULL) ||
        (device_id == NULL) ||
        (primary_key == NULL) ||
        (secondary_key == NULL))
    {
        LogError("Bad arguments: iothub_device_registry = %p, device_id = %p, primary_key = %p, secondary_key = %p",
            iothub_device_registry, device_id, primary_key, secondary_key);
        result = __LINE__;
    }
    else
    {
        DEVICE_INSTANCE* device = (DEVICE_INSTANCE*)malloc(sizeof(DEVICE_INSTANCE));
        if (device == NULL)
        {
            LogError("Cannot allocate memory for new device");
            result = __LINE__;
        }
        else
        {
            if (mallocAndStrcpy_s(&device->device_id, device_id) != 0)
            {
                LogError("Failed copying device_id");
                free(device);
                result = __LINE__;
            }
            else if (mallocAndStrcpy_s(&device->primary_key, primary_key) != 0)
            {
                LogError("Failed copying primary_key");
                free(device->device_id);
                free(device);
                result = __LINE__;
            }
            else if (mallocAndStrcpy_s(&device->secondary_key, secondary_key) != 0)
            {
                LogError("Failed copying secondary_key");
                free(device->primary_key);
                free(device->device_id);
                free(device);
                result = __LINE__;
            }
            else if (singlylinkedlist_add(iothub_device_registry->device_list, device) != 0)
            {
                LogError("Failed adding device to device list");
                free(device->secondary_key);
                free(device->primary_key);
                free(device->device_id);
                free(device);
                result = __LINE__;
            }
            else
            {
                result = 0;
            }
        }
    }

    return result;
}

static bool find_device_by_id(LIST_ITEM_HANDLE list_item, const void* match_context)
{
    bool result;
    DEVICE_INSTANCE* device = (DEVICE_INSTANCE*)singlylinkedlist_item_get_value(list_item);
    const char* device_id = (const char*)match_context;

    if (strcmp(device->device_id, device_id) == 0)
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return result;
}

int iothub_device_registry_find_device_by_id(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const char* device_id, DEVICE_DATA* device_data)
{
    int result;

    if ((iothub_device_registry == NULL) ||
        (device_id == NULL) ||
        (device_data == NULL))
    {
        LogError("Bad arguments: iothub_device_registry = %p, device_id = %p, device_data = %p",
            iothub_device_registry, device_id, device_data);
        result = __LINE__;
    }
    else
    {
        LIST_ITEM_HANDLE search_result = singlylinkedlist_find(iothub_device_registry->device_list, find_device_by_id, device_id);
        if (search_result == NULL)
        {
            LogError("Cannot find device %s",
                device_id);
            result = __LINE__;
        }
        else
        {
            DEVICE_INSTANCE* device = (DEVICE_INSTANCE*)singlylinkedlist_item_get_value(search_result);
            device_data->device_id = device->device_id;
            device_data->primary_key = device->primary_key;
            device_data->secondary_key = device->secondary_key;

            result = 0;
        }
    }

    return result;
}

int iothub_device_registry_subscribe_changes(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, IOTHUB_DEVICE_REGISTRY_STATE_CHANGE_CALLBACK state_changed_callback, void* state_changed_callback_context)
{
    return 0;
}

int iothub_device_registry_process_change(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const unsigned char* change_payload, size_t change_payload_size)
{
    return 0;
}
