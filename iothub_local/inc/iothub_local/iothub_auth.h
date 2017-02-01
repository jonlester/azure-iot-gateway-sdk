// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_AUTH_H
#define IOTHUB_AUTH_H

#ifdef __cplusplus
#include <cstdbool>
extern "C" {
#else
#include <stdbool.h>
#endif

#include "iothub_local/iothub_device_registry.h"

typedef struct IOTHUB_AUTH_INSTANCE_TAG* IOTHUB_AUTH_HANDLE;

extern IOTHUB_AUTH_HANDLE iothub_auth_create(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry);
extern bool iothub_auth_authenticate(IOTHUB_AUTH_HANDLE iothub_auth, const char* device_id, const char* key);
extern void iothub_destroy(IOTHUB_AUTH_HANDLE iothub_auth);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_AUTH_H */
