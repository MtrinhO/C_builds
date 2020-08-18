#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int margin;
}
pair;

// Structs of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair temp[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(int ranks[]);
void sort_pairs(int left_start, int right_end);
void merger(int left_start, int midpoint, int right_end);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // ranks[i] is voter's ith preference
    int ranks[candidate_count];

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs(ranks);
    sort_pairs(0, candidate_count);
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Assign candidate index to rank index
    for(int x=0; x<candidate_count; x++)
    {
        if(strcmp(name, candidates[x])==0)
        {
            ranks[rank]=x;
            return true;
        }
        else
        continue;
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //Iterate through ranks to pull preferences and builds a 2D adjacency matrix: preferences[i][j]
    for (int a=0; a<candidate_count; a++)
    {
        for (int b=candidate_count; b>-1; b--)
        {
            //preferences[i][j] = how many voters prefer candidate [i] > candidate[j]
            if(a<b)
            preferences[ranks[a]][ranks[b]] +=1;

            else if(b<a)
            preferences[ranks[b]][ranks[a]] +=1;

            //Cannot have a candidate preffered over themselves
            else
            preferences[ranks[a]][ranks[b]] =0;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(int ranks[])
{
    //Iterate through ranks to pull preferences and builds a 2D adjacency matrix: preferences[i][j]
    for (int a=0; a<candidate_count; a++)
    {
        for (int b=candidate_count; b>-1; b--)
        {
            int x=0;
            //if preferences[i][j] > preferences [j][i]. i is winner
            if(preferences[ranks[a]][ranks[b]]>preferences[ranks[b]][ranks[a]])
            {
                pairs[x].winner=ranks[a];
                pairs[x].loser=ranks[b];
                pairs[x].margin = ((preferences[ranks[a]][ranks[b]])/(preferences[ranks[b]][ranks[a]])+1);
                x++;
                pair_count+=1;
            }

            //if preferences[j][i] > preferences [i][j]. j is winner
            else if(preferences[ranks[b]][ranks[a]]>preferences[ranks[a]][ranks[b]])
            {
                pairs[x].winner=ranks[b];
                pairs[x].loser=ranks[a];
                pairs[x].margin = ((preferences[ranks[b]][ranks[a]])/(preferences[ranks[a]][ranks[b]])+1);
                x++;
                pair_count+=1;
            }

            //Cannot have a tied pair
            else
            continue;
        }
    }
    return;
}

// MERGESORT: Sort pairs in decreasing order by strength of victory
void sort_pairs(int left_start, int right_end)
{
    //Recursive cases as long as not 1-element array.
    if(left_start < right_end)
    {
        //Definitions (Reading frame)
        int midpoint = (right_end + left_start)/2;

        //Recursive case #1
        sort_pairs(left_start, midpoint);

        //Recursive case #2
        sort_pairs(midpoint+1, right_end);

        //Merger function on left/right halves
        merger(right_end, midpoint, left_start);
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
    for(int y=0; y<=right_end; y++)
    {
        temp[y].winner = pairs[y].winner;
        temp[y].loser = pairs[y].loser;
        temp[y].margin = pairs[y].margin;
    }

    //Copies right or left smallest values back to original array
    while(a<=midpoint && b<=right_end)
    {
        if(temp[a].margin <= temp[b].margin)
        {
            pairs[c].winner=temp[a].winner;
            pairs[c].loser=temp[a].loser;
            pairs[c].margin=temp[a].margin;
            a++;
        }
        else
        {
            pairs[c].winner=temp[b].winner;
            pairs[c].loser=temp[b].loser;
            pairs[c].margin=temp[b].margin;
            b++;
        }
        c++;
    }
    //Copy the reamaining side of temp back into the original array.
    while(a<=midpoint)
    {
        pairs[c].winner=temp[a].winner;
        pairs[c].loser=temp[a].loser;
        pairs[c].margin=temp[a].margin;
        a++;
        c++;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //Lock pairs in order of victory strength
    for(int z=0; z<pair_count; z++)
    {
        int i = pairs[z].winner;
        int j = pairs[z].loser;
        locked[i][j]=true;
        locked[j][i]=true;
    }
    //Failsafe "if" in case of cycle.
    int m = pair_count-1;
    if(pairs[0].winner == pairs[m].loser && pairs[0].margin > pairs[m].margin)
    locked[pairs[m].winner][pairs[0].winner]=false;
    locked[pairs[0].winner][pairs[m].winner]=false;

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int x = pairs[0].winner;
    printf("%s has won the election! \n", candidates[x]);
    return;
}