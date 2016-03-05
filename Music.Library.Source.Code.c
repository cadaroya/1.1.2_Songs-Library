/**


Name: 				DAROYA, Carlos Adrian A.
Student #:  		2015-07397
Section:			thwx



Description: 				The attached code is a record keeping program made specifically for recording songs 
							and other music related data. The program works on files and linked list operations
							to dynamically manipulate all song records. 

							During runtime, the program first loads data from a record file into a linked list,
							thus creating a linked list of songs. If a record file is not present, the program 
							creates one. 

							The program has 3 main functionalities namely: (1) Add song, (2) Update song, (3) List
							songs, all of which can be accessed during runtime. 
 
 							In adding songs, the user is asked to input data for the new song. The data will then be added
 							(1) to the linked list by creating new nodes and (2) to the record file by writing on the file.
 							That way, it updates both runtime information and stored information.

 							In updating songs, the program asks for the song to be updated. The user is then asked to
 							update song information. Afterwards, the program first updates information in the linked
 							list. Once updated, it overwrites the whole record file with the updated linked list. In
 							listing songs, the program asks for the mode of printing (by title, by genre, etc.). The
 							linked list will then be sorted accordingly and printed in the program. 
 
 							The above library functionalities can be accessed until the user chooses to end the program.
 							Throughout runtime, the program checks the correctness of user input to prevent crashing
 							issues due to invalid data. Lastly, the program also avoids confusing interface by clearing
 							the screen of unimportant data.

**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>

/* Defines (struct node) type simply as "node" */
typedef struct node node;

/* Struct parameters */
struct node
{
	int songID, rating;
	char title[100], artist[100], composer[100],  album[100], genre[100], remarks[100];
	
	 node *next_node;
	
};

/*Function that clears the screen by printing newlines*/
void clrscr()
{
    int n;
    for (n = 0; n < 10; n++)
      printf( "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" );
}

/*Function that checks if the user had the program's file delimiter '|' in an input*/
int check_invalid(char string[])
{
	int i;
	// Checks every element of the string
	while(string[i])
	{	
		// If '|' is present, the function returns 1 meaning it is an invalid input
		if(strchr("|", string[i]))
			{
				printf("Error. '|' is an invalid input: ");
				return 1;
			}
		i++;
	}
	
	// Else, it returns 0
	return 0;
}

/*Function that prints menu*/
void print_menu()
{
	printf("\nThe Menu:\n"
			"\n1. Add Songs"
			"\n2. Update Songs"
			"\n3. Print Songs"
			"\n0. Exit program\n\n\n\n\n\n\n\n");
}

