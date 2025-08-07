//Anastasis Drougas.
//it2024023.
#include<stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <string.h>
#include "books.h"


void clear_input_buffer()//Cleans scanf buffer after user input.
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


void clear_screen(){system("clear");}//Function that clears user's screen.


int integer_validation()//Function that returns a valid integer provided by the user.
{
    int input=0;
    do
    {
        if((scanf("%d",&input)!= 1))
        {
            printf(" \033[31mInvalid input, please try again:\033[0m ");
            while(getchar()!= '\n');//Empty scanf buffer.
        }else{break;}
    }while(1);
    return input;    
}


int ISBNsearch (book_node *head,char ISBN[])//Returns if the ISBN code already exists in the list.
{
    book_node *curr=head;
    while(curr!=NULL)
    {
        if (strcmp(curr->ISBN,ISBN) == 0) {return 1;}  
        curr=curr->next;
    }
    return 0;
}


book_node *create_entry_node()//Node creation function.
{
    //Temporary, the user provides the following info and then we create the new node.
    char title_temp[STRING_SIZE];
    char authors_temp[STRING_SIZE];
    char publisher_temp[STRING_SIZE];
    int year_temp;
    char ISBN_temp[20];
    
    //USER INPUTS.
    printf("Please provide the following information about the new entry:\n\n");
    printf("Title: ");
    fgets(title_temp,sizeof(title_temp),stdin);
    title_temp[strcspn(title_temp,"\n")]= '\0';
    printf("Author(s): ");
    fgets(authors_temp,sizeof(authors_temp),stdin);
    authors_temp[strcspn(authors_temp,"\n")]= '\0';
    printf("Publisher: ");
    fgets(publisher_temp,sizeof(publisher_temp),stdin);
    publisher_temp[strcspn(publisher_temp,"\n")]= '\0';
    printf("Year of release: ");
    year_temp=integer_validation();
    printf("ISBN: ");
    clear_input_buffer();
    fgets(ISBN_temp,sizeof(ISBN_temp),stdin);
    ISBN_temp[strcspn(ISBN_temp,"\n")]= '\0';
    
    book_node *new_node =(book_node*)malloc(sizeof(book_node));//Create the new node, memory allocation.
    if(new_node == NULL){perror("Memory allocation failed\n");exit(EXIT_FAILURE);}

    //Copy everything to our new node.
    strcpy(new_node->title,title_temp);
    strcpy(new_node->authors,authors_temp);
    strcpy(new_node->publisher,publisher_temp);
    new_node->year=year_temp;
    strcpy(new_node->ISBN,ISBN_temp);

    new_node->next=NULL;//set to NULL temporarily.
    new_node->previous=NULL;//set to NULL temporarily.

    return new_node;//Returns new node to function1.
}


book_node *add_entry_pushend(book_node *head, book_node *new_entry)//Push new node to the end of the doubly linked list.
{
    if (head==NULL){return new_entry;}//If the list is empty new entry becomes the head.

    book_node *curr = head;
    while(curr->next!=NULL)
        curr=curr->next;

    curr->next=new_entry;
    new_entry->previous=curr;   
    return head;
}


book_node *load_binfile(const char *filename)//Load file data to the doubly linked list
{
    FILE *fptr =fopen(filename,"rb");//Opening the binary file for writting.
    if (fptr==NULL){perror("File not found!\n");return NULL;}

    book_node *head = NULL;
    book_node *tail = NULL; 
    book_data_node data;

    while(fread(&data,sizeof(book_data_node),1,fptr))//Read every single node of the book's data list.
    {
        book_node *new_node =(book_node *)malloc(sizeof(book_node));//Allocate memory for the new node.
        if(new_node==NULL){perror("Memory allocation failed!");exit(EXIT_FAILURE);}

        //Copy data from file to the new node.
        strcpy(new_node->title,data.title);
        strcpy(new_node->authors,data.authors);
        strcpy(new_node->publisher,data.publisher);
        new_node->year =data.year;
        strcpy(new_node->ISBN,data.ISBN);

        new_node->next=NULL;
        new_node->previous=tail;
        
        if (tail != NULL)
            tail->next = new_node;
        else
            head = new_node;//If there is only one node.

        tail = new_node;
    }
    fclose(fptr);
    return head;
}


