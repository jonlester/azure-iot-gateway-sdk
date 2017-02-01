// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUB_H
#define IOTHUB_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IOTHUB_INSTANCE_TAG* IOTHUB_HANDLE;

extern IOTHUB_HANDLE iothub_create(const char* iothub_name);
extern int iothub_start(IOTHUB_HANDLE iothub);
extern int iothub_stop(IOTHUB_HANDLE iothub);
extern void iothub_destroy(IOTHUB_HANDLE iothub);

#ifdef __cplusplus
}
#endif

#endif /* IOTHUB_H */
