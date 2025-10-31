/*This is the main program of the Address Book system.
It provides a menu-driven interface for users to create, 
search, edit, delete, list, and save contacts.*/


#include <stdio.h>
#include "contact.h"

int main() {
    int choice;              //Stores user menu choice
    int sortChoice;          
    int indexlist[20];       //store index of found contacts during search
    AddressBook addressBook; //Declare the addressBook structure

      //Load contacts from file(if contacts are available)
      intialize(&addressBook);
     
    do {
        //Display main menu options
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        //Perform action based on user choice
        switch (choice) {

            case 1:
                //Add new contact
                createContact(&addressBook);
                break;

            case 2:
                //Search the contact by name,phone or email
                searchContact(&addressBook,indexlist);
                break;

            case 3: 
                //Edit the existing contact
                editContact(&addressBook);
                break;

            case 4:
                //Delete a contact from the list
                deleteContact(&addressBook);
                break;

            case 5:  
                //Display all saved contacts        
                listContacts(&addressBook, sortChoice);
                break;

            case 6:
                //Save current contacts to file
                printf("Saving and Exiting...\n");
                saveAndExit(&addressBook);
                break;

            case 7:
                //Exit the program
                printf("Exited Successfully...\n"); 
                break; 

            default:
                //Invalid choice
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);//Continue until user choose to exit
    
       return 0;
}
