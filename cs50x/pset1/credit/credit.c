#include <cs50.h>
#include <math.h>
#include <stdio.h>

int get_digits(long cc);
string get_type(long cc_num);

int main(void)
{
    long cc_no;

    do
    {
        cc_no = get_long("What is your credit card number? ");
    }
    while (cc_no < 1);

    int sum_verif = get_digits(cc_no);
    // printf("Number Now: %i\n", sum_verif); --> checks the value of the checksum
    string get_cc_type = get_type(cc_no);

    if (sum_verif % 10 == 0)
    {
        printf("%s", get_cc_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

// function to check the digits of the credit card and its validity
int get_digits(long cc)
{
    int log = 0; // checks whether the digit is a positive or a negative
    int twice = 0;
    int tens_verif = 0;
    int ones_verif = 0;
    int even_verif = 0;
    int odd_verif = 0;
    int sum_verif = 0;

    while (cc > 0)
    {
        long mod = cc % 10;
        cc = cc / 10;
        if (log % 2 == 1)
        {
            twice = mod * 2;
            if (twice >= 10)
            {
                tens_verif = twice / 10;
                // printf("tens = %i\n", tens_verif);
                ones_verif = twice % 10;
                // printf("ones = %i\n", ones_verif);
                even_verif = even_verif + tens_verif + ones_verif;
            }
            else
            {
                ones_verif = twice;
                even_verif = even_verif + ones_verif;
                // printf("ones = %i\n", ones_verif);
            }
        }
        else
        {
            odd_verif = mod + odd_verif;
            // printf("odd = %i\n", odd_verif);
        }
        log++;
    }
    sum_verif = even_verif + odd_verif;

    return sum_verif;
}

// function to get the type of credit card

string get_type(long cc_num)
{
    // INIT: CC type for use later & checking of credit card length
    string cc_type = NULL;
    int len_cc_num = 1 + (int) log10(cc_num);

    // Gets the first two starting digits of the CC
    while (cc_num >= 100)
    {
        long mod = cc_num % 10;
        cc_num = cc_num / 10;
    }

    // Checks the CC type based on the starting digits
    if ((cc_num == 34 || cc_num == 37) && len_cc_num == 15)
    {
        cc_type = "AMEX\n";
    }
    else if ((cc_num == 51 || cc_num == 52 || cc_num == 53 || cc_num == 54 || cc_num == 55) &&
             len_cc_num == 16)
    {
        cc_type = "MASTERCARD\n";
    }
    else if (cc_num / 10 == 4 &&
             (len_cc_num == 13 ||
              len_cc_num == 16)) // since VISA can start with 4, we can get the int quotient of the
                                 // first two digits of a valid VISA card to get a value of 4
    {
        cc_type = "VISA\n";
    }
    else
    {
        cc_type = "INVALID\n";
    }

    // printf("cc_num: %li\n", cc_num); --> tests the starting number of the CC
    // printf("cc_type: %s", cc_type); --> validates the type of CC
    return cc_type;
}
