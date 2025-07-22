#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //long dollars = 1;
    //while (true){
        //char c = get_char("Here's $%li. Double it and give it to the next person? ", dollars);
        //if (c == 'y' || c == 'Y'){
            //dollars *=2;
        //} else if (c == 'n' || c == 'N'){
            //break;
        //}
    //}
    //printf("Here's $%li.\n", dollars);

    int x = get_float("x: ");
    int y = get_float("y: ");

    printf("%.10f\n", (double) x / y);
    // floating-point imprecision: only uses 32 bits; use double for 64 bits
    // overflow will make it a problem
}
