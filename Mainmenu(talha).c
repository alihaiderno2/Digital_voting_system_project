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

int main()
 {
    candidate_data();

    voter_data();

    MainMenu();

    return 0;
}

  void MainMenu()
 {
int choice;

system("cls");
    
  printf("\n\n");

    printf("==================================\n");

  printf(" SIMPLE VOTING SYSTEM MENU \n");

    printf("======================================\n");

 printf("1. Admin Login\n");

 printf("2. Voter Login\n");

    printf("3. View Candidates\n");

   printf("4. Exit\n");

   printf("=========================================\n");

    printf("Enter your choice (1-4):");

   scanf("%d", &choice);
    
     switch(choice)
     {
     case 1:
     // password check
     {
     char password[20];

     printf("Enter admin password:");

     scanf("%s", password);
                
     if(strcmp(password,"admin123") == 0)

     // Simple hardcoded password
     {
            Admin();
      }
        else
        {
    printf("Wrong password! N0 Access! Try Again\n");

    getch(); // Wait for key press

         MainMenu();

                }
            }
            break;
            
     case 2:
     // Voter login here

     printf("Voter login feature is here.\n");

     printf("Press any key to return to main menu");

     getch();

     MainMenu();
     break;
            
    case 3:
     // Show candidate list

    Candidate_list_show();

     printf("\nPress any key to return to main menu...");

     getch();

     MainMenu();
     break;
            
    case 4:
     printf("Exiting program. Thank you!\n");

     exit(0);
         break;
            
default:
     printf("Invalid choice! Please try again.\n");

        getch();

        MainMenu();
    }
}