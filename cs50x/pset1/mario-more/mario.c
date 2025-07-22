#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("What is your desired height of Mario's pyramid? ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++)
    {
        // prints leading spaces to shift left pyramid
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }

        // prints the blocks to create left pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        // prints the spaces between the two pyramids
        printf("  ");

        // prints the blocks to create right pyramid
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
