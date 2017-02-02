// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SYNCRONIZER_H
#define SYNCRONIZER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SYNCRONIZER_INSTANCE_TAG* SYNCRONIZER_HANDLE;

extern SYNCRONIZER_HANDLE syncronizer_create(void);
extern void syncronizer_destroy(SYNCRONIZER_HANDLE iothub);

#ifdef __cplusplus
}
#endif

#endif /* SYNCRONIZER_H */
