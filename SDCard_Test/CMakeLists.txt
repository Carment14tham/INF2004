add_executable(SDCard_Test
    SDCard_Test.c
        )

# Tell CMake where to find other source code
#add_subdirectory(no-OS-FatFS-SD-SPI-RPi-Pico-master)
#add_subdirectory(mbedtls-development)

# pull in common dependencies
target_link_libraries(SDCard_Test pico_stdlib 
                    pico_cyw43_arch_none 
                    FatFs_SPI
                    mnedtls-development/library/md5.c)

target_include_directories(SDCard_Test PRIVATE "C:/Users/Marie/Documents/Pico-v1.5.1/pico-examples/mbedtls-development/include/" mbedtls/md5.h)

#target_link_libraries(SDCard_Test PRIVATE mbedtls-development/library/md5.c)

# enable usb output, disable uart output
pico_enable_stdio_usb(SDCard_Test 1)
pico_enable_stdio_uart(SDCard_Test 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(SDCard_Test)

# add url via pico_set_program_url
example_auto_set_url(SDCard_Test)
