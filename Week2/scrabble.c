#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
//算法稀烂，不如答案
int scrabble(char c);

int main(void)
{
    string word[2];
    word[0] = get_string("Player 1:");
    word[1] = get_string("Player 2:");
    int score[2] = {0, 0};
    int len[2] = {strlen(word[0]), strlen(word[1])};
    // 计算分数
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < len[i]; j++)
        {
            word[i][j] = toupper(word[i][j]);
            score[i] += scrabble(word[i][j]);
        }
    }
    // 比较分数
    if (score[0] > score[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (score[0] < score[1])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Ties!\n");
    }
}

int scrabble(char c)
{
    if (c == 'A')
    {
        return 1;
    }
    else if (c == 'B')
    {
        return 3;
    }
    else if (c == 'C')
    {
        return 3;
    }
    else if (c == 'D')
    {
        return 2;
    }
    else if (c == 'E')
    {
        return 1;
    }
    else if (c == 'F')
    {
        return 4;
    }
    else if (c == 'G')
    {
        return 2;
    }
    else if (c == 'H')
    {
        return 4;
    }
    else if (c == 'I')
    {
        return 1;
    }
    else if (c == 'J')
    {
        return 8;
    }
    else if (c == 'K')
    {
        return 5;
    }
    else if (c == 'L')
    {
        return 1;
    }
    else if (c == 'M')
    {
        return 3;
    }
    else if (c == 'N')
    {
        return 1;
    }
    else if (c == 'O')
    {
        return 1;
    }
    else if (c == 'P')
    {
        return 3;
    }
    else if (c == 'Q')
    {
        return 10;
    }
    else if (c == 'R')
    {
        return 1;
    }
    else if (c == 'S')
    {
        return 1;
    }
    else if (c == 'T')
    {
        return 1;
    }
    else if (c == 'U')
    {
        return 1;
    }
    else if (c == 'V')
    {
        return 4;
    }
    else if (c == 'W')
    {
        return 4;
    }
    else if (c == 'X')
    {
        return 8;
    }
    else if (c == 'Y')
    {
        return 4;
    }
    else if (c == 'Z')
    {
        return 10;
    }
    else
    {
        return 0;
    }
}
