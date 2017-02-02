// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <stdbool.h>
#include "iothub_local/iothub_device_registry.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/singlylinkedlist.h"

typedef struct DEVICE_INSTANCE_TAG
{
    const char* device_id;
    const char* primary_key;
    const char* secondary_key;
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

int iothub_device_registry_add_device(const char* device_id, const char* primary_key, const char* secondary_key)
{
    return 0;
}

int iothub_device_registry_subscribe_changes(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, IOTHUB_DEVICE_REGISTRY_STATE_CHANGE_CALLBACK state_changed_callback, void* state_changed_callback_context)
{
    return 0;
}

int iothub_device_registry_process_change(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const unsigned char* change_payload, size_t change_payload_size)
{
    return 0;
}