void save_to_binfile(book_node *head, const char *filename)//Save the data to file.
{
    FILE *fptr =fopen(filename,"wb");//Opening the binary file for writting.
    if (fptr==NULL){perror("File not found!\n");exit(EXIT_FAILURE);}

    book_node *curr = head;
    while(curr!= NULL)
    {
        //Copy the data to temp struct (data struct).
        book_data_node data;
        memset(&data,0,sizeof(book_data_node));//Clears stdin buffer to avoid filling the remaining spots with garbage (sets them to 0).
        strcpy(data.title,curr->title);
        strcpy(data.authors,curr->authors);
        strcpy(data.publisher,curr->publisher);
        data.year = curr->year;
        strcpy(data.ISBN,curr->ISBN);

        fwrite(&data,sizeof(book_data_node),1,fptr);
        curr=curr->next;
    }
    fclose(fptr);
    printf("\n \033[32mFile saved succesfully!\033[0m\n\n");
}


void press_enter_to_continue()
{
    printf("\033[32mPress [enter] to continue: \033[0m");
    clear_input_buffer();
}


int main_menu()//The main menu of the application.
{
    printf("\n\n      \033[33m|----------------------|\n");
    printf("      |Library Control System|\n");
    printf("      |----------------------|\033[0m\n\n\n");
    printf(" Select one of the following options:\n");
    printf(" (1) Add a Record.\n");
    printf(" (2) Remove a Record.\n");
    printf(" (3) Modify a Record.\n");
    printf(" (4) Sort Records in the Database.\n");
    printf(" (5) Display information of a specific Record.\n");
    printf(" (6) Display all Record information.\n");
    printf(" (7) Exit the application and Save to file.\n\n");
    printf(" Please provide your selection(1-7): ");
    int answer;
    do
    {
        answer=integer_validation();
        if(answer>=1 && answer<=7){break;}else{printf(" \033[31mInvalid Input! Please provide your selection(1-7):\033[0m ");}
    }while(1);
    clear_input_buffer();
    return answer;
}


void function_1(book_node **head)//Record entry.
{
    char isISBN[20];
    printf("Please enter book's ISBN code: ");
    fgets(isISBN,sizeof(isISBN),stdin);
    isISBN[strcspn(isISBN,"\n")]= '\0';
    if(ISBNsearch(*head,isISBN)==1)
    {
        printf("Sorry but this record is already in the database!\n");
    }else{
        book_node *new_entry = create_entry_node();//New entry node creation.
        *head =add_entry_pushend(*head,new_entry);//Add the new node to the doubly linked list.
    }
}


void function_2(book_node **head)//Remove record.
{
    char ISBN_remove[20];
    printf("Please enter the ISBN code of the record you want to remove: ");
    fgets(ISBN_remove,sizeof(ISBN_remove),stdin);
    ISBN_remove[strcspn(ISBN_remove,"\n")]='\0';
   
    book_node *curr=*head;
    while(curr!=NULL)
    {
        if (strcmp(curr->ISBN, ISBN_remove) == 0)//If we find the record.
        {
            if(curr->previous != NULL)//Check if the node is not the head.
                curr->previous->next=curr->next;
            else
                *head= curr->next;//Delete head.

            if(curr->next != NULL)
                curr->next->previous=curr->previous;

            printf("\nThe title of the record deleted is: %s, with ISBN code: %s\n",curr->title,curr->ISBN);
            free(curr);
            return;
        }
        curr=curr->next;
    }
    printf("\033[31mRecord not found!\033[0m\n");
}


void function_3(book_node *head)//Record modify.
{
    char ISBN_modify[20];
    printf("Please enter the ISBN code of the record you want to modify: ");
    fgets(ISBN_modify,sizeof(ISBN_modify),stdin);
    ISBN_modify[strcspn(ISBN_modify,"\n")]='\0'; 
    
    book_node *curr=head;
    while(curr!=NULL)
    {
        if (strcmp(curr->ISBN,ISBN_modify) == 0) 
        {
            printf("Please provide the following information for the record you want to modify:\n\n");
            printf("Title: ");
            fgets(curr->title,sizeof(curr->title),stdin);
            curr->title[strcspn(curr->title,"\n")]= '\0'; 
            printf("Author(s): ");
            fgets(curr->authors,sizeof(curr->authors),stdin);
            curr->authors[strcspn(curr->authors,"\n")]= '\0';
            printf("Publisher: ");
            fgets(curr->publisher,sizeof(curr->publisher),stdin);
            curr->publisher[strcspn(curr->publisher,"\n")]= '\0';
            printf("Year of release: ");
            curr->year=integer_validation();
            return;
        }  
        curr=curr->next;
    }
    printf("\033[31mSorry but the record you provided is not in the database\033[0m\n");
}


