#include <cs50.h>
#include <stdio.h>

int get_positive_value(void);
void meow(int n);

int main(void)
{
    int times = get_positive_value();
    meow(times);
}

int get_positive_value(void)
{
    int n;
    do
    {
        n = get_int("How many meows? ");
        if (n < 1)
        {
            printf("Value cannot be negative.\n");
        }
    }
    while (n < 1);
    return n;
}
void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
