#include <stdio.h>
#include <stdlib.h>

#define ARG_FILE 1 // defines the index of the file in the argv array

int main(int argc, char *argv[])
{
    if (argc != 2) // checks if the usage of the program is correct
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    char *infile = argv[ARG_FILE]; // remembers the file needed to be opened

    FILE *forensic = fopen(infile, "rb");
    if (forensic == NULL) // checks if the file exists
    {
        printf("Could not open %s\n.", infile);
        return 1;
    }

    unsigned char buffer[512]; // blocks that will check the file
    int file_index = 0;        // set the index of the filename
    FILE *img = NULL;          // set the first pointer file

    while (fread(buffer, 1, 512, forensic) == 512)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF &&
            (buffer[3] & 0xF0) == 0xE0)
        {
            if (img != NULL) // close any previously open file
            {
                fclose(img);
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", file_index);
            img = fopen(filename, "wb");

            file_index++;
        }
        if (img != NULL) // if no file is open, copy the contents to the img
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    if (img != NULL)
    {
        fclose(img);
    }
    fclose(forensic);
}
