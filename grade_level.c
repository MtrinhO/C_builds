#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string text[])
{
     int letters = 0;
     int words = 0;
     int sentences = 0;
    // (1): Count letters, words, sentences, Output original text
    printf("Text: ");
    for(int i=1; i<argc; i++)
    {
        //Count words
        words = words+1;

        //Count letters and sentences
        for(int x=0; x<1000; x++)
        {
            if(isupper(text[i][x])!=0 || islower(text[i][x])!=0)
            {
                letters = letters+1;
            }
            else if((strcmp(&text[i][x], ".")==0) || (strcmp(&text[i][x], "!")==0) || (strcmp(&text[i][x], "?")==0))
            {
                sentences = sentences+1;
            }
            else if(ispunct(text[i][x])!=0 || isalpha(text[i][x])!=0)
            {
                continue;
            }
            else if(strcmp(&text[i][x], "\0")==0)
            {
                x=0;
                break;
            }
        }

        //Print outputs
        printf("%s ", text[i]);
    }
    printf("\n");
    printf("%i Word(s)\n", words);
    printf("%i Letter(s)\n", letters);
    printf("%i Sentence(s)\n", sentences);

    // (2): Proportion calculations
    double word_prop = (100.0/words);
    double sentence_avg = (sentences*word_prop);
    double letter_avg = (letters*word_prop);

    // (3): Coleman-Liau formula
    int index = round(0.0588 * letter_avg - 0.296 * sentence_avg - 15.8);

    if(index>15)
    {
        printf("Grade16+ \n");
    }
    else if(index<1)
    {
        printf("Before Grade 1 \n");
    }
    else
    {
      printf("Grade %i \n", index);
    }
}