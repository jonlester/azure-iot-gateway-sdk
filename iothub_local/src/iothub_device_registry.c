// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "iothub_local/iothub_device_registry.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/xio.h"

typedef struct IOTHUB_DEVICE_REGISTRY_INSTANCE_TAG
{
    XIO_HANDLE http_listener;
} IOTHUB_DEVICE_REGISTRY_INSTANCE;

IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry_create(int port)
{
    IOTHUB_DEVICE_REGISTRY_INSTANCE* result = (IOTHUB_DEVICE_REGISTRY_INSTANCE*)malloc(sizeof(IOTHUB_DEVICE_REGISTRY_INSTANCE));

    (void)port;

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
