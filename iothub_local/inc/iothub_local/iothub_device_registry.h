// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_HTTP_H
#define IOTHUB_HTTP_H

#include "iothub_local/iothub_device_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOTHUB_DEVICE_REGISTRY_INSTANCE_TAG* IOTHUB_DEVICE_REGISTRY_HANDLE;

extern IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry_create(void);
extern void iothub_device_registry_destroy(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_http);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_HTTP_H */
