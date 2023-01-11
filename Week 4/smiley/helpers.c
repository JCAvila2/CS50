#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through the rows of the image grid of pixels
    for (int h = 0; h < height; h++)
    {
        // Iterate through the columns of the image grid of pixels
        for (int w = 0; w < width; w++)
        {
            // Check if the actual pixel is black (its black when the value of each BYTE is 0)
            if (image[h][w].rgbtRed == 0x00 && image[h][w].rgbtGreen == 0x00 && image[h][w].rgbtBlue == 0x00)
            {
                // Change the color of the pixel. (In this case I changed it to orange 0xffa500)
                image[h][w].rgbtRed = 0xff;
                image[h][w].rgbtGreen = 0xa5;
            }
        }
    }
}