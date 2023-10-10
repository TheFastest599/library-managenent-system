// C program for the above approach
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

// Structure to store books
struct Books
{
	char bid[7];
	char title[100];
	char author[100];
	char category[30];
	int quantity;
};

struct node
{
	struct Books book;
	struct node *next;
};

struct node *head;
struct node *current = NULL;
struct node *previous = NULL;
struct node *p;

int choice;
bool loop;
char ans;
char id[7];

char *category[] = {"Arts", "Autobiography", "Biography", "Bussiness", "Economics", "Education", "Fantasy", "Fiction", "Health", "History", "Law", "Management", "Novel", "Personal Development", "Philosophy", "Photography", "SPACE", "Story"};

void loadData();
void printData(struct node *head);
void line();
void controlLoop();
void clearInputBuffer();
void idGenerator(char *id, char category[]);
void writeInFile();

// Driver Code
int main()
{
	loop = true;
	int quantity;
	char bid[7];
	bool bookFound = false;
	while (loop)
	{
		printf("----------------------------------------LIBRARY MANAGEMENT SYSTEM----------------------------------------\n");
		loadData();
		printf("\nPlease select one of the options-\n");
		printf("1. Borrow Book\n");
		printf("2. Return Book\n");
		printf("3. Add Book\n");
		printf("4. Delete Book\n");
		printf("5. Display Books\n");
		printf("6. Exit\n");
		printf("-> ");
		scanf("%d", &choice);
		printf("\n \n");
		switch (choice)
		{
		case 1:
			// To borrow Book.
			bookFound = false;
			quantity = 0;
			printf("-------------------BORROW BOOKS------------------\n");
			printf("Enter the Book ID - ");
			scanf("%s", bid);
			for (p = head; p->next != NULL; p = p->next)
			{
				if (strcmp(p->book.bid, bid) == 0)
				{
					bookFound = true;
					break;
				}
			}
			if (bookFound)
			{
				printf("Book found--\n");
				line();
				printf("\n|%-8s| %-45s| %-30s| %-25s| %-10s|\n", "bid", "title", "author", "category", "quantity");
				line();
				printf("\n|%-8s| %-45s| %-30s| %-25s| %-10d|\n", p->book.bid, p->book.title, p->book.author, p->book.category, p->book.quantity);
				line();
				printf("\n");
				if (p->book.quantity == 0)
				{
					printf("Sorry requested book not available.\n");
				}
				else
				{
					printf("Enter quantuty - ");
					scanf("%d", &quantity);
					if (quantity > p->book.quantity)
					{
						printf("Sorry wrong quantity.Please try again.\n");
					}
					else
					{
						p->book.quantity = p->book.quantity - quantity; // Reduce book.
						writeInFile();
						printf("Thanks for borrowing and please visit us again!!\n");
						// printf("You borrowed %d books of - %s by - %s .\n", quantity, p->book.title, p->book.author);
					}
				}
			}
			else
			{
				printf("Book not found!!\n");
			}
			controlLoop();
			break;
		case 2:
			// To return Book.
			bookFound = false;
			quantity = 0;
			printf("-------------------RETURN BOOKS------------------\n");
			printf("Enter the Book ID - ");
			scanf("%s", bid);
			for (p = head; p->next != NULL; p = p->next)
			{
				if (strcmp(p->book.bid, bid) == 0)
				{
					bookFound = true;
					break;
				}
			}
			if (bookFound)
			{
				printf("Book found--\n");
				line();
				printf("\n|%-8s| %-45s| %-30s| %-25s| %-10s|\n", "bid", "title", "author", "category", "quantity");
				line();
				printf("\n|%-8s| %-45s| %-30s| %-25s| %-10d|\n", p->book.bid, p->book.title, p->book.author, p->book.category, p->book.quantity);
				line();
				printf("\n");
				if (p->book.quantity == 0)
				{
					printf("Sorry requested book not available.\n");
				}
				else
				{
					printf("Enter quantity - ");
					scanf("%d", &quantity);
					p->book.quantity = p->book.quantity + quantity; // Return  book.
					writeInFile();
					printf("Thanks for returning and please visit us again!!\n");
					// printf("You returned %d books of - %s by - %s .\n", quantity, p->book.title, p->book.author);
				}
			}
			else
			{
				printf("Book not found!!\n");
			}
			controlLoop();
			break;
		case 3:
			printf("---------------ADDITION OF BOOKS TO INVENTORY------------------\n");
			int catSelect; // Takes input for category
			char title[46];
			char author[31];
			char name[20];
			printf("Pick one of the category : \n");
			for (int i = 0; i < 18; i++)
			{
				printf("%d. %s\n", i + 1, category[i]);
			}
			printf("-> ");
			scanf("%d", &catSelect);
			clearInputBuffer();
			printf("------------------------------------------------------------------\n");
			int idResult = 0;
			struct node *s;
			do
			{
				idGenerator(id, category[catSelect - 1]); // Generates new ID
				for (s = head; s != NULL; s = s->next)
				{
					idResult = strcmp(id, s->book.bid);
				}
			} while (idResult == 0); // To prevent duplication of id
			printf("BID - %s\n", id);
			printf("Category - %s\n", category[catSelect - 1]);
			printf("Enter the following - \n");
			printf("Title - ");
			scanf("%[^\n]%*c", title);
			printf("Author - ");
			scanf("%[^\n]%*c", author);
			printf("Quantity - ");
			scanf("%d", &quantity);
			struct node *addEntry; // Creation of roots
			addEntry = malloc(sizeof(struct node));
			addEntry->next = NULL;
			strcpy(addEntry->book.author, author);
			strcpy(addEntry->book.bid, id);
			strcpy(addEntry->book.category, category[catSelect - 1]);
			strcpy(addEntry->book.title, title);
			addEntry->book.quantity = quantity; // Filling of details
			if (head == NULL || strcmp(head->book.category, category[catSelect - 1]) > 0)
			{
				// Insert at the beginning
				addEntry->next = head;
				head = addEntry;
			}
			else
			{
				// Find the appropriate position to insert
				for (current = head; current->next != NULL && strcmp(current->next->book.category, category[catSelect - 1]) <= 0; current = current->next)
					;
				addEntry->next = current->next;
				current->next = addEntry;
			} // Traversing to required position - 1 and entering data
			writeInFile();
			printf("--------------------------------------New Book Entry Successfull!!------------------------------------------------\n");
			controlLoop();
			break;
		case 4:
			// To delete Book.
			bookFound = false;
			quantity = 0;
			printf("-------------------DELETE BOOKS------------------\n");
			printf("Enter the Book ID - ");
			scanf("%s", bid);
			for (p = head; p->next != NULL; p = p->next)
			{
				if (strcmp(p->book.bid, bid) == 0)
				{
					bookFound = true;
					break;
				}
				else
				{
					previous = p;
				}
			}
			if (bookFound)
			{
				printf("Book found--\n");
				line();
				printf("\n|%-8s| %-45s| %-30s| %-25s| %-10s|\n", "bid", "title", "author", "category", "quantity");
				line();
				printf("\n|%-8s| %-45s| %-30s| %-25s| %-10d|\n", p->book.bid, p->book.title, p->book.author, p->book.category, p->book.quantity);
				line();
				printf("\n");
				if (p->book.quantity == 0)
				{
					printf("Sorry requested book not available.\n");
				}
				else
				{
					char bookName[100];
					char ansd;
					strcpy(bookName, p->book.title);
					printf("Want to delete BOOK '%s' for sure? (Y/N) : ", p->book.title);
					clearInputBuffer();
					scanf("%c", &ansd);
					if (ansd == 'y' || ansd == 'Y')
					{
						previous->next = p->next; // For deletion
						free(p);
						writeInFile();
						printf("Book '%s' successfully deleted!\n", bookName);
					}
					else if (ansd == 'n' || ansd == 'n')
					{
						printf("Book '%s' not deleted.\n", p->book.title);
					}
				}
			}
			else
			{
				printf("Book not found!!\n");
			}
			controlLoop();
			break;
		case 5:
			printf("--------------------TABLE OF AVAILABLE BOOKS------------------------\n");
			printData(head); // Print table of book data.
			controlLoop();
			break;
		case 6:
			loop = false;
			break;
		default:
			break;
		}
	}
	return 0;
}

