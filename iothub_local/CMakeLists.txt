#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)

compileAsC99()

set(iothub_local_c_files
./src/iothub_local.c
./src/iothub.c
./src/iothub_auth.c
./src/iothub_http.c
./src/iothub_device_messaging.c
./src/iothub_device_registry.c
./src/iothub_message.c
../deps/uamqp/src/socket_listener_win32.c
../deps/uamqp/src/amqpalloc.c
)

set(iothub_local_h_files
./inc/iothub_local/iothub.h
./inc/iothub_local/iothub_auth.h
./inc/iothub_local/iothub_http.h
./inc/iothub_local/iothub_device_messaging.h
./inc/iothub_local/iothub_device_registry.h
./inc/iothub_local/iothub_message.h
)

include_directories(./inc)
include_directories(../deps/c-utility/inc)
include_directories(../deps/uamqp/inc)

add_executable(iothub_local
    ${iothub_local_c_files} 
    ${iothub_local_h_files})

linkSharedUtil(iothub_local)

copy_gateway_dll(iothub_local ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
