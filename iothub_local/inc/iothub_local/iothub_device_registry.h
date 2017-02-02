// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_DEVICE_REGISTRY_H
#define IOTHUB_DEVICE_REGISTRY_H

#include "iothub_local/iothub_device_registry.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOTHUB_DEVICE_REGISTRY_INSTANCE_TAG* IOTHUB_DEVICE_REGISTRY_HANDLE;
typedef void (*IOTHUB_DEVICE_REGISTRY_STATE_CHANGE_CALLBACK)(void* context, const unsigned char* state_change_payload, size_t state_change_payload_size);

typedef struct DEVICE_DATA_TAG
{
    const char* device_id;
    const char* primary_key;
    const char* secondary_key;
} DEVICE_DATA;

extern IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry_create(void);
extern void iothub_device_registry_destroy(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_http);
extern int iothub_device_registry_add_device(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const char* device_id, const char* primary_key, const char* secondary_key);
extern int iothub_device_registry_find_device_by_id(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const char* device_id, DEVICE_DATA* device_data);
extern int iothub_device_registry_subscribe_changes(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, IOTHUB_DEVICE_REGISTRY_STATE_CHANGE_CALLBACK state_changed_callback, void* state_changed_callback_context);
extern int iothub_device_registry_process_change(IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry, const unsigned char* change_payload, size_t change_payload_size);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_DEVICE_REGISTRY_H */
