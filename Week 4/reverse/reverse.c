#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Use 2 command lines (input file and output file)\n");
        return 1;
    }



    // Open input file for reading
    // TODO #2
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        printf("Error opening the input file \n");
        return 1;
    }



    // Read header into an array
    // TODO #3
    WAVHEADER c;
    fread(&c, sizeof(char), 44, input_file);



    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(c))
    {
        printf("Input is not a WAV file\n");
        return 1;
    }



    // Open output file for writing
    // TODO #5
    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL)
    {
        printf("The output file cannot be open \n");
    }



    // Write header to file
    // TODO #6
    fwrite(&c, sizeof(char), 44, output_file);



    // Use get_block_size to calculate size of block
    // TODO #7
    int size_of_block = get_block_size(c);



    // Write reversed audio to file
    // TODO #8
    // Get the size of the file
    fseek(input_file, 1, SEEK_END);
    long file_size = ftell(input_file);
    rewind(input_file);

    // Read the data and save on memory
    unsigned char *data = malloc(file_size);
    fread(data, 1, file_size, input_file);

    // Close input file
    fclose(input_file);

    // Invert data
    for (int i = 0; i < file_size / 2; i++)
    {
        unsigned char temp = data[i];
        data[i] = data[file_size - i - 1];
        data[file_size - i - 1] = temp;
    }

    // Write the inverted data on the output file and close it
    fwrite(data, 1, file_size, output_file);
    fclose(output_file);
    free(data);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    char input_format[4] = {header.format[0], header.format[1], header.format[2], header.format[3]};
    char *t = strstr(input_format, "WAVE");
    if (t)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int n_channels = header.numChannels;
    float b_p_sample = header.bitsPerSample * 0.125;
    return n_channels * b_p_sample;
}