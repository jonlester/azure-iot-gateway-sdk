// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include <string.h>
#include "iothub_local/iothub_http.h"
#include "iothub_local/iothub.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/xio.h"
#include "azure_uamqp_c/socket_listener.h"

typedef struct IOTHUB_HTTP_INSTANCE_TAG
{
    IOTHUB_HANDLE iothub;
    SOCKET_LISTENER_HANDLE socket_listener;
    XIO_HANDLE socket_io;
    unsigned char* received_bytes;
    size_t received_bytes_count;
} IOTHUB_HTTP_INSTANCE;

IOTHUB_HTTP_HANDLE iothub_http_create(IOTHUB_HANDLE iothub, int port)
{
    IOTHUB_HTTP_INSTANCE* result = (IOTHUB_HTTP_INSTANCE*)malloc(sizeof(IOTHUB_HTTP_INSTANCE));
    if (result == NULL)
    {
        LogError("Could not allocate memory for iothub HTTP instance");
    }
    else
    {
        result->received_bytes = NULL;
        result->received_bytes_count = 0;
        result->iothub = iothub;
        result->socket_io = NULL;
        result->socket_listener = socketlistener_create(port);
        if (result->socket_listener == NULL)
        {
            LogError("Could not create socket listener");
            free(result);
            result = NULL;
        }
    }

    return (IOTHUB_HTTP_HANDLE)result;
}

void iothub_http_destroy(IOTHUB_HTTP_HANDLE iothub_http)
{
    if (iothub_http == NULL)
    {
        LogError("NULL IoTHub HTTP handle");
    }
    else
    {
        if (iothub_http->socket_io != NULL)
        {
            xio_destroy(iothub_http->socket_io);
        }
        socketlistener_destroy(iothub_http->socket_listener);
        free(iothub_http->received_bytes);
        free(iothub_http);
    }
}

static void on_socket_io_open_complete(void* context, IO_OPEN_RESULT open_result)
{
}

static void on_socket_io_error(void* context)
{
}

static void consume_bytes(IOTHUB_HTTP_HANDLE iothub_http, size_t bytes)
{
    if (bytes > iothub_http->received_bytes_count)
    {
        (void)memmove(iothub_http->received_bytes, iothub_http->received_bytes + bytes, (iothub_http->received_bytes_count - bytes));
    }
    else
    {
        free(iothub_http->received_bytes);
        iothub_http->received_bytes = NULL;
    }

    iothub_http->received_bytes_count -= bytes;
}

static void on_socket_bytes_received(void* context, const unsigned char* buffer, size_t size)
{
    IOTHUB_HTTP_HANDLE iothub_http = (IOTHUB_HTTP_HANDLE)context;
    unsigned char* new_received_bytes = (unsigned char*)realloc(iothub_http->received_bytes, iothub_http->received_bytes_count + size + 1);
    if (new_received_bytes == NULL)
    {
        LogError("Cannot allocate memory for received bytes");
    }
    else
    {
        const char* end_request;

        iothub_http->received_bytes = new_received_bytes;
        (void)memcpy(iothub_http->received_bytes + iothub_http->received_bytes_count, buffer, size);
        iothub_http->received_bytes_count += size;

        iothub_http->received_bytes[iothub_http->received_bytes_count] = '\0';

        end_request = strstr(iothub_http->received_bytes, "\r\n\r\n");
        if (end_request != NULL)
        {
            char device_id[128];

            /* got one request */
            if (sscanf(iothub_http->received_bytes, "POST /devices/%[^/]messages/events?api-version=2016-11-14 HTTP/1.1",
                device_id) != 1)
            {
                LogError("Error getting device id");
            }
            else
            {
                IOTHUB_DEVICE_MESSAGING_HANDLE iothub_device_messaging = iothub_get_device_messaging_interface(iothub_http->iothub, device_id, "");
                if (iothub_device_messaging == NULL)
                {
                    LogError("Could not obtain device messaging interface for device %s", device_id);
                }
                else
                {
                    IOTHUB_MESSAGE_HANDLE iothub_message = IoTHubMessage_CreateFromString("");
                    if (iothub_message == NULL)
                    {
                        LogError("Could not create message for device %s", device_id);
                    }
                    else
                    {
                        if (iothub_device_messaging_send_message_async(iothub_device_messaging, iothub_message, NULL, NULL) != 0)
                        {
                            LogError("Could not send message async for device %s", device_id);
                        }
                        else
                        {
                            LogInfo("D2C message - device_id = %s", device_id);
                        }
                    }

                    iothub_device_messaging_destroy(iothub_device_messaging);
                }
            }

            consume_bytes(iothub_http, end_request + 4 - iothub_http->received_bytes);
        }
    }
}

static void on_socket_accepted(void* context, XIO_HANDLE socket_io)
{
    IOTHUB_HTTP_HANDLE iothub_http = (IOTHUB_HTTP_HANDLE)context;

    iothub_http->socket_io = socket_io;
    if (xio_open(iothub_http->socket_io, on_socket_io_open_complete, iothub_http, on_socket_bytes_received, iothub_http, on_socket_io_error, iothub_http) != 0)
    {
        LogError("Cannot open accepted socket");
    }
}

int iothub_http_start(IOTHUB_HTTP_HANDLE iothub_http)
{
    int result;

    if (iothub_http == NULL)
    {
        LogError("NULL IoTHub HTTP handle");
        result = __LINE__;
    }
    else
    {
        if (socketlistener_start(iothub_http->socket_listener, on_socket_accepted, iothub_http) != 0)
        {
            LogError("Cannot start socket listener");
            result = __LINE__;
        }
        else
        {
            result = 0;
        }
    }

    return result;
}

int iothub_http_stop(IOTHUB_HTTP_HANDLE iothub_http)
{
    int result;

    if (iothub_http == NULL)
    {
        LogError("NULL IoTHub HTTP handle");
        result = __LINE__;
    }
    else
    {
        if (socketlistener_stop(iothub_http->socket_listener) != 0)
        {
            LogError("Could not stop socket listener");
            result = __LINE__;
        }
        else
        {
            result = 0;
        }
    }

    return result;
}

void iothub_http_dowork(IOTHUB_HTTP_HANDLE iothub_http)
{
    if (iothub_http == NULL)
    {
        LogError("NULL IoTHub HTTP handle");
    }
    else
    {
        socketlistener_dowork(iothub_http->socket_listener);
        if (iothub_http->socket_io != NULL)
        {
            xio_dowork(iothub_http->socket_io);
        }
    }
}
