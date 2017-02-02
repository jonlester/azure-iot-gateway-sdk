// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_HTTP_H
#define IOTHUB_HTTP_H

#include "iothub_local/iothub.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOTHUB_HTTP_INSTANCE_TAG* IOTHUB_HTTP_HANDLE;

extern IOTHUB_HTTP_HANDLE iothub_http_create(IOTHUB_HANDLE iothub, int port);
extern int iothub_http_start(IOTHUB_HTTP_HANDLE iothub_http);
extern int iothub_http_stop(IOTHUB_HTTP_HANDLE iothub_http);
extern void iothub_http_destroy(IOTHUB_HTTP_HANDLE iothub_http);
extern void iothub_http_dowork(IOTHUB_HTTP_HANDLE iothub_http);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_HTTP_H */
