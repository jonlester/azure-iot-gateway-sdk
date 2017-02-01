#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

cmake_minimum_required(VERSION 2.8.11)

compileAsC99()

set(iothub_local_c_files
./src/iothub_local.c
./src/iothub.c
)

set(iothub_local_h_files
./inc/iothub_local/iothub_local.h
./inc/iothub_local/iothub.h
)

include_directories(./inc)

add_executable(iothub_local
    ${iothub_local_c_files} 
    ${iothub_local_h_files})
