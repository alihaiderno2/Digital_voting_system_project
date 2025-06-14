# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <stdbool.h>
# include <windows.h>
# include <ctype.h>
typedef struct Candidate
{
    char name[100];
    char Party_name[20];
    int votes;
    long long int ID;
}candidate;
typedef struct Voter
{
    long long int ID;
    char name[100];
    bool hasvoted;
} voter;
candidate candid_list[6];
voter voter_list[100];
int candidate_count=0;
int voter_count=0;
bool Loggedin=false;
void Admin();
void Admin_Login();
void Entry_candidates();
void candid_list_show();
void Votes_casted();
void Display_Result();
void Add_voters();
void delete_voters();
void candidate_load();
void voter_load();
void candidate_count_updater();
void voter_count_updater();
void voter_list_updater();
void candid_list_updater();
bool name_input_validation(char *s);
void MainMenu();
void castVote();
int main()
{
    castVote();
} 
void castVote() 
{
    long long int voterID;
    int voter_index = -1;

    printf("\n====================== VOTING PANEL ======================\n");
    printf("Enter your Voter ID: ");
    scanf("%lld", &voterID);

    // Verify Voter ID
    for (int i = 0; i < voter_count; i++) {
        if (voter_list[i].ID == voterID) {
            voter_index = i;
            break;
        }
    }

    if (voter_index == -1) {
        printf(" Voter ID not found. Please register first.\n");
        return;
    }

    if (voter_list[voter_index].hasvoted) {
        printf(" You have already voted. Multiple voting is not allowed.\n");
        return;
    }

    printf("\n Welcome %s!\n", voter_list[voter_index].name);
    printf("Here is the list of candidates:\n\n");

    printf("-----------------------------------------------------------\n");
    printf("| Serial |     Name      |        Party         |\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < candidate_count; i++) {
        printf("|   %2d   | %-13s | %-20s |\n", i, candid_list[i].name, candid_list[i].Party_name);
    }

    printf("-----------------------------------------------------------\n");

    // Cast vote
    int vote_choice;
    printf("Enter the serial number of the candidate you want to vote for: ");
    scanf("%d", &vote_choice);

    if (vote_choice < 0 || vote_choice >= candidate_count) {
        printf(" Invalid choice. Vote not recorded.\n");
        return;
    }

    // Confirm vote
    char confirm;
    printf("\nYou are voting for: %s (%s)\n", 
           candid_list[vote_choice].name, candid_list[vote_choice].Party_name);
    printf("Are you sure? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        candid_list[vote_choice].votes++;
        voter_list[voter_index].hasvoted = true;

        printf("\n Vote successfully cast for %s (%s). Thank you, %s!\n",
               candid_list[vote_choice].name,
               candid_list[vote_choice].Party_name,
               voter_list[voter_index].name);
    } else {
        printf(" Vote cancelled.\n");
    }

    printf("===========================================================\n");
}
