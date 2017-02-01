// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include "iothub_local/iothub.h"

int main(int argc, void** argv)
{
    int result;
    IOTHUB_HANDLE iothub = iothub_create("dcristoiothub");

    if (iothub == NULL)
    {
        (void)printf("Could not create IoTHub instance");
        result = __LINE__;
    }
    else
    {
        if (iothub_start(iothub) != 0)
        {
            (void)printf("Could not start IoTHub");
            result = __LINE__;
        }
        else
        {
            getchar();

            (void)iothub_stop(iothub);

            iothub_destroy(iothub);
            result = 0;
        }
    }

    (void)argc;
    (void)argv;

    return result;
}
