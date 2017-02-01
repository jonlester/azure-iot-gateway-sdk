// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_DEVICE_MESSAGING_H
#define IOTHUB_DEVICE_MESSAGING_H

#include "iothub_local/iothub_message.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOTHUB_DEVICE_MESSAGING_INSTANCE_TAG* IOTHUB_DEVICE_MESSAGING_HANDLE;

typedef enum IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_RESULT_TAG
{
    IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_RESULT_OK,
    IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_RESULT_ERROR
} IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_RESULT;

typedef void(*IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_CALLBACK)(void* context, IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_RESULT send_message_result, const char* error_string);

extern IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging_create(void);
extern void iothub_device_messaging_destroy(IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging);
extern int iothub_device_messaging_send_message_async(IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging, IOTHUB_MESSAGE_HANDLE iothub_message, IOTHUB_DEVICE_MESSAGING_SEND_MESSAGE_CALLBACK send_message_callback, void* send_message_callback_context);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_DEVICE_MESSAGING_H */
