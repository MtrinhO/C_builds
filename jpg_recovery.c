//Problem prompt: CS50

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define FAT 512
#define FileNameLen 8

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
//(0): Checks for invalid/more than 1 input file, defines files, indexes
    BYTE buffer[FAT];
    FILE* card = fopen(argv[1], "r");
    FILE* jpg;
    if(argc!=2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }

    if(card==NULL)
    {
        printf("File not found.\n");
        return 1;
    }

//(1): Iterate through reading frame, only accounts for JPG 512B blocks
    int recovered_jpgs = 0;
    bool first_jpg_found = false;
    while(fread(buffer, FAT, 1, card))
    {
        //If beginning of a new JPG
        if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && ((buffer[3] & 0xf0)==0xe0 && first_jpg_found==false))
        {
            //If first JPEG, indicate first jpeg found, then write
            first_jpg_found=true;
            char filename[FileNameLen];
            sprintf(filename, "%03i.jpg", recovered_jpgs);
            jpg = fopen(filename, "w");
            fwrite(buffer, FAT, 1, jpg);
            recovered_jpgs++;
        }
        //Else if n jpeg (n!=1), close previous jpeg and write
        else if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && ((buffer[3] & 0xf0)==0xe0))
        {
            fclose(jpg);

            char filename[FileNameLen];
            sprintf(filename, "%03i.jpg", recovered_jpgs);
            jpg = fopen(filename, "w");
            fwrite(buffer, FAT, 1, jpg);
            recovered_jpgs++;
        }
        //If continution of JPEG
        else if (first_jpg_found==true)
        {
            fwrite(buffer, FAT, 1, jpg);
        }
    }
    //Fin: close files
    fclose(jpg);
    fclose(card);
}