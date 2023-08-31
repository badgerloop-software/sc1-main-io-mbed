cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

set(MBED_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mbed-os CACHE INTERNAL "")
set(MBED_CONFIG_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL "")
set(APP_TARGET sc1-main-io-mbed)
set(DRV_INCLUDE_DIR embedded/drivers/include)
set(DRV_SRC_DIR embedded/drivers/src)
set(DEV_INCLUDE_DIR embedded/devices/include)
set(DEV_SRC_DIR embedded/devices/src)
set(HEADER_FILES
    ${DRV_INCLUDE_DIR}/uart.h
    ${DRV_INCLUDE_DIR}/i2cdevice.h
    ${DRV_INCLUDE_DIR}/can.h
    ${DEV_INCLUDE_DIR}/tca6416.h
    ${DEV_INCLUDE_DIR}/mppt.h
    ${DEV_INCLUDE_DIR}/mcc.h
    ${DEV_INCLUDE_DIR}/ina219.h
    ${DEV_INCLUDE_DIR}/bms.h
    applications/uartApp.h
)
set(SRC_FILES
    ${DRV_SRC_DIR}/uart.cpp
    ${DRV_SRC_DIR}/i2cdevice.cpp
    ${DRV_SRC_DIR}/can.cpp
    ${DEV_SRC_DIR}/tca6416.cpp
    ${DEV_SRC_DIR}/mppt.cpp
    ${DEV_SRC_DIR}/mcc.cpp
    ${DEV_SRC_DIR}/ina219.cpp
    ${DEV_SRC_DIR}/bms.cpp
    applications/uartApp.cpp
)

# Example of defining binary preprocessor
OPTION(DEF_BLINK_RATE_250 "Blinking rate optionally specified on command line" OFF)
IF(DEF_BLINK_RATE_250)
    ADD_DEFINITIONS(-DBLINK_RATE_250)
ENDIF(DEF_BLINK_RATE_250)

# Example of specifying/defining variable preprocessor
IF(BLINK_RATE)
    ADD_DEFINITIONS(-DBLINK_RATE=${BLINK_RATE}ms)
ENDIF(BLINK_RATE)

include(${MBED_PATH}/tools/cmake/app.cmake)

project(${APP_TARGET})

add_subdirectory(${MBED_PATH})

add_executable(${APP_TARGET} main.cpp) # ${SRC_FILES} ${HEADER_FILES})

#target_include_directories(${APP_TARGET} PRIVATE
#    ${DRV_INCLUDE_DIR} ${DRV_SRC_DIR}
#    ${DEV_INCLUDE_DIR} ${DEV_SRC_DIR}
#    applications
#)

target_sources(${APP_TARGET}
    PRIVATE
        main.cpp
)

target_link_libraries(${APP_TARGET}
    PRIVATE
        mbed-os
)

mbed_set_post_build(${APP_TARGET})

option(VERBOSE_BUILD "Have a verbose build process")
if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

