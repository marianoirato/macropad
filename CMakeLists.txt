cmake_minimum_required(VERSION 3.13)

set(PROGRAM_NAME macropad)

include(pico_sdk_import.cmake)

project(${PROGRAM_NAME})

pico_sdk_init()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/main.c
        ${CMAKE_CURRENT_LIST_DIR}/keyboard/keyboard.c
        ${CMAKE_CURRENT_LIST_DIR}/usb/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/oled/oled.c
        ${CMAKE_CURRENT_LIST_DIR}/oled/ssd1306.c
        )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/oled
        ${CMAKE_CURRENT_LIST_DIR}/usb
        ${CMAKE_CURRENT_LIST_DIR}/keyboard
        )

# In addition to pico_stdlib required for common PicoSDK functionality, add dependency on tinyusb_device
# for TinyUSB device support and tinyusb_board for the additional board support library used by the example
target_link_libraries(${PROJECT_NAME} PUBLIC 
        pico_stdlib 
        tinyusb_device 
        tinyusb_board 
        hardware_i2c
        )

# Uncomment this line to enable fix for Errata RP2040-E5 (the fix requires use of GPIO 15)
#target_compile_definitions(dev_hid_composite PUBLIC PICO_RP2040_USB_DEVICE_ENUMERATION_FIX=1)

pico_add_extra_outputs(${PROJECT_NAME})

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)