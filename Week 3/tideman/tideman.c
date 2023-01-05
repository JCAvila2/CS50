#include <cs50.h>
#include <stdio.h>
#include <string.h> // i added this


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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool is_cycle(int start_cycle, int finish_cycle);
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

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check if the vote is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // check if the candidate is on a previous rank (was voted by this person before)
            for (int r = 0; r < rank; r++)
            {
                if (ranks[r] == i)
                {
                    return false;
                }
            }

            // if is not on a previous rank and is valid make the vote
            ranks[rank] = i;
            return true;
        }
    }

    // if the name received is not a valid candidate return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update 2d array "preferences" with the winners
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int l = 0; l < candidate_count; l++)
    {
        for (int j = l + 1; j < candidate_count; j++)
        {
            pair_count++;
            if (preferences[l][j] > preferences[j][l])
            {
                pairs[pair_count - 1].winner = l;
                pairs[pair_count - 1].loser = j;
            }
            else if (preferences[l][j] < preferences[j][l])
            {
                pairs[pair_count - 1].winner = j;
                pairs[pair_count - 1].loser = l;
            }
            else
            {
                pair_count--;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int changes;
    do
    {
        changes = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            // if needed use abs (need to add a library)
            int actual_gap = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
            int next_gap = preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner];

            // check if the next has a bigger W
            if (actual_gap < next_gap)
            {
                changes++;

                int temp_w = pairs[i].winner;
                int temp_l = pairs[i].loser;

                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;

                pairs[i + 1].winner = temp_w;
                pairs[i + 1].loser = temp_l;
            }
        }
    }
    while (changes != 0);
}

// Check if adding a new edge will create a cycle
bool is_cycle(int start_cycle, int finish_cycle)
{
    if (finish_cycle == start_cycle)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[finish_cycle][i])
        {
            if (is_cycle(start_cycle, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int false_candidates = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                false_candidates++;
                if (false_candidates == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
}