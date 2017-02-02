// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#include "iothub_local/iothub_http.h"
#include "iothub_local/iothub.h"
#include "azure_c_shared_utility/xlogging.h"
#include "azure_c_shared_utility/xio.h"
#include "azure_uamqp_c/socket_listener.h"

typedef struct IOTHUB_HTTP_INSTANCE_TAG
{
    SOCKET_LISTENER_HANDLE socket_listener;
    XIO_HANDLE socket_io;
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
        socketlistener_destroy(iothub_http->socket_listener);
        free(iothub_http);
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