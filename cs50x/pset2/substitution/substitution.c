// This is a C code that uses a user-provided cipherkey to decode a user-provided text

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

bool is_valid_key(string key);
char subst(char letter, string key);

int main(int argc, char *argv[])
{
    // Set up the arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key \n");
        return 1;
    }

    string key = argv[1];
    // Check if the cipherkey is a valid
    if (!is_valid_key(key))
    {
        printf("Invalid key. The key must contain 26 unique alphabetic characters.\n");
        return 1;
    }

    // Enter text to cipher
    string plaintext = get_string("plaintext: ");

    // Conversion of text
    int n = strlen(plaintext);
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
    {
        printf("%c", subst(plaintext[i], key));
    }
    printf("\n");

    return 0;
}

// Checks the validity cipherkey
bool is_valid_key(string key)
{
    int length = strlen(key);
    if (length != 26)
    {
        return false;
    }

    bool seen[26] = {false};

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }

        int index = toupper(key[i]) - 'A';

        if (seen[index])
        {
            return false;
        }

        seen[index] = true;
    }
    return true;
}

// Encrypts the cipherkey
char subst(char letter, string key)
{
    if (isupper(letter))
    {
        return toupper(key[letter - 'A']);
    }
    else if (islower(letter))
    {
        return tolower(key[letter - 'a']);
    }
    return letter;
}
