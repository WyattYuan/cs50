#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long card = get_long("Type a credit card number in,plz.");

    long sum1 = 0, sum2 = 0, sum = 0;
    int first_number, second_number;
    int digit = 0, first_two_number = 0;

    for (long i = (card * 10) / 100; i > 1; i /= 100)
    {
        int t = (i % 10) * 2;
        if(t > 9)
        {
            t = t / 10 + t % 10;
        }
        //printf("%d\n", t);
        sum1 += t;

    }
    for (long i = card; i > 1; i /= 100)
    {
        sum2 += (i % 10);
    }

    sum = sum1 + sum2;

    //printf("%ld,%ld,%ld\n", sum1,sum2,sum);

    if (sum % 10 == 0)
    {
        digit = log10(card) + 1;
        first_number = card / pow(10, digit - 1);
        first_two_number = card / pow(10, digit - 2);
        //printf("check:%i,%i\n", first_number, first_two_number);

        if (digit == 15 && (first_two_number == 34 || first_two_number == 37))
        {
            printf("AMEX\n");
        }
        else if (digit == 16 && first_two_number > 50 && first_two_number < 56)
        {
            printf("MASTERCARD\n");
        }
        else if ((digit == 13 || digit == 16) && first_number == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
