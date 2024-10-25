#include "helpers.h"
#include <math.h>
#include <stdlib.h>

#define MAX_RGB_VALUE 255 // 添加最大RGB值的宏定义

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 原代码：多次计算平均值，结果赋值多次
            // image[i][j].rgbtRed =
            //     round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            uint8_t average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average; // 合并赋值操作
            image[i][j].rgbtBlue = average; // 合并赋值操作
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (newimage == NULL) // 添加内存分配失败的检查
    {
        return; // 处理内存分配失败
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = 0, green = 0, blue = 0;//刷新重复利用的变量
            double count = 0; // 精度
            // 遍历3x3区域,将rgb值记录
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (h + i < 0 || h + i >= height || w + j < 0 || w + j >= width)
                    {
                        // do nothing
                    }
                    else 
                    {
                        red += image[h + i][w + j].rgbtRed;
                        green += image[h + i][w + j].rgbtGreen;
                        blue += image[h + i][w + j].rgbtBlue;
                        count++;
                    }
                }
            }
            // 求均值并赋给newimage
            newimage[h][w].rgbtRed = round(red / count);
            newimage[h][w].rgbtGreen = round(green / count);
            newimage[h][w].rgbtBlue = round(blue / count);
        }
    }
    // 将模糊结果复制回原图
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = newimage[h][w]; // 无需.rgbtRed .rgbtGreen这样分别赋值
        }
    }
    free(newimage); // 释放内存
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE(*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (newimage == NULL) // 添加内存分配失败的检查
    {
        return; // 处理内存分配失败
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int GxRed = 0, GyRed = 0;
            int GxGreen = 0, GyGreen = 0;
            int GxBlue = 0, GyBlue = 0;

            // 原代码：多次进行边界检查
            // 遍历每个像素
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (h + i < 0 || h + i >= height || w + j < 0 || w + j >= width)
                    {
                        // do nothing
                    }
                    else
                    {
                        // 求Gx，Gy
                        GxRed += Gx[i + 1][j + 1] * image[h + i][w + j].rgbtRed;
                        GyRed += Gy[i + 1][j + 1] * image[h + i][w + j].rgbtRed;
                        GxGreen += Gx[i + 1][j + 1] * image[h + i][w + j].rgbtGreen;
                        GyGreen += Gy[i + 1][j + 1] * image[h + i][w + j].rgbtGreen;
                        GxBlue += Gx[i + 1][j + 1] * image[h + i][w + j].rgbtBlue;
                        GyBlue += Gy[i + 1][j + 1] * image[h + i][w + j].rgbtBlue;
                    }
                }
            }
            // 求平方平均数
            // 原代码：多次调用平方根和条件判断
            newimage[h][w].rgbtRed = fmin(round(sqrt(GxRed * GxRed + GyRed * GyRed)), MAX_RGB_VALUE);  // 确保不超过255
            newimage[h][w].rgbtGreen = fmin(round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)), MAX_RGB_VALUE); // 确保不超过255
            newimage[h][w].rgbtBlue = fmin(round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue)), MAX_RGB_VALUE); // 确保不超过255
        }
    }
    // 将边缘检测结果复制回原图
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = newimage[h][w]; // 直接赋值给原图，简化代码
        }
    }
    free(newimage); // 释放内存
}