/*Function that removes extra '\n' in a string*/
void newline_remover(char string[])
{
	if(string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = '\0';
}

/*Function that prints a songlist */
void print_list(node *current)
{
	printf("______________________________________________________________________________\n");
	printf("\n\t\t\t\tLIST OF SONGS\n\n");
	printf("______________________________________________________________________________");
	
	while(current != NULL)
	{
	
		printf("\n\nSongID: %d"
				"\nTitle: %s"
				"\nArtist: %s"
				"\nComposer: %s"
				"\nAlbum: %s"
				"\nGenre: %s"
				"\nRemarks: %s"
				"\nRatings: %d"
				"\n",
		current->songID, current->title, current->artist, current->composer, current->album, 
		current->genre, current->remarks, current->rating);
		
		if(current->next_node)	printf(".   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .   .");
			
			current = current->next_node;
	}
	
	// Success Message to notify user
	printf("______________________________________________________________________________\n");
	char buff[100];
	printf("\n\nScroll up to view. Press enter when you're done reading . . .  ");
	fgets(buff,100, stdin);
	clrscr();
	
}


/* Function that writes data in the node the Linked List */
 node* write_list( node *current,  node *head, char *string, int type)
{	
	// Ensures that the last character in a string is '\0'
	newline_remover(string);
	
	// Switch case that will select where the tokenstring will be saved
	int num;
	switch(type)
	{
		case 1:
			sscanf(string, "%d", &num);
			current->songID = num;
			break;
		case 2:
			strcpy(current->title, string);
			break;
		case 3:
			strcpy(current->artist, string);
			break;
		case 4:
			strcpy(current->composer, string);
			break;
		case 5:
			strcpy(current->album, string);
			break;
		case 6:
			strcpy(current->genre, string);
			break;	
		case 7:
			strcpy(current->remarks, string);
			break;
		case 8:
			sscanf(string, "%d", &num);
			current->rating = num;
			break;
		default:
			printf("\nThis will not appear.");				
	}
	
	return current;
}

/* Function that Parses the String Line read from the file and Creates the new nodes */
 node * parse_create( node *head, char string[])
{
	// Creates the new element for the linked list
	node *current = (node*)malloc(sizeof(node));
	char *token;
	int N = 1;
	
	// Start of Tokenizing Block Code (Parsing)
	token = strtok(string, "|");
	
	while(token!=NULL)
	{
		// The 'N' value dictates which struct variable the token will be saved Into
		// There are 8 structure variables (1-8), so when it reaches 9, it resets to 1.
		
		if(N == 9) N = 1;
		
		// Sends parsed data and the current node to update information in the same node
		current = write_list(current, head, token, N);
		token = strtok(NULL, "|");
		
		N++;
	}
	
	current->next_node = head;
	head = current;

	// Returns the node with complete values
	return head;
}

/* Function that reads the Existing Song list into a Linked List */
node * read_songlist(node *head, int *songID)
{
	// Opens the file for reading
	FILE *fp = fopen("songlist.txt", "a+");
	char buff[1000]; 
	
	// Reads the file per-line using fgets
	while(fgets(buff, 1000, fp))
	{
		// Counts the songID while reading
		// The number of lines correspond to the songID
		
		(*songID)++;					
		
		// Parses the line into significant data while creating structs
		head = parse_create(head,buff); 
	}
	
	fclose(fp);
	
	//Returns the head of the Completed linked list
	return head;
}

/*Function that asks for User input (Add & Update Functions )*/
node *user_input(node * current)
{
	// Variables for input validation
	int flag = 0, n, rating, choice;
	char badc, string[100];
	
	// Input of Title (Can't be empty)
	printf("\n\nTitle: ");
	while(flag == 0)
	{	
		fgets(current->title, 100, stdin);
		
		if(current->title[0] == '\n')
			printf("Error. You MUST input title: ");
			
		else if(check_invalid(current->title) == 1)
			flag = 0;
			
		else 
			flag = 1;
	}
	
	// Input of Artist
	printf("Artist: ");
	fgets(current->artist, 100, stdin);
	while(check_invalid(current->artist) == 1) fgets(current->artist, 100, stdin);
	
	// Input of Composer
	printf("Composer: ");
	fgets(current->composer, 100, stdin);
	while(check_invalid(current->composer) == 1) fgets(current->composer, 100, stdin);
	
	// Input of Album
	printf("Album: ");
	fgets(current->album, 100, stdin);
	while(check_invalid(current->album) == 1) fgets(current->album, 100, stdin);
	
	// Input of Genre, There can only be 3 types of genre as stated
	flag = 0;
	printf("Genre (1-Art, 2-Popular, 3-Traditional): ");
	while(flag == 0)
	{
		fgets(string, 100, stdin);
		newline_remover(string);
		n = sscanf(string, "%d %c", &choice, &badc);
		
		if(n != 1)
			printf("Error. Please choose a number: ");
			
		else if(choice < 1 || choice > 3)
			printf("Error. Please choose a number: ");
			
		else 
			flag = 1;
	}
	
	// The string copied to current->genre depends on the variable choice
	switch(choice)
	{
		case 1: 
			strcpy(current->genre, "Art");
			break;
		case 2:
			strcpy(current->genre, "Popular");
			break;
		case 3:
			strcpy(current->genre, "Traditional");
			break;
		default:
			printf("This would not come out.");
	}
	
	// Input of Remarks
	printf("Remarks: ");
	fgets(current->remarks, 100, stdin);
	while(check_invalid(current->remarks) == 1) fgets(current->remarks, 100, stdin);
	
	// Input of Rating (Can only choose from the range 1-5)
	flag = 0;
	printf("Rating (1-5): ");
	while(flag == 0)
	{
		fgets(string, 100, stdin);
		newline_remover(string);
		n = sscanf(string, "%d %c", &rating, &badc);
		
		if(n != 1)
			printf("Error. Please choose from the range: ");
			
		else if(rating < 1 || rating > 5)
			printf("Error. Please choose from the range: ");
			
		else 
			flag = 1;
	}
	current->rating = rating;
	
	// Removes newline from string inputs
	newline_remover(current->title);
	newline_remover(current->artist);
	newline_remover(current->composer);
	newline_remover(current->album);
	newline_remover(current->genre);
	newline_remover(current->remarks);
	
	// If blanks are entered, It
	if(current->artist[0] == '\0')
		strcpy(current->artist, "<Unknown>");
	if(current->composer[0] == '\0')
		strcpy(current->composer, "<Unknown>");
	if(current->album[0] == '\0')
		strcpy(current->album, "Single");
	if(current->remarks[0] == '\0')
		strcpy(current->remarks, "<N/A>");
	
	// Returns current node with the new values
	return current;
}


/* Function that adds songs: both in structs and in file */
node* add_song( node *head, int songID)
{	
	// File opened for appending to write at the end
	FILE *fp = fopen("songlist.txt", "a");
	
	// Memory Allocation
	node *current = NULL;
	current = ( node*)malloc(sizeof( node));
	
	current->songID = songID; 
	
	// Asking for User Inputs
	current = user_input(current);
	
	// Prints Added songs to the file (Separated by '|' in one line)
	fprintf(fp, "%d|%s|%s|%s|%s|%s|%s|%d\n", current->songID, current->title,current->artist, 
	current->composer, current->album, current->genre, current->remarks, current->rating);
	
	current->next_node = head;
	head = current;
	
	// Success Message to notify user
	clrscr();
	char buff[100];
	printf("\n\nThe song was successfully added. Press enter to continue . . .  ");
	fgets(buff,100, stdin);
	clrscr();
	
	fclose(fp);
	
	return head;
}

/* Function that updates a song */
node * update_song(node *head)
{
	// If the library is initially empty, it will prompt the user and exit updating
	if(head == NULL)
	{
		char buff[100];
		printf("The library is empty. Add songs first. . . Okay?\n"
				"Press Enter to continue . . . ");
		fgets(buff,100, stdin);
		clrscr();
		return NULL;
	}
	
	printf("\n>> Updating Songs >>\n ");
	// If songs exist in the library, it will continue on updating process
	char song[100];
	node *current = head;
	
	// Asking for user input
	printf("\nEnter the title of the song to be updated:  ");
	fgets(song, 100, stdin);
	newline_remover(song);
	
	int count = 0;
	
	// Loop finding the matching data by comparing the user input and the titles
	while(current != NULL)
	{
		if(strcasecmp(current->title, song)==0)
		{
			printf("\n%d -\tTitle: %s\n\tArtist: %s\n\tID : %d", ++count, // count iterates to record number of matches
			current->title, current->artist, current->songID );
		}
		current = current->next_node;
	}
	
	char input[50];
	
	// If there are no matches, it will prompt the user and go back to main menu
	if(count == 0)
	{
		clrscr();
		char buff[100];
		printf("\n\nWhat you're trying to update doesn't exist.\nPress Enter to Continue . . .  ");
		fgets(buff,100, stdin);
		clrscr();
		return head;
	}
	
	
	char string[50], badc;
	int choice, flag = 0, n;
	
	// Asking the user to choose from the list of songs that matched
	printf("\n\nEnter Choice: ");
	while(flag == 0)
		{
			fgets(string, 50, stdin);
			newline_remover(string);
			n = sscanf(string, "%d %c", &choice, &badc);
			
			if(n != 1)
				printf("Error. Please choose from the range: ");
			
			else if(choice < 1 || choice > count)
				printf("Error. Please choose from the range: ");
				
			else 
				flag = 1;
		}
	
	count = 0;
	current = head;
	
	// Saves the head of the current to be updated in newHead
	node *newHead = current;
	
	// Finds the choice of the user by checking the equality of title && the number of choice
	while(current != NULL)
	{
		if(strcasecmp(current->title, song)==0 && choice == ++count)
		{
			// Updating of Data
			clrscr();
			printf("\nUpdating song  . . .");
			current = user_input(current);
		}
		
		current=current->next_node;
	}
	
	current = newHead;
	
	// Overwrites the whole file with the new linked list
	FILE *fp = fopen("songlist.txt", "w");
	
	while(current != NULL)
	{
		// Print the linked list into the file
		
		fprintf(fp, "%d|%s|%s|%s|%s|%s|%s|%d\n", current->songID, current->title,current->artist, 
		current->composer, current->album, current->genre, current->remarks, current->rating);
		
		current = current->next_node;
	}
	
	// Success Message to notify the user
	clrscr();
	char buff[100];
	printf("\n\nUpdating successful. Press enter to continue . . .  ");
	fgets(buff,100, stdin);
	clrscr();
	
	fclose(fp);
	
	// Updates the head in main function
	return newHead;
}

/*Function that swaps the data of two nodes*/
void swap(node  *node1, node *node2)
{
	node *temp = (node *)malloc(sizeof(node));
	temp->songID = node1->songID;
	temp->rating = node1->rating;
	strcpy(temp->title, node1->title);
	strcpy(temp->artist, node1->artist);
	strcpy(temp->composer, node1->composer);
	strcpy(temp->genre, node1->genre);
	strcpy(temp->album, node1->album);
	strcpy(temp->remarks, node1->remarks);
	
	node1->songID = node2->songID;
	node1->rating = node2->rating;
	strcpy(node1->title, node2->title);
	strcpy(node1->artist, node2->artist);
	strcpy(node1->composer, node2->composer);
	strcpy(node1->genre, node2->genre);
	strcpy(node1->album, node2->album);
	strcpy(node1->remarks, node2->remarks);
	
	node2->songID = temp->songID;
	node2->rating = temp->rating;
	strcpy(node2->title, temp->title);
	strcpy(node2->artist, temp->artist);
	strcpy(node2->composer, temp->composer);
	strcpy(node2->genre, temp->genre);
	strcpy(node2->album, temp->album);
	strcpy(node2->remarks, temp->remarks);
}

/*Function the creates the new temporary nodes for search functions*/
node *temp_list(node *current)
{
	node *newcurr = (node *)malloc(sizeof(node));
						
	newcurr->songID = current->songID;
	newcurr->rating = current->rating;
	strcpy(newcurr->title, current->title);
	strcpy(newcurr->artist, current->artist);
	strcpy(newcurr->album, current->album);
	strcpy(newcurr->composer, current->composer);
	strcpy(newcurr->remarks, current->remarks);
	strcpy(newcurr->genre, current->genre);
		
	return newcurr;
}

/*Function that searches for the substring in a song title*/
node * substring_search(node * head)
{
	char substring[50];
	char string[50];
	
	// Asking for user input on substring
	printf("\nEnter a substring to be searched: ");
	fgets(substring, 50, stdin);
	newline_remover(substring);
	
	// Declaration of check
	int check = strlen(substring);
	
	int i,j, count;
	
	node *newcurr = NULL, *newhead = NULL, *current = head;

	// Creates a new linked list exclusively for songs containing the substring
	while(current)
	{
		// "string" is every current->title in the list, and it will be checked if corresponding with the substring
		strcpy(string, current->title);
		toupper(string); 
		int len = strlen(string);
		
		for(i=0;i<len;i++)
		{	
			count = 0;
			
			// If string element i correponds with substring[0], it will enter the checking loop
			string[i] = toupper(string[i]); substring[0] = toupper(substring[0]);
			
			if(string[i] == substring[0])
			{
				for(j=i;count<check;j++)
				{
			
					// If the element still correponds, count will continue iterating
					string[j] = toupper(string[j]); substring[count] = toupper(substring[count]);
					if(string[j] == substring[count])
						count++;
				
					// Else, the loop breaks
					else
						break;
					
					// if count completes the check value, the substring linked list is made
					if(count == check)
					{	
						newcurr = temp_list(current);
					
						newcurr->next_node = newhead;
						newhead = newcurr;
					}
				}
				
				// It breaks the for loop to move on quickly
				break;
			}
		}
		current = current->next_node;
	}
	
	// If newhead is still NULL, there are no matches with the substring
	if(newhead == NULL)
	{
		return NULL;
	}
	
	else
	return newhead;
}

/*Functions that Creates a Linked List of songs under a specific Artist (To be sorted)*/
node *artist_search(node * head)
{
	char string[50];
	
	// Asking for user input on Artist name
	printf("\nEnter the Artist name: ");
	fgets(string, 50, stdin);
	newline_remover(string);
	
	node *newcurr = NULL, *newhead = NULL, *current = head;
	
	// Finds all the songs same with user input
	while(current)
	{
		if(strcasecmp(current->artist, string) == 0)
		{
			newcurr = temp_list(current);
					
			newcurr->next_node = newhead;
			newhead = newcurr;
		}
		
		current = current->next_node;
	}
	
	return newhead;
}

/*Functions that Creates a Linked List of songs under a specific Composer (To be sorted)*/
node *composer_search(node * head)
{
	char string[50];
	
	// Asking for user input on Composer
	printf("\nEnter the Composer: ");
	fgets(string, 50, stdin);
	newline_remover(string);
	
	node *newcurr = NULL, *newhead = NULL, *current = head;
	
	// Finds all the songs same with user input
	while(current)
	{
		if(strcasecmp(current->composer, string) == 0)
		{
			newcurr = temp_list(current);
					
			newcurr->next_node = newhead;
			newhead = newcurr;
		}
		
		current = current->next_node;
	}
	
	return newhead;
}

/*Functions that Creates a Linked List of songs under a specific Genre (To be sorted)*/
node *genre_search(node * head)
{
	char string[50], badc;
	int flag = 0, n, choice;
	
	// Asking for user input on Genre
	printf("Which song genre will be printed? (1-Art, 2-Popular, 3-Traditional): ");
	while(flag == 0)
	{
		fgets(string, 50, stdin);
		newline_remover(string);
		n = sscanf(string, "%d %c", &choice, &badc);
		
		if(n != 1)
			printf("Error. Please choose a number: ");
			
		else if(choice < 1 || choice > 3)
			printf("Error. Please choose a number: ");
			
		else 
			flag = 1;
	}
	
	switch(choice)
	{
		case 1: 
			strcpy(string, "Art");
			break;
		case 2:
			strcpy(string, "Popular");
			break;
		case 3:
			strcpy(string, "Traditional");
			break;
		default:
			strcpy(string, "Unknown");
			
	}
	node *newcurr = NULL, *newhead = NULL, *current = head;
	
	// Finds all the songs same with user input
	while(current)
	{
		if(strcasecmp(current->genre, string) == 0)
		{
			newcurr = temp_list(current);
					
			newcurr->next_node = newhead;
			newhead = newcurr;
		}
		
		current = current->next_node;
	}
	
	return newhead;
}

/*Functions that Creates a Linked List of songs under a specific Album (To be sorted)*/
node *album_search(node * head)
{
	char string[50];
	
	// Asking for user input on Album
	printf("\nEnter the Album: ");
	fgets(string, 50, stdin);
	newline_remover(string);
	
	node *newcurr = NULL, *newhead = NULL, *current = head;
	
	// Finds all the songs same with user input
	while(current)
	{
		if(strcasecmp(current->album, string) == 0)
		{
			newcurr = temp_list(current);
					
			newcurr->next_node = newhead;
			newhead = newcurr;
		}
		
		current = current->next_node;
	}
	
	return newhead;
}

/*Functions that Creates a Linked List of songs with ratings asked by the user (To be sorted)*/
node *ratings_search(node * head)
{
	char string[50], badc;
	int rating, flag = 0, n;
	
	printf("\nEnter the Rating (1-5): ");
	// Asking for user input on Ratings
	while(flag == 0)
		{
			fgets(string, 50, stdin);
			newline_remover(string);
			n = sscanf(string, "%d %c", &rating, &badc);
			
			if(n != 1)
				printf("Error. Please choose from the range: ");
			
			else if(rating < 1 || rating > 5)
				printf("Error. Please choose from the range: ");
				
			else 
				flag = 1;
		}
	
	node *newcurr = NULL, *newhead = NULL, *current = head;
	
	// Finds all the songs with ratings above
	while(current)
	{
		if(rating <= current->rating)
		{
			newcurr = temp_list(current);
					
			newcurr->next_node = newhead;
			newhead = newcurr;
		}
		
		current = current->next_node;
	}
	
	return newhead;
}

/* Functions that sorts by Rating (Primary), Title (Secondary) and Artist (Tertiary)*/
void sort_rating(node *newhead)
{
	// If there are no matches from the search functions, it will prompt the user and go back to main menu
	if(newhead == NULL)
	{	
		clrscr();
		char buff[100];
		printf("\n\nWhat you searched for is not in the library.\nPress Enter to Continue . . .  ");
		fgets(buff,100, stdin);
		clrscr();
		return;
	}
	
	node *newcurr = newhead, *up;
	
	// Bubble Sort Algorithm, Swapping data
	while(newcurr->next_node)
	{
		for(up=newcurr->next_node; up !=NULL ;up=up->next_node)
		{
			
			if(newcurr->rating < up->rating)
			{
				// If the current rating is less than the next node's rating, it will swap data
				swap(newcurr, up);
			}
			
			else if(newcurr->rating == up->rating)
			{
				// If the ratings are the same, it will sort be title
				if(strcasecmp(newcurr->title, up->title)>0)
				{
					swap(newcurr,up);
				}
				
				// If the titles are the same, it will sort by artist
				else if(strcasecmp(newcurr->title,up->title)==0)
				{
					if(strcasecmp(newcurr->artist, up->artist)>0)
					{
						swap(newcurr,up);
					}
				}
			}
		}
		
		newcurr = newcurr->next_node;
	}
	
	// Prints the sorted list
	clrscr();
	print_list(newhead);
	return;
}


/* Functions that sorts by Title (Primary) and Artist (Secondary)*/
void sort_title(node *newhead)
{
	
	// If there are no matches from the search functions, it will prompt the user and go back to main menu
	if(newhead == NULL)
	{
		clrscr();
		char buff[100];
		printf("\n\nWhat you searched for is not in the library.\nPress Enter to Continue . . .  ");
		fgets(buff,100, stdin);
		return;
	}
	
	node *newcurr = newhead, *up;
	
	// Bubble Sort Algorithm, Swapping data
	while(newcurr->next_node)
	{
		for(up=newcurr->next_node; up !=NULL ;up=up->next_node)
		{
			if(strcasecmp(newcurr->title, up->title)>0)
			{
				// If the ratings are the same, it will sort be title
				swap(newcurr, up);
			}
			
			else if(strcasecmp(newcurr->title,up->title)==0)
			{
				// If the titles are the same, it will sort by artist
				if(strcasecmp(newcurr->artist, up->artist)>0)
				{	
					
					swap(newcurr,up);
				}
			}
		}
		
		newcurr = newcurr->next_node;
	}
	
	// Prints the sorted list
	clrscr();
	print_list(newhead);
	return;
}

/*Function that prompts the user for the mode of printing the song list*/
node * print_mode(node *head, int max)
{	

	// If the library is initially empty, it will prompt the user and exit updating
	clrscr();
	if(head == NULL)
	{
		char buff[100];
		printf("The library is empty. Add songs first. . . Okay?\n"
				"Press Enter to continue . . . ");
		fgets(buff,100, stdin);
		clrscr();
		return;
	}
	
	// Else, it will continue
	char input[50], badc;
	int choice, flag = 0, n;
	
	printf("______________________________________________________________________________\n");
	printf("\n\t\t\tChoose a Printing Mode\n\n");
	printf("______________________________________________________________________________");
	printf("\n\n\n\nHow would you like to print the songs?\n"
			"\n1. By title"
			"\n2. By artist"
			"\n3. By composer"
			"\n4. By genre"
			"\n5. By album"
			"\n6. By rating"
			"\n7. Print The Entire library"
			"\n0. Return to main menu"
			"\n\n\n\nPlease choose a number: ");
		
	// Asking for user's choice from the menu (Cannot be 8 or 9)
	while(flag == 0)
		{
			fgets(input, 100, stdin);
			newline_remover(input);
			n = sscanf(input, "%d %c", &choice, &badc);
			
			if(n != 1)
				printf("Error. Input only numbers from the menu: ");
			
			else if(choice == 8 || choice == 9)
				printf("Error. Input only numbers from the menu: ");
				
			else 
				flag = 1;
		}
	
	node *newhead = NULL;
	
	// The songs are sorted depending on the user's choice
	switch(choice)
		{
		case 1: // Print By Title
			newhead = substring_search(head);
			sort_title(newhead);
			break;
		case 2: // Print By Artist
			newhead = artist_search(head);
			sort_title(newhead);
			break;
		case 3: // Print By Composer
			newhead = composer_search(head);
			sort_title(newhead);
			break;
		case 4: // Print By Genre
			newhead = genre_search(head);
			sort_title(newhead);
			break;
		case 5: // Print By Album
			newhead = album_search(head);
			sort_title(newhead);
			break;
		case 6: // Print By Rating
			newhead = ratings_search(head);
			sort_rating(newhead);
			break;
		case 7: // Print By All
			sort_title(head);
			break;
		case 0:
			printf("\n>> Ending Program >>\n\n");
			return 0;
		default:
			printf("This won't come out");
		}
		

}

/* Function that prints header */
void printables()
{
	printf("\n______________________________________________________________________________\n");
	printf("\n\t\t\t<< Music Library of Carlos >>\n\n");
	printf("______________________________________________________________________________"
			"\n\n\n");
}

int main()
{	
	node *head = NULL;
	int songID = 0;
	
	// This Loads the Library saved in the file and counts songID
	head = read_songlist(head, &songID); 
	
	while(1)
	{	
		char string[100], badc;
		int choice, flag = 0, n;
		printables();
		print_menu();
		printf("\nWhat do you wish to do now? ");
		
		// Input Validation of User Input
		while(flag == 0)
		{
			fgets(string, 100, stdin);
			newline_remover(string);
			n = sscanf(string, "%d %c", &choice, &badc);
			
			if(n != 1)
				printf("Error. Input only numbers from the menu: ");
			
			else if(choice != 1 && choice != 2 && choice != 3 && choice != 0)
				printf("Error. Input only numbers from the menu: ");
				
			else 
				flag = 1;
		}
		
		// Library Function is done depending on the user's choice
		switch(choice)
		{
		case 1: // Add songs
			clrscr();
			printf("\n\n>> Adding Songs >>\n");
			head = add_song(head, songID++);
			break;
		case 2: // Update Songs
			clrscr();
			head = update_song(head);
			break;
		case 3: // Print Song List
			clrscr();
			print_mode(head, songID);
			break;
		case 0: // Exits Program
			printf("\n>> Ending Program >>\n\n");
			return 0;
		default:
			printf("This won't come out. Just for formalities's sake");
		}
	}
}
