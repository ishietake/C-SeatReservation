#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Declaring reservation as a structure
struct reservation
{
    char client[50];
    char location[50];
    int age;

    int row; 
    char col;
};

FILE *ptr;

// Creating an array of structures to display the available seats
char systemseat[10][6] = {{' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '},
                          {' ', ' ', ' ', ' ', ' ', ' '}};

// Declaration of functions to be used
void input();
int conversion(char B);
int available(int A, int B);
void printsystem();
void displaytraveler();
void alter();
int leave();

void main()
{
	// Using process() function that partakes in the void main()
    ptr = fopen("information.dat", "rb");
    struct reservation process;
    while(fread(&process, sizeof(struct reservation), 1, ptr)) systemseat[process.row - 1][conversion(process.col) - 1] = 'X';  
    fclose(ptr);
	
	// Interface of Main Menu that is in void main(), allowing the users to choose what they want to do
    int user = 1;
    while (user != 0)
    {
        printf("\n");
		printf("---------------------------------------------------------------------------------------\n");
		printf("\t    Greetings! Welcome to TechnoClub Airlines, our Dear Passengers!\n");
		printf("---------------------------------------------------------------------------------------\n");
        printf("\n");
        printf("\t\t\t\t\t   - - -");
        printf("\n");
        
        printf("\n");
        printf("   This is an online seat reservation system. We're hoping to assist you well here.\n");
        printf("_______________________________________________________________________________________\n");
        
		printf("\n");
        
        // Options of the Main Menu
        printf("\t\t\t\t\tMain Menu\n\n");
		printf("\t\t\tPress 1 to generate a new reservation seat.\n");
        printf("\t\t\tPress 2 to change reservation seat.\n");
        printf("\t\t\tPress 3 to view system's seats.\n");
        printf("\t\t\tPress 4 to present all of the reserved clients.\n");
		printf("\n\t\t\t\t\tPress 0 to exit.\n\n\n");
		
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
		
        printf("\n\nWhat is your choice?  ");
		scanf("%d", &user);
        
        // Creating a switch cases to call the respected functions
        switch(user)
        {
            case 1:
            {
                input();
                printf("\n");
                printf("\n");
                system("pause");
                break;
            }
            
            case 2:
            {
                alter();
                printf("\n");
                printf("\n");
                system("pause");
                break;
            }
            
            case 3:
            {
                printsystem();
                printf("\n");
                printf("\n");
                system("pause");
                break;
            }
            
            case 4:
            {
                displaytraveler();
                printf("\n");
                printf("\n");
                system("pause");
                break;
            }
            
            case 0:
            {
                leave();
                break;
            }
            
            default:
            {
               printf("\nInvalid choice! Please enter only the number shown on the Main Menu.\n");
               printf("\n");
               printf("\n");
               system("pause");
               break;
            }
        }
    }
}

void input()
{
    system("cls");
    printf("---------------------------------------------------------------------------------------\n");
	printf("\t\t\t   TechnoClub Airlines: Seat Reservation\n");
	printf("---------------------------------------------------------------------------------------\n\n");
    
	struct reservation input;

    // Letting the users input their data needed in the code
    printf("For our new passenger, kindly fill out the information needed below. Thank you!\n\n");
    printf("\tName: ");
    scanf(" %[^\n]s", &input.client);

    printf("\tAge: ");
    scanf("%d", &input.age);

    printf("\tCity: ");
    scanf(" %[^\n]s", &input.location);

    // Scanning the rows and columns in one input
    printf("\nRow: (1-10) | Column: (A-F)\n");
    printf("Please choose a seat (example - 1A): ");
    scanf("%d", &input.row);
    scanf(" %c", &input.col);

    // Inspecting the seats: taken or not
    if (available(input.row, conversion(input.col)) == 1)
    {
        printf("\nThe seat is already taken! Back to main menu.\n\n");
        return;
    }
    
    else
    {
        // The seat has been recognized for the new passenger
        systemseat[input.row - 1][conversion(input.col) - 1] = 'X';

        ptr = fopen("information.dat", "ab");

        fwrite(&input, sizeof(struct reservation), 1, ptr);
        fclose(ptr);

        printf("\nSeat has been reserved. Thank you for choosing TechnoClub Airlines!\n");
        printf("______________________________________________________________________\n");
    }
}

