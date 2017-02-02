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
    bool is_connected;
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
        LogError("Bad arguments: device_id = %p, primary_key = %p, secondary_key = %p",
            device_id, primary_key, secondary_key);
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

int iothub_device_registry_find_device_by_id(const char* device_id, DEVICE_DATA* device_data)
{
    int result;

    if ((device_id == NULL) ||
        (device_data == NULL))
    {
        LogError("Bad arguments: device_id = %p, device_data = %p",
            device_id, device_data);
        result = __LINE__;
    }
    else
    {
        result = 0;
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
