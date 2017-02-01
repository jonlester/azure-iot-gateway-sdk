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

IOTHUB_HANDLE iothub_create(const char* iothub_name)
{
    IOTHUB_INSTANCE* result = (IOTHUB_INSTANCE*)malloc(sizeof(IOTHUB_INSTANCE));
    if (result == NULL)
    {
        LogError("Could not allocate memory for iothub instance");
    }
    else
    {
        if (malloc)
        result->iothub_name = (char*)mallocAndS
    }

    return result;
}

void iothub_destroy(IOTHUB_HANDLE iothub)
{

}

int iothub_start(IOTHUB_HANDLE iothub)
{
    return 0;
}
