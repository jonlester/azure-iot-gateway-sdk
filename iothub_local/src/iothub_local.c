// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>
#include "iothub_local/iothub.h"
#include "iothub_local/iothub_http.h"
#include "iothub_local/iothub_device_registry.h"
#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/threadapi.h"

int main(int argc, void** argv)
{
    int result;

    if (platform_init() != 0)
    {
        (void)printf("POlatform init failed");
        result = __LINE__;
    }
    else
    {
        IOTHUB_DEVICE_REGISTRY_HANDLE iothub_device_registry = iothub_device_registry_create();
        if (iothub_device_registry == NULL)
        {
            (void)printf("Could not create IoTHub device registry instance");
            result = __LINE__;
        }
        else
        {
            IOTHUB_HANDLE iothub = iothub_create(iothub_device_registry, "dcristoiothub");
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
                        while (1)
                        {
                            iothub_http_dowork(iothub_http);
                            ThreadAPI_Sleep(0);
                        }

                        (void)printf("Stopping HTTP head for IoTHub ...\r\n");

                        (void)iothub_http_stop(iothub_http);

                        result = 0;
                    }
                }

                iothub_destroy(iothub);
            }

            iothub_device_registry_destroy(iothub_device_registry);
        }

        platform_deinit();
    }

    (void)argc;
    (void)argv;

    return result;
}
