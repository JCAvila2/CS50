#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Check if all the values are different
            if (!(image[h][w].rgbtRed == image[h][w].rgbtGreen && image[h][w].rgbtBlue == image[h][w].rgbtGreen))
            {
                // Get the average of all 3 colors to know the brightness in grayscale and apply it to the image
                int average = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / (float) 3);
                image[h][w].rgbtRed = average;
                image[h][w].rgbtGreen = average;
                image[h][w].rgbtBlue = average;
            }
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // Apply the given algorithm for this case
            int sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int sepiaGreen = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);

            // Check if any value is bigger than 255, and if it is change its value to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Apply the calculated values to the pixel
            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0, m = floor(width / 2); h < height; h++)
    {
        int w_r = width - 1;
        int w_l = 0;

        // Iterate through the pixels from the limits to the center
        while (w_l <= m && w_r >= m)
        {
            // Save temporal values of left
            int temp_colorRed_l = image[h][w_l].rgbtRed;
            int temp_colorGreen_l = image[h][w_l].rgbtGreen;
            int temp_colorBlue_l = image[h][w_l].rgbtBlue;

            // Change rigth values to left
            image[h][w_l].rgbtRed = image[h][w_r].rgbtRed;
            image[h][w_l].rgbtGreen = image[h][w_r].rgbtGreen;
            image[h][w_l].rgbtBlue = image[h][w_r].rgbtBlue;

            // Change the right values with the temporal
            image[h][w_r].rgbtRed = temp_colorRed_l;
            image[h][w_r].rgbtGreen = temp_colorGreen_l;
            image[h][w_r].rgbtBlue = temp_colorBlue_l;

            // prepare for the next iteration
            w_r--;
            w_l++;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image
    RGBTRIPLE image_copy[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image_copy[h][w] = image[h][w];
        }
    }


    // Blurry the original image with the data from the copy
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int average_red;
            int average_green;
            int average_blue;


            // Check if this pixel is on a corner
            if (h == 0 && w == 0) // Top left
            {
                average_red = round((image_copy[h][w].rgbtRed + image_copy[h][w + 1].rgbtRed + image_copy[h + 1][w].rgbtRed
                                     + image_copy[h + 1][w + 1].rgbtRed) / (float) 4);

                average_green = round((image_copy[h][w].rgbtGreen + image_copy[h][w + 1].rgbtGreen + image_copy[h + 1][w].rgbtGreen
                                       + image_copy[h + 1][w + 1].rgbtGreen) / (float) 4);

                average_blue = round((image_copy[h][w].rgbtBlue + image_copy[h][w + 1].rgbtBlue + image_copy[h + 1][w].rgbtBlue
                                      + image_copy[h + 1][w + 1].rgbtBlue) / (float) 4);
            }
            else if (h == 0 && w == width - 1) // Top right
            {
                average_red = round((image_copy[h][w].rgbtRed + image_copy[h][w - 1].rgbtRed + image_copy[h + 1][w].rgbtRed
                                     + image_copy[h + 1][w - 1].rgbtRed) / (float) 4);

                average_green = round((image_copy[h][w].rgbtGreen + image_copy[h][w - 1].rgbtGreen + image_copy[h + 1][w].rgbtGreen
                                       + image_copy[h + 1][w - 1].rgbtGreen) / (float) 4);

                average_blue = round((image_copy[h][w].rgbtBlue + image_copy[h][w - 1].rgbtBlue + image_copy[h + 1][w].rgbtBlue
                                      + image_copy[h + 1][w - 1].rgbtBlue) / (float) 4);
            }
            else if (h == height - 1 && w == 0) // Bottom left
            {
                average_red = round((image_copy[h][w].rgbtRed + image_copy[h - 1][w].rgbtRed + image_copy[h - 1][w + 1].rgbtRed
                                     + image_copy[h][w + 1].rgbtRed) / (float) 4);

                average_green = round((image_copy[h][w].rgbtGreen + image_copy[h - 1][w].rgbtGreen + image_copy[h - 1][w + 1].rgbtGreen
                                       + image_copy[h][w + 1].rgbtGreen) / (float) 4);

                average_blue = round((image_copy[h][w].rgbtBlue + image_copy[h - 1][w].rgbtBlue + image_copy[h - 1][w + 1].rgbtBlue
                                      + image_copy[h][w + 1].rgbtBlue) / (float) 4);
            }
            else if (h == height - 1 && w == width - 1) // Bottom right
            {
                average_red = round((image_copy[h][w].rgbtRed + image_copy[h - 1][w].rgbtRed + image_copy[h - 1][w - 1].rgbtRed
                                     + image_copy[h][w - 1].rgbtRed) / (float) 4);

                average_green = round((image_copy[h][w].rgbtGreen + image_copy[h - 1][w].rgbtGreen + image_copy[h - 1][w - 1].rgbtGreen
                                       + image_copy[h][w - 1].rgbtGreen) / (float) 4);

                average_blue = round((image_copy[h][w].rgbtBlue + image_copy[h - 1][w].rgbtBlue + image_copy[h - 1][w - 1].rgbtBlue
                                      + image_copy[h][w - 1].rgbtBlue) / (float) 4);
            }

            // Check if the pixel is on a limit
            else if (h == 0) // Top
            {
                average_red = round((
                                        image_copy[h][w - 1].rgbtRed + image_copy[h][w].rgbtRed + image_copy[h][w + 1].rgbtRed
                                        + image_copy[h + 1][w - 1].rgbtRed + image_copy[h + 1][w].rgbtRed + image_copy[h + 1][w + 1].rgbtRed)
                                    / (float) 6);

                average_green = round((
                                          image_copy[h][w - 1].rgbtGreen + image_copy[h][w].rgbtGreen + image_copy[h][w + 1].rgbtGreen
                                          + image_copy[h + 1][w - 1].rgbtGreen + image_copy[h + 1][w].rgbtGreen + image_copy[h + 1][w + 1].rgbtGreen)
                                      / (float) 6);

                average_blue = round((
                                         image_copy[h][w - 1].rgbtBlue + image_copy[h][w].rgbtBlue + image_copy[h][w + 1].rgbtBlue
                                         + image_copy[h + 1][w - 1].rgbtBlue + image_copy[h + 1][w].rgbtBlue + image_copy[h + 1][w + 1].rgbtBlue)
                                     / (float) 6);

            }
            else if (h == height - 1) // Bottom
            {
                average_red = round((
                                        image_copy[h - 1][w - 1].rgbtRed + image_copy[h - 1][w].rgbtRed + image_copy[h - 1][w + 1].rgbtRed
                                        + image_copy[h][w - 1].rgbtRed + image_copy[h][w].rgbtRed + image_copy[h][w + 1].rgbtRed)
                                    / (float) 6);

                average_green = round((
                                          image_copy[h - 1][w - 1].rgbtGreen + image_copy[h - 1][w].rgbtGreen + image_copy[h - 1][w + 1].rgbtGreen
                                          + image_copy[h][w - 1].rgbtGreen + image_copy[h][w].rgbtGreen + image_copy[h][w + 1].rgbtGreen)
                                      / (float) 6);

                average_blue = round((
                                         image_copy[h - 1][w - 1].rgbtBlue + image_copy[h - 1][w].rgbtBlue + image_copy[h - 1][w + 1].rgbtBlue
                                         + image_copy[h][w - 1].rgbtBlue + image_copy[h][w].rgbtBlue + image_copy[h][w + 1].rgbtBlue)
                                     / (float) 6);
            }
            else if (w == 0) // Left
            {
                average_red = round((
                                        image_copy[h - 1][w].rgbtRed + image_copy[h][w].rgbtRed + image_copy[h + 1][w].rgbtRed
                                        + image_copy[h - 1][w + 1].rgbtRed + image_copy[h][w + 1].rgbtRed + image_copy[h + 1][w + 1].rgbtRed)
                                    / (float) 6);

                average_green = round((
                                          image_copy[h - 1][w].rgbtGreen + image_copy[h][w].rgbtGreen + image_copy[h + 1][w].rgbtGreen
                                          + image_copy[h - 1][w + 1].rgbtGreen + image_copy[h][w + 1].rgbtGreen + image_copy[h + 1][w + 1].rgbtGreen)
                                      / (float) 6);

                average_blue = round((
                                         image_copy[h - 1][w].rgbtBlue + image_copy[h][w].rgbtBlue + image_copy[h + 1][w].rgbtBlue
                                         + image_copy[h - 1][w + 1].rgbtBlue + image_copy[h][w + 1].rgbtBlue + image_copy[h + 1][w + 1].rgbtBlue)
                                     / (float) 6);

            }
            else if (w == width - 1) // Right
            {
                average_red = round((
                                        image_copy[h - 1][w].rgbtRed + image_copy[h][w].rgbtRed + image_copy[h + 1][w].rgbtRed
                                        + image_copy[h - 1][w - 1].rgbtRed + image_copy[h][w - 1].rgbtRed + image_copy[h + 1][w - 1].rgbtRed)
                                    / (float) 6);

                average_green = round((
                                          image_copy[h - 1][w].rgbtGreen + image_copy[h][w].rgbtGreen + image_copy[h + 1][w].rgbtGreen
                                          + image_copy[h - 1][w - 1].rgbtGreen + image_copy[h][w - 1].rgbtGreen + image_copy[h + 1][w - 1].rgbtGreen)
                                      / (float) 6);

                average_blue = round((
                                         image_copy[h - 1][w].rgbtBlue + image_copy[h][w].rgbtBlue + image_copy[h + 1][w].rgbtBlue
                                         + image_copy[h - 1][w - 1].rgbtBlue + image_copy[h][w - 1].rgbtBlue + image_copy[h + 1][w - 1].rgbtBlue)
                                     / (float) 6);
            }

            // For the inner pixels
            else
            {
                average_red = round((
                                        image_copy[h - 1][w - 1].rgbtRed + image_copy[h - 1][w].rgbtRed + image_copy[h - 1][w + 1].rgbtRed
                                        + image_copy[h][w - 1].rgbtRed + image_copy[h][w].rgbtRed + image_copy[h][w + 1].rgbtRed
                                        + image_copy[h + 1][w - 1].rgbtRed + image_copy[h + 1][w].rgbtRed + image_copy[h + 1][w + 1].rgbtRed)
                                    / (float) 9);

                average_green = round((
                                          image_copy[h - 1][w - 1].rgbtGreen + image_copy[h - 1][w].rgbtGreen + image_copy[h - 1][w + 1].rgbtGreen
                                          + image_copy[h][w - 1].rgbtGreen + image_copy[h][w].rgbtGreen + image_copy[h][w + 1].rgbtGreen
                                          + image_copy[h + 1][w - 1].rgbtGreen + image_copy[h + 1][w].rgbtGreen + image_copy[h + 1][w + 1].rgbtGreen)
                                      / (float) 9);

                average_blue = round((
                                         image_copy[h - 1][w - 1].rgbtBlue + image_copy[h - 1][w].rgbtBlue + image_copy[h - 1][w + 1].rgbtBlue
                                         + image_copy[h][w - 1].rgbtBlue + image_copy[h][w].rgbtBlue + image_copy[h][w + 1].rgbtBlue
                                         + image_copy[h + 1][w - 1].rgbtBlue + image_copy[h + 1][w].rgbtBlue + image_copy[h + 1][w + 1].rgbtBlue)
                                     / (float) 9);
            }

            // Change the color of the actual pixel
            image[h][w].rgbtRed = average_red;
            image[h][w].rgbtGreen = average_green;
            image[h][w].rgbtBlue = average_blue;
        }
    }
}