void loadData()
{
	int row = 0;
	int column = 0;
	int count = 0;
	// Open csv to read data
	FILE *fp = fopen("Books_data.csv", "r");

	if (!fp)
		printf("Can't open file\n");

	else
	{
		// Here we have taken size of
		char buffer[100];

		while (fgets(buffer, 99, fp))
		{
			column = 0;						   // Resets column counter
			char *token = strtok(buffer, ","); // Splits the string with ","
			if (row >= 1)
			{
				current = malloc(sizeof(struct node));
				if (row == 1)
				{
					head = current;
				}
				else if (row > 1)
				{
					previous->next = current;
				}
				current->next = NULL;
			} // setting linked list
			while (token != NULL)
			{
				if (row >= 1)
				{
					switch (column)
					{
					case 0:
						strcpy(current->book.bid, token);
						break;
					case 1:
						strcpy(current->book.title, token);
						break;
					case 2:
						strcpy(current->book.author, token);
						break;
					case 3:
						strcpy(current->book.category, token);
						break;
					case 4:
						current->book.quantity = atoi(token);
						break;

					default:
						break;
					}
				}
				token = strtok(NULL, ",");
				column++; // column counter
			}
			row++;				// Row counter
			previous = current; // sets the current node to previous
		}
		// Close the file
		fclose(fp);
	}
}

