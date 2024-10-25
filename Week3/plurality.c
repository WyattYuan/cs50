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
} candidate;

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
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    int if_valid = -1;//如果有效，返回这个人的索引，如果无效，返回-1;此法不考虑重名

    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(name,candidates[i].name) == 0){
            if_valid = i;
        }else{
            //do nothing
        }
    }
    if(if_valid != -1){
        candidates[if_valid].votes++;
        return true;
    }
    // go through all the candidates, compare name and candidates[i].name
    // if 0 return ture
    // update candidates[i].votes ++
    // if != 0
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int most = 0;

    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes > most){
            most = candidates[i].votes;
        }else{
            //do nothing
        }
    }
    for(int i = 0; i < candidate_count; i++){
        if(candidates[i].votes == most)printf("%s\n",candidates[i].name);
    }
    return;
}
