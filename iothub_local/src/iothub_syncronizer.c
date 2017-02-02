// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "iothub_local/iothub.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/crt_abstractions.h"

typedef struct IOTHUB_INSTANCE_TAG
{
    char* iothub_name;
} IOTHUB_INSTANCE;

SYNCRONIZER_HANDLE syncronizer_create(void)
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

int iothub_start(IOTHUB_HANDLE iothub)
{
    int result;

    if (iothub == NULL)
    {
        LogError("NULL IoTHub handle");
        result = __LINE__;
    }
    else
    {
        LogInfo("Starting IoTHub %s ...", iothub->iothub_name);
        result = 0;
    }

    return result;
}

int iothub_stop(IOTHUB_HANDLE iothub)
{
    int result;

    if (iothub == NULL)
    {
        LogError("NULL IoTHub handle");
        result = __LINE__;
    }
    else
    {
        LogInfo("Stopping IoTHub %s ...", iothub->iothub_name);
        result = 0;
    }

    return result;
}