// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "iothub_local/iothub_local.h"
#include "iothub_local/iothub.h"

int main(int argc, void** argv)
{
    IOTHUB_HANDLE iothub = iothub_create("dcristoiothub");
    int result;

    if (iothub_start(iothub) != 0)
    {
        result = __LINE__;
    }
    else
    {
        iothub_destroy(iothub);
        result = 0;
    }

    (void)argc;
    (void)argv;

    return result;
}
