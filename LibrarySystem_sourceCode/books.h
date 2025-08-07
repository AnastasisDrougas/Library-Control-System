//Anastasis Drougas.
//it2024023.
#ifndef BOOKS_H
#define BOOKS_H
#define STRING_SIZE 256
#define ISBN_SIZE 20

typedef struct node //Declare the struct (node for our double linked list).
{
    //Data.
    char title[STRING_SIZE];
    char authors[STRING_SIZE];
    char publisher[STRING_SIZE];
    int year;
    char ISBN[ISBN_SIZE];
    //Pointers.
    struct node *next;
    struct node *previous;

}book_node;

typedef struct data_node_temp
{
    //Node that contains only the data.
    char title[STRING_SIZE];
    char authors[STRING_SIZE];
    char publisher[STRING_SIZE];
    int year;
    char ISBN[ISBN_SIZE];
}book_data_node;

int main_menu();//Prints main Menu.

void clear_screen();//Clears user's screen.

void press_enter_to_continue();

void clear_input_buffer();//Cleans buffer.

int ISBNsearch (book_node *head,char ISBN[]);//Search based on ISBN code.

int integer_validation();//Returns valid integer.

void free_list(book_node *head);//Deallocate memory of the linked list.


book_node *create_entry_node();//Creates a new node.
book_node *add_entry_pushend(book_node *head,book_node *new_entry);//Push new entry to the end.

book_node *load_binfile(const char *filename);//Loads data from file.
void save_to_binfile(book_node *head, const char *filename);//Saves data ti file.


void function_1(book_node **head);//Add new record.

void function_2(book_node **head);//Remove Record.

void function_3(book_node *head);//Modify a record.

void function_4(book_node *head);//Sort items based on user's preference.

void function_5(book_node *head);//Prints information for a specific record.

void function_6(book_node *head); //Print all record information.

#endif