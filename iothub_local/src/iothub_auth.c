// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "iothub_local/iothub_auth.h"
#include "iothub_local/iothub_device_registry.h"
#include "azure_c_shared_utility/xlogging.h"

typedef struct IOTHUB_AUTH_INSTANCE_TAG
{
    IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry;
} IOTHUB_AUTH_INSTANCE;

IOTHUB_AUTH_HANDLE iothub_auth_create(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry)
{
    IOTHUB_AUTH_INSTANCE* result = (IOTHUB_AUTH_INSTANCE*)malloc(sizeof(IOTHUB_AUTH_INSTANCE));
    if (result == NULL)
    {
        LogError("Could not allocate memory for iothub authentication instance");
    }
    else
    {
        result->iothub_device_registry = iothub_device_registry;
    }

    return (IOTHUB_AUTH_HANDLE)result;
}

void iothub_auth_destroy(IOTHUB_AUTH_HANDLE iothub_auth)
{
    if (iothub_auth == NULL)
    {
        LogError("NULL IoTHub auth handle");
    }
    else
    {
        free(iothub_auth);
    }
}