void alter()
{
    system("cls");

    int A; char B;

    // Asking the row and column of the seat to find
    printf("---------------------------------------------------------------------------------------\n");
	printf("\t\t\tTechnoClub Airlines: Changing Seat Reservation\n");
	printf("---------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t\tRow: (1-10) | Column: (A-F)\n\n");
    printf("What seat do you want to change? ");
    scanf("%d", &A);
    scanf(" %c", &B);
    B = toupper(B);
    
    struct reservation alter;

    // Inspecting the seats: taken or not
    if (available(A, conversion(B)) == 1)
    {
        // Continuing the load when the seat is taken
        ptr = fopen("information.dat", "rb");
        while (fread(&alter, sizeof(struct reservation), 1, ptr))
        {
            alter.col = toupper(alter.col);
            if (alter.row == A && alter.col == B)
            {
                // Printing the previous seat
                printf("\n");
				printf("---------------------------------------------------------------------------------------\n");
                printf("%-35s%-5d%-25s%d%c\n", alter.client, alter.age, alter.location, alter.row, alter.col);
                printf("---------------------------------------------------------------------------------------\n");
                break;
            }
        }
        fclose(ptr);
        
        // Letting the users input new desired seat
        printf("\nWhere do you want to place a new seat? (example - 1A): ");
        scanf("%d", &alter.row);
        scanf(" %c", &alter.col);

        // Marking and unmarking the seat with 'X' and ' '
        systemseat[A - 1][conversion(B) - 1] = ' ';
        systemseat[alter.row - 1][conversion(alter.col) - 1] = 'X';
        
        FILE *temp;
        ptr = fopen("information.dat", "rb");
        temp = fopen("temp.dat", "wb");

        struct reservation process;

        while (fread(&process, sizeof(struct reservation), 1, ptr))
        {
            process.col = toupper(process.col);

            if (process.row == A && process.col == B)
            {
                fwrite(&alter, sizeof(struct reservation), 1, temp);
                continue;
            }

            fwrite(&process, sizeof(struct reservation), 1, temp);
        }
        fclose(ptr);
        fclose(temp);
        
        remove("information.dat");
        rename("temp.dat", "information.dat");

        printf("\n\nChanges have been saved. Have a safe trip!\n");
    }
    else printf("\n\nThe seat is still available. Anyways, have a safe trip!\n");
}

void displaytraveler()
{
    // Print all the informations of the client
	system("cls");
	printf("---------------------------------------------------------------------------------------\n");
	printf("\t\t   TechnoClub Airlines: Information of Passengers\n");
	printf("---------------------------------------------------------------------------------------\n\n");
	
	printf("\n");
	printf("|NAME\t\t\t\t |AGE   |CITY\t\t\t|SEAT NUMBER\n");
	printf("\n");
	
    ptr = fopen("information.dat", "rb");
    struct reservation traveler;
    while(fread(&traveler, sizeof(struct reservation), 1, ptr))
		printf("%-35s%-5d%-25s%d%c\n", traveler.client, traveler.age, traveler.location, traveler.row, traveler.col);
    fclose(ptr);
}

//Conversion of columns to make it integers
int conversion(char B)
{
    B = tolower(B);
    switch (B)
    {
        case 'a':
            return 1;
        case 'b':
            return 2;
        case 'c':
            return 3;
        case 'd':
            return 4;
        case 'e':
            return 5;
        case 'f':
            return 6;
        default:
            return 0;
    }
}

// Inspecting if the seat is still available
int available(int A, int B)
{
    if (systemseat[A-1][B-1] == 'X')
        return 1;
    return 0;
}

// Print the whole seat reservation system
void printsystem()
{	

int i, j;

    system("cls");
    printf("---------------------------------------------------------------------------------------\n");
	printf("\t\t\tTechnoClub Airlines: Seat Blocking\n");
	printf("---------------------------------------------------------------------------------------\n\n");
    printf("\tA\tB\tC\tD\tE\tF\n");
    for (i = 0; i < 10; i++)
    {
        printf("%d", i+1);
        for (j = 0; j < 6; j++)
            printf("\t%c", systemseat[i][j]);
        printf("\n");
    }
}

// Returning the program that saves everything in the savedfile.txt
int leave()
{
    FILE *savedfile;

    ptr = fopen("information.dat", "rb");
    savedfile = fopen("savedfile.txt", "wb");

    struct reservation log;
    while(fread(&log, sizeof(struct reservation), 1, ptr))
    {
        fprintf(savedfile, "%-35s%-5d%-25s%d%c\n", log.client, log.age, log.location, log.row, log.col);
    }

    fclose(savedfile);
    fclose(ptr);
    return 0;
}
