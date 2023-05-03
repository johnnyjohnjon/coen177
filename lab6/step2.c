#include <stdio.h>

int main(int argc, char *argv[])
{
    char buffer[10000];
    FILE *fp;

    fp = fopen(argv[1], "rb");

    if (fp == NULL)
    {
        printf("Could not open file %s", argv[1]);
        return 1;
    }

    while (fread(buffer, sizeof(buffer), 1, fp))
    {
    }
    fclose(fp);
    return 0;
}