void function_4(book_node *head)//Sorting based on user's preference.
{
    printf(" Please enter the type of sorting you want to do:\n");
    printf(" (1) Based on the Title\n");
    printf(" (2) Based on Author(s) Name\n");
    printf(" (3) Based on Publisher Name\n");
    printf(" (4) Based on Year of release\n");
    printf(" (5) Based on ISBN code\n");
    printf("Please provide your answer (1-5): ");
    int sort_preference;
    do
    {
        sort_preference = integer_validation();//Get the answer by th user.
        if(((sort_preference==1)||(sort_preference==2)||(sort_preference==3)||(sort_preference==4)||(sort_preference==5)))
        {
            break;
        }else{printf("\033[31mInvalid input!Please enter one of the options (1-5)\033[0m\n");}
    }while(1);

    int flag1;//If nothing changes the flag1 remains false which means the sorting proccess has ended.
    int flag2;//flag2 becomes true when we need to swap the values.
    book_node *curr;
    char title_temp[STRING_SIZE],author_temp[STRING_SIZE],publisher_temp[STRING_SIZE],ISBN_temp[ISBN_SIZE];
    int year_temp;
    do
    {
        flag1=0;
        curr=head;
        while(curr->next!=NULL)
        {
            flag2=0;
            if(sort_preference==1)                                                //Steps:  //Check what type of sorting the user wants to do.
            {                                                                              //Compare the current node with the next node.
                if(strcmp(curr->title,curr->next->title)>0){flag2=1;}                      //If the current node has a greater ASCI value than the next flag2 becomes true.
            }else if (sort_preference==2)
            {
                if (strcmp(curr->authors,curr->next->authors)>0){flag2=1;}
            }else if(sort_preference==3)
            {
                if (strcmp(curr->publisher,curr->next->publisher)>0){flag2=1;}
            }else if(sort_preference==4)
            {
                if(curr->year>curr->next->year){flag2=1;}
            }else
            {
                if (strcmp(curr->ISBN,curr->next->ISBN)>0){flag2=1;}
            }
            if(flag2==1)                                                       //If flag2 is true we swap the current node with the next node.
            {//SWAP THE NODES
                strcpy(title_temp,curr->title);//Title.
                strcpy(curr->title,curr->next->title);
                strcpy(curr->next->title,title_temp);

                strcpy(author_temp,curr->authors);
                strcpy(curr->authors,curr->next->authors);//Authors.
                strcpy(curr->next->authors,author_temp);

                strcpy(publisher_temp,curr->publisher);//Publisher.
                strcpy(curr->publisher,curr->next->publisher);
                strcpy(curr->next->publisher,publisher_temp);

                year_temp=curr->year;//Year.
                curr->year=curr->next->year;
                curr->next->year=year_temp;

                strcpy(ISBN_temp,curr->ISBN);//ISBN.
                strcpy(curr->ISBN,curr->next->ISBN);
                strcpy(curr->next->ISBN,ISBN_temp);
                
                flag1=1;
            }
            curr=curr->next;
        }
    }while(flag1);
}


void function_5(book_node *head)//Prints information for a specific record.
{
    char ISBN[20];
    printf("Please enter the ISBN code of the record you want to see the details: ");
    fgets(ISBN,sizeof(ISBN),stdin);
    ISBN[strcspn(ISBN,"\n")]='\0';   
    book_node *curr=head;
    while(curr!=NULL)
    {
        if (strcmp(curr->ISBN,ISBN) == 0) 
        {
            printf("\nThe Record exists! These are the record's information\n");
            printf("Title: %s\n",curr->title);
            printf("Author(s): %s\n", curr->authors);
            printf("Publisher: %s\n", curr->publisher);
            printf("Year of release: %d\n", curr->year);
            printf("ISBN: %s\n", curr->ISBN);
            putchar('\n');
            return;
        }  
        curr=curr->next;
    }
    printf("\033[31mSorry but the record you provided is not in the database\033[0m\n");
}


void function_6(book_node *head)//Print information for every record in the database.
{
    book_node *curr = head;
    int i=1;
    while(curr)
    {
        printf("\033[34m---------------Book #%d---------------\033[0m\n",i++);
        printf("        \033[34mTitle:\033[0m %s\n", curr->title);
        printf("        \033[34mAuthor(s):\033[0m %s\n", curr->authors);
        printf("        \033[34mPublisher:\033[0m %s\n", curr->publisher);
        printf("        \033[34mYear:\033[0m %d\n", curr->year);
        printf("        \033[34mISBN:\033[0m %s\n", curr->ISBN);
        curr=curr->next;
        putchar('\n');
    }
}

void free_list(book_node *head)//Deallocate memory of the doubly linked list.
{
    book_node *temp;
    while (head != NULL)
    {
        temp=head;
        head=head->next;
        free(temp);   
    }
}



    
