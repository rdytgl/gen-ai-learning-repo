#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the averages of the rgb values
            int aveHex =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update the value of the RGB values
            image[i][j].rgbtRed = aveHex;
            image[i][j].rgbtGreen = aveHex;
            image[i][j].rgbtBlue = aveHex;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the sepvia int values of each color
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);

            // If the values go over 255, cap at 255
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

            // Update the value of the RGB values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++) // only get half of the image so it does not overlap
        {
            // Get RGB triple of the pixels
            int reflectRed = image[i][j].rgbtRed;
            int reflectGreen = image[i][j].rgbtGreen;
            int reflectBlue = image[i][j].rgbtBlue;

            // Get RGB triple of the opposite side of the image then place it towards the end
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            // Swap the pixels
            image[i][width - 1 - j].rgbtRed = reflectRed;
            image[i][width - 1 - j].rgbtGreen = reflectGreen;
            image[i][width - 1 - j].rgbtBlue = reflectBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Get RGBTRIPLE
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++) // di = delta i; change in row
            {
                for (int dj = -1; dj <= 1; dj++) // dj = delta j; change in col
                {
                    int ni = i + di; // neighbour row
                    int nj = j + dj; // neighbour col

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    return;
}
