//Merger and mergesort algorithm iterated upon Stephen O'Neil implementation for int arrays.

#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];
candidate temp[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void mergesort(int left_start, int right_end);
void merger(int left_start, int midpoint, int right_end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    mergesort(0,candidate_count);
    string winners[MAX];
    for(int y=0; y<candidate_count+1; y++)
    {
        if(candidates[y].votes == candidates[candidate_count].votes)
        {
            winners[y] = candidates[y].name;
            printf("%s has won the election with %i votes! \n", winners[y], candidates[candidate_count].votes);
        }
    }
    return 1;
}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int x=0; x<candidate_count; x++)
    {
        if(strcmp(name,candidates[x].name)==0)
        {
            printf("%s \n", name);
            candidates[x].votes+=1;
            return true;
        }
        else
        continue;
    }
    return false;
}

// Print the winner (or winners) of the election: Implement recursive merge sort algorithm
void mergesort(left_start, right_end)
{
//Recursive cases as long as not 1-element array.
    if(left_start < right_end)
    {
        //Definitions (Reading frame)
        int midpoint = (right_end + left_start)/2;

        //Recursive case #1
        mergesort(left_start, midpoint);

        //Recursive case #2
        mergesort(midpoint+1, right_end);

        //Merger function on left/right halves
        merger(left_start, midpoint, right_end);
    }
}

//Merger function of structs/arrays
void merger(int left_start, int midpoint, int right_end)
{
    //Index definitions
    int a = left_start;
    int b = midpoint+1;
    int c = left_start;

    //Duplicate candidate structure (temp)
    for(int x=0; x<=right_end; x++)
    {
        temp[x].name = candidates[x].name;
        temp[x].votes = candidates[x].votes;
    }

    //Copies right or left smallest values back to original array
    while(a<=midpoint && b<=right_end)
    {
        if(temp[a].votes <= temp[b].votes)
        {
            candidates[c].name=temp[a].name;
            candidates[c].votes=temp[a].votes;
            a++;
        }
        else
        {
            candidates[c].name=temp[b].name;
            candidates[c].votes=temp[b].votes;
            b++;
        }
        c++;
    }
    //Copy the reamaining side of temp back into the original array.
    while(a<=midpoint)
    {
        candidates[c].name=temp[a].name;
        candidates[c].votes=temp[a].votes;
        a++;
        c++;
    }
}