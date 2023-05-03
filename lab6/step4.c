
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int buffsize = atoi(argv[2]);

    char buffer[buffsize];
    FILE *fp;
    FILE *fpout;

    fp = fopen(argv[1], "rb");
    fpout = fopen("output", "wb");

    if (fp == NULL)
    {
        printf("Could not open file %s", argv[1]);
        return 1;
    }

    while (fread(buffer, buffsize, 1, fp))
    {
        fwrite(buffer, sizeof(buffer), 1, fpout);
    }

    fclose(fp);
    fclose(fpout);
    return 0;
}