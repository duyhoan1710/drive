#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define DRIVER_FILE_NAME "/dev/des_encrypt"


int hextostring(char *in, int len, char *out)
{
    int i;

    memset(out, 0, sizeof(out));
    for (i = 0; i < len; i++)
    {
        sprintf(out, "%s%02hhx", out, in[i]);
    }
    return 0;
}

int stringtohex(char *in, int len, char *out)
{
    int i;
    int converter[105];
    converter['0'] = 0;
    converter['1'] = 1;
    converter['2'] = 2;
    converter['3'] = 3;
    converter['4'] = 4;
    converter['5'] = 5;
    converter['6'] = 6;
    converter['7'] = 7;
    converter['8'] = 8;
    converter['9'] = 9;
    converter['a'] = 10;
    converter['b'] = 11;
    converter['c'] = 12;
    converter['d'] = 13;
    converter['e'] = 14;
    converter['f'] = 15;

    memset(out, 0, sizeof(out));

    for (i = 0; i < len; i = i + 2)
    {
        char byte = converter[in[i]] << 4 | converter[in[i + 1]];
        out[i / 2] = byte;
    }
}

int main()
{
    // char buffer[1000], hex[200], send_data[100] = "xin chao toi la tran gia luong";
    // uint16_t send_byte;
    int des_fd = open(DRIVER_FILE_NAME, O_RDWR);

    // send_byte = ((uint16_t)(strlen(send_data) / 8) + 1) * 8;
    // sprintf(buffer, "%s\n%d\n%s", "encrypt", send_byte, send_data);

    // char type[100], data[200];
    // size_t data_len;

    // write(des_fd, buffer, strlen(buffer));

    // memset(send_data, 0, sizeof(buffer));
    // read(des_fd, send_data, sizeof(send_data));

    // sprintf(buffer, "%s\n%d\n%s", "decrypt", send_byte, send_data);
    // write(des_fd, buffer, strlen(buffer));

    // memset(buffer, 0, sizeof(buffer));
    // read(des_fd, buffer, sizeof(buffer));

    // printf("buffer: %s\n", buffer);

    char test_data[1000] = "test 123456786", hex[100], bin[100], cipher[100];
    hextostring(test_data, strlen(test_data), hex);
    memset(test_data, 0, sizeof(test_data));
    sprintf(test_data, "encrypt\n%s", hex);
    printf("%s\n", test_data);
    write(des_fd, test_data, strlen(test_data));
    read(des_fd, cipher, sizeof(cipher));

    printf("cipher: %s\n", cipher);

    memset(test_data, 0, sizeof(test_data));
    sprintf(test_data, "decrypt\n%s", cipher);
    printf("%s\n", test_data);
    write(des_fd, test_data, strlen(test_data));

    memset(cipher, 0, sizeof(cipher));
    read(des_fd, cipher, sizeof(cipher));

    printf("plan text: %s\n", cipher);
    stringtohex(cipher, strlen(cipher), test_data);
    printf("test data: %s\n", test_data);

    return 0;
}