#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <cs50.h>

int main(int argc, string key[])
{
    //(1a): Key validation for multiple arguments:
    if(argc!=2)
    {
        printf("Only one text key allowed as input \n");
        return 1;
    }

    //(1b): Key validation against repeat chars
    char* str = key[1];
    char* alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for(int m=0; m<strlen(str); m++)
    {
        if (strchr(str, alphabet[m])==NULL)
        {
            printf("No repeating characxters allowed \n");
            return 1;
        }
        else
        {
            continue;
        }
    }

    //(1c): Key validation for: non-alphabetic chars, length != 26 chars:
    for (int x=0; x<27; x++)
    {
        if(ispunct(key[1][x])!=0 || isdigit(key[1][x])!=0)
        {
            printf("Key must only contain alphabetic characters \n");
            return 1;
        }

        if(strcmp(&key[1][26], "\0")!=0 || isalpha(key[1][26])!=0)
        {
            printf("Key must be 26 letters \n");
            return 1;
        }
        else
        {
            continue;
        }
    }

    // (2) Input plaintext, defnitions of alphabet and cypher:
    char* plaintext = get_string("plaintext: ");
    char* cypher=plaintext;

    // (3) Convert plaintext to cyphertext in case-incensitive manner
    int z=0;
    for (int y=0; y<(strlen(plaintext)); z++)
    {
        if(plaintext[y]==tolower(alphabet[z]))
        {
            cypher[y]=tolower(str[z]);
            y+=1;
            z=0;
        }
        else if(plaintext[y]==alphabet[z])
        {
            cypher[y]=str[z];
            y+=1;
            z=0;
        }
        else if(ispunct(plaintext[y])!=0 || isspace(plaintext[y])!=0 || isdigit(plaintext[y])!=0)
        {
            y+=1;
            continue;
        }
    }
    printf("ciphertext: %s \n", cypher);
}