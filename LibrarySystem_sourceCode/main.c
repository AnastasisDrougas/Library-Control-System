//Anastasis Drougas.
//it2024023
#include<stdio.h>
#include<stdlib.h>
#include "books.h"

int main()
{
    clear_screen();
    book_node *head=load_binfile("books.dat");//Load data from file.
    if (head == NULL) {perror("File retrieval failed!\n");exit(EXIT_FAILURE);}
    do
    {
        int answer = main_menu();
        if(answer == 1)//Add new record (create new node to the doubly linked list).
        {
            clear_screen();
            function_1(&head);
            press_enter_to_continue();
        }else if(answer==2)//Remove a record (remove a node from the  doubly linked list).
        {
            clear_screen();
            function_2(&head);
            press_enter_to_continue();
        }else if (answer==3)//Modify a record's info.
        {
            clear_screen();
            function_3(head);
            clear_input_buffer();
            press_enter_to_continue();
        }else if(answer==4)//Sorting based on user's preference.
        {
            clear_screen();
            function_4(head);
            printf("\n\nRecords Sorted!\n");
            clear_input_buffer();
            press_enter_to_continue();
        }else if (answer==5)//Print specific record information.
        {
            clear_screen();
            function_5(head);
            //clear_input_buffer();
            press_enter_to_continue();
        }
        else if(answer==6)//Print the info of the records in our linked list.
        {
            clear_screen();
            function_6(head);
            press_enter_to_continue();
        }else if (answer==7){break;}//Exit.
        clear_screen();
    }while(1);
    save_to_binfile(head,"books.dat");//Save data to file.
    free_list(head);
    return EXIT_SUCCESS;
    
}