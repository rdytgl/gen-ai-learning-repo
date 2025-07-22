#include "helpers.h"
#include <math.h>
#define SOBEL_X 3
#define SOBEL_Y 3

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    int Gx[SOBEL_X][SOBEL_X] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int Gy[SOBEL_Y][SOBEL_Y] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRedX = 0;
            float sumGreenX = 0;
            float sumBlueX = 0;
            float sumRedY = 0;
            float sumGreenY = 0;
            float sumBlueY = 0;

            for (int di = -1; di <= 1; di++) // di = delta i; change in row
            {
                for (int dj = -1; dj <= 1; dj++) // dj = delta j; change in col
                {
                    int ni = i + di; // neighbour row
                    int nj = j + dj; // neighbour col

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRedX += copy[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        sumGreenX += copy[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        sumBlueX += copy[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];

                        sumRedY += copy[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        sumGreenY += copy[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        sumBlueY += copy[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }
            int redXY = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int greenXY = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int blueXY = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            image[i][j].rgbtRed = fmin(255, redXY);
            image[i][j].rgbtGreen = fmin(255, greenXY);
            image[i][j].rgbtBlue = fmin(255, blueXY);
        }
    }

    return;
}
