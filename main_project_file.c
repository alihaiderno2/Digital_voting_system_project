# include <stdio.h>
# include <conio.h>
# include <string.h>
# include <stdbool.h>
# include <windows.h>
# include <ctype.h>
//candidate struct
typedef struct Candidate
{
    char name[100];
    char Party_name[20];
    int votes;
    long long int ID;
}candidate;
//voter struct
typedef struct Voter
{
    long long int ID;
    char name[100];
    bool hasvoted;
} voter;
//Candaidates limit
candidate candid_list[6];

//Voters limit
voter voter_list[100];

int candidate_count=0;
int voter_count=0;

//Admin ID and Password
long long int admin_ID=1234;
char admin_password[10]="abc";

bool Loggedin=false;
//Admin side functions
void Admin();
void Admin_Login();
void Entry_candidates();
void candid_list_show();
void Votes_casted();
void Display_Result();
void Add_voters();
void delete_voters();
bool name_input_validation(char *s);

//File handling functions
void candidate_load();
void voter_load();
void candidate_count_updater();
void voter_count_updater();
void voter_list_updater();
void candid_list_updater();

//Main menu function
void MainMenu();

//Voter side function
void castVote();

int main()
{
    //Function to load candidates information from files to the program
    candidate_load();

    //Function to load Voters information from files to the program
    voter_load();

    //Mainn menu
    MainMenu();

    //Function to update candidates count
    candidate_count_updater();

    //Function to update voters count
    voter_count_updater();

    //Function to update the information of the candidates
    candid_list_updater();

    //Function to update the information of the voters
    voter_list_updater();

    return 0;
}

void Admin_Login()
{
    //Function for admin login
    int password_attempts=0;
    long long int ID_input;
        printf("=====================================  Welcome to the Admin Panel  =====================================");
        printf("\n\nKindly enter your ID: ");
        scanf("%lld",&ID_input);

        if(admin_ID!=ID_input)
        {
            printf("\nThis is invalid ID\n");
            return;
        }

        char admin_password_input[10];
        //To count the password attempts
        while(password_attempts<3)
        {
            printf("\nEnter your password: ");
            scanf("%9s",admin_password_input);
            if(strcmp(admin_password,admin_password_input)==0)
            {
                printf("LOGGEDIn\n");
                Loggedin=true;
            }
            else
            {
                printf("\nInvalid Password");
                password_attempts++;
                if(password_attempts==3)
                    {
                        printf("You have reached the password limit (Admin panel in locked)");
                    }
            }

            if(Loggedin==true)
            {
                Admin();
                break;
            }

        }
        return;
}

void Admin()
{
    //The main admin function
    system("cls");
    int password_attempts=0;

    while(true)
    {
        int admin_input;
        printf("==========================================\tEnter your choice for further processing(1-7)\t ========================================");
        printf("\n\n1.Enter Candidate inforamtion\n");
        printf("2.Check total votes casted\n");
        printf("3.Add Voters\n");
        printf("4.Delete Voters\n");
        printf("5.Display Result\n");
        printf("6.Display all candidates\n");
        printf("7.Back to main menu\n");
        printf("==========================================\t=============================================\t ========================================\n");
        printf("Enter your choice here:  ");
        scanf("%d",&admin_input);

        if(admin_input==1)
        {
            Entry_candidates();
        }
        else if(admin_input==2)
        {   
            Votes_casted();
        }
        else if(admin_input==3)
        {
            Add_voters();
        }
        else if(admin_input==4)
        {
            delete_voters();
        }
        else if(admin_input==5)
        {
            Display_Result();
            printf("Press any key to return to the main menu");
            getch();
            MainMenu();
        }
        else if(admin_input==6)
        {
            candid_list_show();
            printf("Press any key to return to the main menu");
            getch();
            MainMenu();
        }
        else if(admin_input==7)
        {
            MainMenu();
        }
        else
        {
            printf("Invalid Input Please try again");
            exit(0);
            return;
        }

    }
}

