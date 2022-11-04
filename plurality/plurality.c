#include <cs50.h>
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

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

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
        candidate[i].name = argv[i + 1];
        candidate[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name)) // this will run the vote bool function
        {
            printf("Invalid vote.\n");
        }

    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++)
    {
         // adds to vote total if they are the same by comparing strings
         // tried to do candidates[i].name == name originally but didn't work
         // REMEMBER == is only for numbers for char or string use strcmp (return 0 if same)
        if(strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    //if none of the candidates matched it won't return true so its invalid
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
   /* BETTER WAY (NOT OVER THINKING IT)
   int maximum_vote = 0;

    //iterate over list of candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //check for candidate votes that are  greater than maximum_vote and set them to maximum_vote
        if (candidates[i].votes > maximum_vote)
        {
            maximum_vote = candidates[i].votes;
        }
    }

    //iterate over list of candidate
    for (int i = 0; i < candidate_count; i++)
    {
        //check for candidate votes that are equal to maximum vote and print them as you go
        if (candidates[i].votes == maximum_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    */

   //initlize winner and votes needed to be winner
   string winner[MAX];
   winner[0] = candidates[0].name;
   int wincount = candidates[0].votes;
   int totalwinners = 1;
    //loop through and see which one(s) had the most
   for(int i = 1; i < candidate_count; i++)
   {
       if(wincount < candidates[i].votes)
       {
        winner[0] = candidates[i].name;
        wincount = candidates[i].votes;
        totalwinners = 1;
       }
       else if(wincount == candidates[i].votes)
       {
        totalwinners += 1;
        winner[totalwinners - 1] = candidates[i].name;
       }
   }
   //print all winners
   for(int j = 0; j < totalwinners; j++)
   {
       printf("WINNER: %s\n", winner[j]);
   }
    return;
}