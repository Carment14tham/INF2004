#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hw_config.h"
#include "sd_card.h"
#include "ff.h"
#include "diskio.h"
#include "mbedtls/md5.h"

//Function for MD5 Checksum print
void print_md5_sum(const unsigned char *digest) {
    for (int i = 0; i < 16; i++) {
        printf("%02x", (unsigned int)digest[i]);
    }
    printf("\n");
}

int main() {

    FRESULT fr;
    //FATFS fs;
    FIL fil;
    UINT ret;
    char buf[100];
    BYTE byteArr[1000];
    char filename[] = "test02.txt";

    // Initialize chosen serial port
    stdio_init_all();
    
    // sleep_ms(10000);
    // Wait for user to press 'enter' to continue
    printf("\r\nSD card test. Enter 'A' or 'B' to console to start.\r\n");
    while (true) {
        buf[0] = getchar();
        if ((buf[0] == 'A') || (buf[0] == 'B')) {
            break;
        }
    }

     // Initialize SD card
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        while (true);
    }
    /* START MD5 PORTION*/
    // Open the file for reading
    fr = f_open(&fil, filename, FA_READ);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file for reading(%d)\r\n", fr);
        while (true);
    }

    // Read the contents of the file into a buffer
    char file_contents[1000];
    memset(file_contents, 0, sizeof(file_contents));
    f_read(&fil, file_contents, sizeof(file_contents), &ret);

    // Close the file
    fr = f_close(&fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        while (true);
    }

    // Calculate the MD5 checksum
    mbedtls_md5_context ctx;
    unsigned char md5sum[16];
    mbedtls_md5_init(&ctx);
    mbedtls_md5_starts(&ctx);
    mbedtls_md5_update(&ctx, (unsigned char *)file_contents, strlen(file_contents));
    mbedtls_md5_finish(&ctx, md5sum);
    mbedtls_md5_free(&ctx);

    // Print the MD5 checksum
    printf("MD5 Checksum: ");
    print_md5_sum(md5sum);

    /* End of MD5 PORTION */

    // Mount drive
    // fr = f_mount(&fs, "0:", 0);
    // if (fr != FR_OK) {
    //     printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
    //     while (true);
    // }

    // // Open file for writing ()
    // fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    // if (fr != FR_OK) {
    //     printf("ERROR: Could not open file for writing (%d)\r\n", fr);
    //     while (true);
    // }

    // // Write something to file
    // ret = f_printf(&fil, "This is another test\r\n");
    // if (ret < 0) {
    //     printf("ERROR: Could not write to file (%d)\r\n", ret);
    //     f_close(&fil);
    //     while (true);
    // }
    // ret = f_printf(&fil, "of writing to an SD card.\r\n");
    // if (ret < 0) {
    //     printf("ERROR: Could not write to file (%d)\r\n", ret);
    //     f_close(&fil);
    //     while (true);
    // }

    // // Close file
    // fr = f_close(&fil);
    // if (fr != FR_OK) {
    //     printf("ERROR: Could not close file (%d)\r\n", fr);
    //     while (true);
    // }

    // // Open file for reading
    // fr = f_open(&fil, filename, FA_READ);
    // if (fr != FR_OK) {
    //     printf("ERROR: Could not open file for reading(%d)\r\n", fr);
    //     while (true);
    // }


    // // Print every line in file over serial
    // printf("Reading from file '%s':\r\n", filename);
    // printf("---\r\n");
    // while (f_gets(buf, sizeof(buf), &fil)) {
    //     printf(buf);
    // }
    // printf("\r\n---\r\n");

    // // Close file
    // fr = f_close(&fil);
    // if (fr != FR_OK) {
    //     printf("ERROR: Could not close file (%d)\r\n", fr);
    //     while (true);
    // }

    // Unmount drive
    // f_unmount("0:");

    //int64_t test = 0;
    //DSTATUS ds = disk_initialize(0);
    DRESULT ds1 = disk_read(0, byteArr, 62333951, 1);
    printf("%d\n", ds1);

    // Loop forever doing nothing
    while (true) {
        printf("Hello SD Card\n");
        sleep_ms(1000);
    }
}