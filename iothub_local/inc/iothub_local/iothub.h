// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_H
#define IOTHUB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOTHUB_INSTANCE_TAG* IOTHUB_HANDLE;

#include "iothub_local/iothub_device_messaging.h"
#include "iothub_local/iothub_device_registry.h"

extern IOTHUB_HANDLE iothub_create(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const char* iothub_name);
extern IOTHUB_DEVICE_MESSAGING_HANDLE iothub_get_device_messaging_interface(IOTHUB_HANDLE iothub, const char* device_id, const char* sas_token);
extern int iothub_stop(IOTHUB_HANDLE iothub);
extern void iothub_destroy(IOTHUB_HANDLE iothub);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_H */
