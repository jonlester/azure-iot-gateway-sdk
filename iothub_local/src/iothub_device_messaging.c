// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "iothub_local/iothub_device_messaging.h"
#include "azure_c_shared_utility/xlogging.h"

typedef struct IOTHUB_DEVICE_MESSAGING_INSTANCE_TAG
{
    int dummy;
} IOTHUB_DEVICE_MESSAGING_INSTANCE;

IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging_create(const char* device_id)
{
    IOTHUB_DEVICE_MESSAGING_HANDLE result = (IOTHUB_DEVICE_MESSAGING_HANDLE)malloc(sizeof(IOTHUB_DEVICE_MESSAGING_INSTANCE));

    (void)device_id;

    if (result == NULL)
    {
        LogError("Could not initialize device messaging interface");
    }

    return result;
}

void iothub_device_messaging_destroy(IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging)
{
    if (iothub_device_messaging == NULL)
    {
        LogError("NULL iothub_device_messaging");
    }
    else
    {
        free(iothub_device_messaging);
    }
}

int iothub_device_messaging_send_message_async(IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging, IOTHUB_MESSAGE_HANDLE iothub_message, IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_CALLBACK send_message_callback, void* send_message_callback_context)
{

}
