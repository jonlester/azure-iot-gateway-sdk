// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "iothub_local/iothub.h"
#include "iothub_local/iothub_auth.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/crt_abstractions.h"

typedef struct IOTHUB_INSTANCE_TAG
{
    IOTHUB_AUTH_HANDLE iothub_auth;
    char* iothub_name;
} IOTHUB_INSTANCE;

IOTHUB_HANDLE iothub_create(const char* iothub_name)
{
    IOTHUB_INSTANCE* result = (IOTHUB_INSTANCE*)malloc(sizeof(IOTHUB_INSTANCE));
    if (result == NULL)
    {
        LogError("Could not allocate memory for iothub instance");
    }
    else
    {
        if (mallocAndStrcpy_s(&result->iothub_name, iothub_name) != 0)
        {
            LogError("Cannot allocate memory for the IoTHub name");
            free(result);
            result = NULL;
        }
    }

    return (IOTHUB_HANDLE)result;
}

void iothub_destroy(IOTHUB_HANDLE iothub)
{
    if (iothub == NULL)
    {
        LogError("NULL IoTHub handle");
    }
    else
    {
        free(iothub->iothub_name);
        free(iothub);
    }
}

IOTHUB_DEVICE_MESSAGING_HANDLE iothub_get_device_messaging_interface(IOTHUB_HANDLE iothub, const char* device_id, const char* sas_token)
{
    IOTHUB_DEVICE_MESSAGING_HANDLE result;

    if (iothub == NULL)
    {
        LogError("NULL IoTHub handle");
        result = NULL;
    }
    else
    {
        if (iothub_auth_authenticate_device(iothub->iothub_auth, device_id, sas_token))
        {
            LogError("Could not authenticate device %s", device_id);
            result = NULL;
        }
        else
        {
            result = iothub_device_messaging_create(device_id);
            if (result == NULL)
            {
                LogError("Could not get device messaging interface for device %s", device_id);
                result = NULL;
            }
        }
    }

    return result;
}