void line()
{
	for (int i = 1; i <= 128; i++)
	{
		printf("%s", "-");
	}
}

void printData(struct node *head)
{
	line();
	printf("\n|%-8s| %-45s| %-30s| %-25s| %-10s|\n", "bid", "title", "author", "category", "quantity");
	line();
	for (p = head; p != NULL; p = p->next)
	{
		printf("\n|%-8s| %-45s| %-30s| %-25s| %-10d|\n", p->book.bid, p->book.title, p->book.author, p->book.category, p->book.quantity);
		line();
	}
}

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
		// Keep reading characters until a newline or EOF is encountered
	}
}

void controlLoop()
{
	printf("\n\nRun again? (Y/N) : ");
	clearInputBuffer();
	scanf("%c", &ans);
	if (ans == 'y' || ans == 'Y')
	{
		loop = true;
	}
	else
	{
		loop = false;
	}
}

void idGenerator(char *id, char category[]) // ID generator.
{
	int lower = 0, upper = 999, num, j = 0;
	char snum[4], word[4], ch;
	srand(time(0));
	for (int i = 0; i < 1; i++)
	{
		num = (rand() %
			   (upper - lower + 1)) +
			  lower;
	} // creates a random number in the range 0-999
	for (int i = 0; i < 3; i++)
	{
		word[i] = category[i];
	} // takes first three letters of category
	word[3] = '\0';
	sprintf(snum, "%03d", num); // converts number to string
	while (word[j])
	{
		ch = word[j];
		word[j] = toupper(ch);
		j++;
	} // converts the 3 letters to uppercase
	strcpy(id, word);
	strcat(id, snum); // concatinates the letters and numbers to make ID.
}

void writeInFile()
{
	FILE *fp = fopen("Books_data.csv", "w");
	fprintf(fp, "bid,title,author,category,quantity\n");
	for (p = head; p != NULL; p = p->next)
	{
		fprintf(fp, "%s,%s,%s,%s,%d\n", p->book.bid, p->book.title, p->book.author, p->book.category, p->book.quantity);
	}
	fclose(fp);
}
