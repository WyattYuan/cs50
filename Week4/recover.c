#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int isHead(BYTE *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Damn, your card can't be opened for reading.");
        return 1;
    }

    uint8_t buffer[512];
    int count = 0;
    char filename[8];
    FILE *outptr = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (isHead(buffer))
        {
            // 关闭上一个文件(注释掉这一行会导致内存问题，因为最后一次没有关闭文件)
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            snprintf(filename, sizeof(filename), "%03d.jpg", count);
            outptr = fopen(filename, "w");

            // if (outptr == NULL)//by fitten
            // {
            //     printf("Could not create output file.\n");
            //     return 1;
            // }
            count++;
        }

        // 继续写入数据块到当前打开的JPEG文件
        if (outptr != NULL)
        {
            fwrite(buffer, 1, 512, outptr);
        }
    }

    // 如果在循环外仍然有打开的文件，确保关闭它，无此行会有内存问题
    if (outptr != NULL)
    {
        fclose(outptr);
    }

    // 关闭内存卡文件
    fclose(card);
}

int isHead(BYTE *buffer)
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0;
            // f0 = 1111 0000
            // e0 = 1110 0000
}
