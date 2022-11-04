#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
     //for each pixle avg the rgb value and set all rgb equal to that
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // use sepia formula to change values making sure they are not ablve 255 or below 0
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            image[i][j].rgbtRed = sepiaRed;

            int sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            image[i][j].rgbtGreen = sepiaGreen;

            int sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
int newvalue(int i, int j, int height, int width, RGBTRIPLE copy[height][width], int color);

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = newvalue(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = newvalue(i, j, height, width, copy, 1);
            image[i][j].rgbtBlue = newvalue(i, j, height, width, copy, 2);
        }
    }
    return;
}

int newvalue(int i, int j, int height, int width, RGBTRIPLE copy[height][width], int color)
{
    int sum = 0;
    int denom = 0;

    for( int k = i - 1; k < i + 2; k++)
    {
        for( int l = j - 1; l < j + 2; l++)
        {
            if(k < 0 || k > height || l < 0 || l > width)
            {
                continue;
            }
            else if(color == 0)
            {
                sum += copy[k][l].rgbtRed;
                denom++;
            }
            else if(color == 1)
            {
                sum += copy[k][l].rgbtGreen;
                denom++;
            }
            else if(color == 2)
            {
                sum += copy[k][l].rgbtBlue;
                denom++;
            }
        }
    }
    int finalval = sum/denom;
    return finalval;
}