// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include "iothub_local/iothub.h"
#include "iothub_local/iothub_http.h"

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
        IOTHUB_HTTP_HANDLE iothub_http = iothub_http_create(iothub, 80);
        if (iothub_http == NULL)
        {
            (void)printf("Could not create IoTHub HTTP instance");
            result = __LINE__;
        }
        else
        {
            (void)printf("Starting HTTP head for IoTHub ...\r\n");

            if (iothub_http_start(iothub_http) != 0)
            {
                (void)printf("Could not start IoTHub");
                result = __LINE__;
            }
            else
            {
                getchar();

                (void)printf("Stopping HTTP head for IoTHub ...\r\n");

                (void)iothub_http_stop(iothub_http);

                result = 0;
            }
        }

        iothub_destroy(iothub);
    }

    (void)argc;
    (void)argv;

    return result;
}