void Entry_candidates()
{
    //Function to allow the admin add new candidates
    int candid;
    printf("How many Candidates do you want to Add(only enter an integer): ");
    if(scanf("%d",&candid)!=1)
    {
        printf("You didn't enter the right type of input\n");
        while (getchar()!='\n')system("cls");
        return;
    }
    //To check if there is enough space to enter new candidates
    if(candid+candidate_count>6)
    {
        printf("\n\t\t\tYou can't store candidates more than %d as already %d candidates have been registered",6-candidate_count,candidate_count);
        system("cls");
        return;
    }
    //Entering candidates information in the file
    FILE *candidate_infoo;
    candidate_infoo=fopen("Candidate_info.txt","a");

    for(int i=0;i<candid;i++)
    {
        bool duplicate_ID=false;
        printf("Enter ID: ");
        scanf("%lld",&candid_list[candidate_count].ID);
        for(int j=0;j<candidate_count;j++)
        {
            if(candid_list[j].ID==candid_list[candidate_count].ID)
            {
                printf("\nID already exists\n");
                duplicate_ID=true;
            }
        }
        if(duplicate_ID==true)
        {
            i--;
            candid_list[candidate_count].ID=0;
            continue;
        }

        fprintf(candidate_infoo,"%lld ",candid_list[candidate_count].ID);
        printf("Enter name(only first name): ");
        scanf("%30s",candid_list[candidate_count].name);
        if(!name_input_validation(candid_list[candidate_count].name))
        {
            printf("Entered the wrong Name\n");
            candid_list[candidate_count].ID=0;
            i--;
            strcpy(candid_list[candidate_count].name,"");
            continue;
        }

        fprintf(candidate_infoo,"%s ",candid_list[candidate_count].name);
        printf("Enter Party name: ");
        scanf("%s",candid_list[candidate_count].Party_name);
        if(!name_input_validation(candid_list[candidate_count].Party_name))
        {
            printf("Entered the wrong Name\n");
            candid_list[candidate_count].ID=0;
            i--;
            strcpy(candid_list[candidate_count].name,"");
            strcpy(candid_list[candidate_count].Party_name,"");
            continue;
        }

        fprintf(candidate_infoo,"%s",candid_list[candidate_count].Party_name);
        candid_list[candidate_count].votes=0;
        fprintf(candidate_infoo, "%d\n", candid_list[candidate_count].votes);
        printf("\nName %s,Id %lld ,Party %s,votes %d\n",candid_list[candidate_count].name,candid_list[candidate_count].ID,candid_list[candidate_count].Party_name,candid_list[candidate_count].votes);
        candidate_count++;
        candidate_count_updater();
    }

    fclose(candidate_infoo);
    candid_list_show();
    system("cls");
    return;
}
void candid_list_show()
{
    //Function to display the candidates list
    printf("Following are the candidates appearing in the election\n\n");

        for(int i=0;i<candidate_count;i++)
        {
            printf("Name: %-20s| ID: %-20lld| Party: %-20s| Votes: %-4d\n",candid_list[i].name,candid_list[i].ID,candid_list[i].Party_name,candid_list[i].votes);
        }

}
void Votes_casted()
{
    //Function to display the total votes casted
    printf("Following are the total votes casted against each candidate\n");
    printf("Name\t\tParty\t\tID\t\t\tVotes\n");

    for(int i=0;i<candidate_count;i++)
    {
        printf("%s\t\t%s\t\t%lld\t\t%d\n",candid_list[i].name,candid_list[i].Party_name,candid_list[i].ID,candid_list[i].votes);
    }

    printf("\t\t\t\t\tPress any key to exit......");
    char ch;
    ch=getch();
    system("cls");
    return;

}
void Display_Result()
{
    //Function to display results
     int result=0;
    bool tie=false;
     int tie_total[6],total=0;

    for( int i=0;i<candidate_count;i++)
    {
        if(candid_list[i].votes>candid_list[result].votes)
        {
            result=i;
        }
    }

    for(int j=0;j<candidate_count;j++)
    {
        if(result!=j)
        {
            if(candid_list[result].votes==candid_list[j].votes)
            {
                tie=true;
                tie_total[total++]=j;
            }
        }
    }
    //To check tie
    if(tie==true)
    {
        tie_total[total++]=result;
        printf("\t\t\t\t\t\tWe have a tie between\n");
        for(long long int z=0;z<total;z++)
        {
            printf("The  %s from %s with %d Votes\n",candid_list[tie_total[z]].name,candid_list[tie_total[z]].Party_name,candid_list[tie_total[z]].votes);
        }
        return;
    }
    printf("The Winner is %s from %s with %d Votes\n",candid_list[result].name,candid_list[result].Party_name,candid_list[result].votes);
}
void Add_voters()
{
    //Function to add new voters
    int num;
    bool duplicate_ID;
    FILE *voters_list_ptr;
    voters_list_ptr=fopen("voter_info.txt","a");
    printf("How many voters do you want to add(1-100)\n");
    scanf("%d",&num);

    if(voter_count+num>100)
    {
        printf("you can't store voters more than %d as already %d voters have been registered",100-voter_count,voter_count);
        return;
    }

    for(int i=0;i<num;i++)
    {
        duplicate_ID=false;
        printf("Enter the Voter ID: ");
        scanf("%lld",&voter_list[voter_count].ID);
        for(int j=0;j<voter_count;j++)
        {
            if(voter_list[j].ID==voter_list[voter_count].ID)
            {
                printf("\nID already exists\n");
                duplicate_ID=true;
            }
        }
        if(duplicate_ID==true)
        {
            i--;
            voter_list[voter_count].ID=0;
            continue;
        }
        fprintf(voters_list_ptr,"%lld ",voter_list[voter_count].ID);
        printf("Enter the Voter Name(only first name): ");
        scanf("%s",voter_list[voter_count].name);

        if(!name_input_validation(voter_list[voter_count].name))
        {
            printf("Entered the wrong Name\n");
            voter_list[voter_count].ID=0;
            i--;
            strcpy(voter_list[voter_count].name,"");
            continue;
        }
        fprintf(voters_list_ptr,"%s ",voter_list[voter_count].name);
        voter_list[voter_count].hasvoted=false;
        fprintf(voters_list_ptr,"%d\n",voter_list[voter_count].hasvoted);
        printf("ID: %lld Name:%s Hasvoted:%d\n",voter_list[voter_count].ID,voter_list[voter_count].name,voter_list[voter_count].hasvoted);
        voter_count++;
        voter_count_updater();

    }

    fclose(voters_list_ptr);

}
void delete_voters()
{
    //Function to delete voters
    int new_voter_count=0;
    bool voter_found=false;
    long long int ID;
    //Temporary file to hold the data of voters except the voter deleted
    FILE *ptr2=fopen("temp_voter_info.txt","w");
    printf("Enter the ID you want to delete:");
    scanf("%lld",&ID);

    for(int i=0;i<voter_count;i++)
    {
        if(ID!=voter_list[i].ID)
        {
            fprintf(ptr2,"%lld %s %d\n",voter_list[i].ID,voter_list[i].name,voter_list[i].hasvoted);
            new_voter_count++;
        }
        else
        {
            voter_found=true;
        }
    }

    if(!voter_found)
    {
        printf("This voter doesnot exist\nKindly press y to delete any other voter or e to exit the program\n");
        char input;
        input =getch();
        if(input=='y'||input=='Y')
        {
            delete_voters();
        }
        else{
            return;
        }
    }
    //Tp replace the voter_info.txt file with the temporary file
    voter_count=new_voter_count;
    fclose(ptr2);
    remove("voter_info.txt");
    rename("temp_voter_info.txt","voter_info.txt");
    voter_load();
    voter_count_updater();
}
void candidate_load()
{
    //Function to load the candidates information from the file
    FILE *candid_list_ptr;
    candid_list_ptr=fopen("candidate_count.txt","r");
    int a;
    fscanf(candid_list_ptr,"%d",&a);
    fclose(candid_list_ptr);
    candidate_count=a;
    FILE *ptr=fopen("Candidate_info.txt","r");

    for(int i=0;i<candidate_count;i++)
    {
        fscanf(ptr,"%lld",&candid_list[i].ID);
        fscanf(ptr,"%s",candid_list[i].name);
        fscanf(ptr,"%s",candid_list[i].Party_name);
        fscanf(ptr,"%d",&candid_list[i].votes);
    }

    fclose(ptr);

}
void voter_load()
{
    //Function to load the voters information from the file
    FILE *ptr_for_voter_count=fopen("voter_count.txt","r");
    int a;
    fscanf(ptr_for_voter_count,"%d",&a);
    fclose(ptr_for_voter_count);
    voter_count=a;
    FILE *ptr=fopen("voter_info.txt","r");

    for(int i=0;i<voter_count;i++)
    {
        fscanf(ptr,"%lld",&voter_list[i].ID);
        fscanf(ptr, "%s",voter_list[i].name);
        fscanf(ptr,"%d",&voter_list[i].hasvoted);
    }

    fclose(ptr);

}
void candidate_count_updater()
{
    //Function to update the candidates count in the file
    FILE *candid_list_ptr;
    candid_list_ptr=fopen("candidate_count.txt","w");
    fprintf(candid_list_ptr,"%d",candidate_count);
    fclose(candid_list_ptr);
}
void voter_count_updater()
{
    //Function to update the voters count in the file
    FILE *voter_list_ptr;
    voter_list_ptr=fopen("voter_count.txt","w");
    fprintf(voter_list_ptr,"%d",voter_count);
    fclose(voter_list_ptr);
}
void candid_list_updater()
{
    //Function to update the candidates information in the file
    FILE *ptr=fopen("Candidate_info.txt","w");
    for(int i=0;i<candidate_count;i++)
    {
        fprintf(ptr,"%lld ",candid_list[i].ID);
        fprintf(ptr,"%s ",candid_list[i].name);
        fprintf(ptr,"%s ",candid_list[i].Party_name);
        fprintf(ptr,"%d\n",candid_list[i].votes);
    }
    fclose(ptr);
}
void voter_list_updater()
{
    //Function to update the voters information in the file
    FILE *ptr=fopen("voter_info.txt","w");
    for(int i=0;i<voter_count;i++)
    {
        fprintf(ptr,"%lld ",voter_list[i].ID);
        fprintf(ptr,"%s ",voter_list[i].name);
        fprintf(ptr,"%d\n",voter_list[i].hasvoted);
    }
    fclose(ptr);
}
bool name_input_validation(char *s)
{
    //Function for Names input validation
    int flag=0;
    for(int i=0;s[i]!='\0';i++)
    {
        if(isalpha(s[i])==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        return false;
    }
    return true;
}
void MainMenu()
 {
int choice;

system("cls");
    
  printf("\n\n");

    printf("======================================\n");

  printf(" SIMPLE VOTING SYSTEM MENU(Polling station number 1)\n");

    printf("======================================\n");

 printf("1. Admin Login\n");

 printf("2. Voter Panel\n");

    printf("3. View Candidates\n");

   printf("4. Display Results\n");

   printf("5. Exit\n");

   printf("======================================\n");

    printf("Enter your choice (1-5):");

   scanf("%d", &choice);
    
     switch(choice)
     {
     case 1:
     
            Admin_Login();

            break;
            
     case 2:

     castVote();
     printf("Press any key to return to main menu");

     getch();

     MainMenu();
     break;
            
    case 3:

    candid_list_show();

     printf("\nPress any key to return to main menu...");

     getch();

     MainMenu();
     break;

    case 4:
     printf("\t\t\t\t\t\tThese are the Results\n");

     Display_Result();

     printf("\nPress any key to return to main menu...");

     getch();

     MainMenu();
     break;      
    case 5:

     printf("Exiting program. Thank you!\n");
     candid_list_updater();
     voter_list_updater();
     exit(0);
     break;
            
default:
     printf("Invalid choice! Please try again.\n");

        getch();

        MainMenu();
    }
}
void castVote() 
{
    long long int voterID;
    int voter_index = -1;

    printf("\n====================== VOTING PANEL ======================\n");
    printf("Enter your Voter ID: ");
    scanf("%lld", &voterID);

    // Verify Voter by their ID
    for (int i = 0; i < voter_count; i++) 
    {
        if (voter_list[i].ID == voterID) 
        {
            voter_index = i;
            break;
        }
    }

    if (voter_index == -1) 
    {
        printf(" Voter ID not found. Please register first.\n");
        return;
    }

    if (voter_list[voter_index].hasvoted) 
    {
        printf(" You have already voted. Multiple voting is not allowed.\n");
        return;
    }

    printf("\n Welcome %s!\n", voter_list[voter_index].name);
    printf("Here is the list of candidates:\n\n");

    printf("-----------------------------------------------------------\n");
    printf("| Serial |     Name      |        Party         |\n");
    printf("-----------------------------------------------------------\n");
    // Candidate options list
    for (int i = 0; i < candidate_count; i++) 
    {
        printf("|   %2d   | %-13s | %-20s |\n", i, candid_list[i].name, candid_list[i].Party_name);
    }

    printf("-----------------------------------------------------------\n");

    // Cast vote
    int vote_choice;
    printf("Enter the serial number of the candidate you want to vote for: ");
    scanf("%d", &vote_choice);

    if (vote_choice < 0 || vote_choice >= candidate_count) 
    {
        printf(" Invalid choice. Vote not recorded.\n");
        return;
    }

    // Confirm the vote
    char confirm;
    printf("\nYou are voting for: %s (%s)\n", 
           candid_list[vote_choice].name, candid_list[vote_choice].Party_name);
    printf("Are you sure? (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') 
    {
        candid_list[vote_choice].votes++;
        voter_list[voter_index].hasvoted = true;

        printf("\n Vote successfully cast for %s (%s). Thank you, %s!\n",
               candid_list[vote_choice].name,
               candid_list[vote_choice].Party_name,
               voter_list[voter_index].name);
    } 
    else 
    {
        printf("Vote cancelled.\n");
    }

    printf("===========================================================\n");
}