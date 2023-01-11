#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define BLOCK_SIZE 512
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // Check if the user write only one command line argument
    if (argc != 2)
    {
        printf("./recover (name of the forensic image) \n");
        return 1;
    }


    // Open the input file
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Input file cannot be open \n");
        return 1;
    }


    // Set up the output files
    int images_found = 0;
    char output_file_name[8];
    FILE *output_file;


    // Allocate memory for one block
    BYTE data[BLOCK_SIZE];


    // Read each block until the end of the input file
    while (fread(data, BLOCK_SIZE, 1, input_file) == 1)
    {
        // Check if the block has an JPEG header
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && ((data[3] & 0xf0) == 0xe0))
        {
            // If the actual image is not the first one found close the output file of the previous image
            if (images_found != 0)
            {
                fclose(output_file);
            }

            // Change the name of the output file, open the new output file and write the data
            sprintf(output_file_name, "%03i.jpg", images_found);
            output_file = fopen(output_file_name, "w");
            fwrite(data, BLOCK_SIZE, 1, output_file);
            images_found++;
        }
        else if (images_found > 0)
        {
            fwrite(data, BLOCK_SIZE, 1, output_file);
        }
    }


    // Close both files
    fclose(input_file);
    fclose(output_file);
}