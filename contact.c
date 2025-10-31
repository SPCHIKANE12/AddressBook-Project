/*This project is a Contact Management System in C that allows users to 
add, search, edit, delete, and list contacts.It includes input validation, duplicate checking,
and file handling for saving and loading contacts*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    sortCriteria=0;
    int compare;
    rechoice:
    printf("Sort By:\n1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &sortCriteria);
    Contact Temp;

    

    for(int i=0;i<addressBook->contactCount-1;i++){
        for(int j=0;j<addressBook->contactCount-1-i;j++){

            if(sortCriteria == 1)
            compare=strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
            else if(sortCriteria == 2)
            compare=strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone);
            else if(sortCriteria == 3)
            compare=strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email);

            else{
                printf("Error: Invalid sort choice\n");
                goto rechoice;
            }
        
        if(compare > 0){
            Temp=addressBook->contacts[j];
            addressBook->contacts[j]=addressBook->contacts[j+1];
            addressBook->contacts[j+1]=Temp;

        }
    }
}

    printf("\n========================== CONTACT LIST ===============================\n");
    if(addressBook->contactCount==0){
        printf("No contacts available.\n");
        printf("=======================================================================\n");
        return;
    }

    printf("=======================================================================\n");
    printf("%-5s | %-20s | %-15s | %-20s\n","Sr.No","Name","Phone","Email");
    printf("=======================================================================\n");
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-5d | %-20s | %-15s | %-30s\n",i+1,addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
     printf("=======================================================================\n");
}


void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}
    

void intialize(AddressBook *addressBook) {
    addressBook->contactCount=0;
    loadContactsFromFile(addressBook); 

}

void createContact(AddressBook *addressBook)
{
    //Check addressBook is Full or Not
	if(addressBook->contactCount >= 100){
        printf("Error:AddressBook is full.Cannot add more contacts.\n");
        return;
    }
     
     Contact NewContact;

            printf("\n========================= ADD NEW CONTACT ========================\n");
    
            reEntername:
            getchar();
            printf("Enter new name: ");
            scanf("%[^\n]",NewContact.name);
            int i;

            //Check name must be alphabate and space
            for(i=0;i<strlen(NewContact.name);i++){
                if(!isalpha(NewContact.name[i]) && NewContact.name[i] != ' '){
                     printf("Invalid input:Name must contain only letters and spaces.\n");
                     goto reEntername;
                }
             }  

                 reEnterphone:  
                 getchar();
                 printf("Enter new phone number[10 digit]: ");
                 scanf("%[^\n]",NewContact.phone);
    
                 //Check length of the phone number
                 if(strlen(NewContact.phone)!=10){
                    printf("Invalid input: Phone number must be exactly 10 digit.\n");
                    goto reEnterphone;
                }

                //Check phone number must be digit
                for(int i=0;i<strlen(NewContact.phone);i++){
                    if(!isdigit(NewContact.phone[i])){
                        printf("Invalid input: Phone number must contain only digits.\n");
                        goto reEnterphone;
                    }
                }

                //Check must be phone number is unique
                for(int i=0;i<addressBook->contactCount;i++){
                    if(strstr(addressBook->contacts[i].phone,NewContact.phone)!=NULL){
                    printf("Error: This phone number already exists.\n");
                    goto reEnterphone;
                }
             }
        
                 reEnteremail:
                 getchar();
                 printf("Enter new email: ");
                 scanf("%[^\n]",NewContact.email);


                //Check email must be in lowercase
                for(i=0;i<strlen(NewContact.email);i++){
                    if(isupper(NewContact.email[i])||isspace(NewContact.email[i]) ) {
                        printf("Error:Email must be in lowercase contain no space.\n");
                        goto reEnteremail;
                    }
                    if (!(islower(NewContact.email[i]) ||isdigit(NewContact.email[i]) 
                          || NewContact.email[i] == '.' || NewContact.email[i] == '_'|| NewContact.email[i]=='@')) {
                       printf("Only letters, digits, dots, and underscores are allowed!\n");
                      goto reEnteremail;
                     }
                 }

                  // Email must end with @gmail.com
                 char *gmail_pos = strstr(NewContact.email, "@gmail.com");

               // If "@gmail.com" not found OR not at the very end → error
               if (gmail_pos == NULL || strcmp(gmail_pos, "@gmail.com") != 0) {
               printf("Error: Email must end with '@gmail.com'.\n");
               goto reEnteremail;
               }

             // If email is only "@gmail.com" (no name before it)
             if (gmail_pos == NewContact.email) {
             printf("Error: There must be at least one character before '@gmail.com'.\n");
             goto reEnteremail;
             }

             
             //Check email must be unique
             for(int i=0;i<addressBook->contactCount;i++){
                if(strstr(addressBook->contacts[i].email,NewContact.email)!=NULL){
                    printf("Error: This email already exists.\n");
                    goto reEnteremail;
                }
             }

           addressBook->contacts[addressBook->contactCount]=NewContact;
           addressBook->contactCount++;
        
          printf("==================================================================\n");
          printf("Contact added successfully.\n");
          printf("==================================================================\n");

     }


int searchContact(AddressBook *addressBook,int *indexlist) 
{
    int choice;
    char new_name[20];
    char new_phone[10];
    char new_email[30];
    int found = 0;


    getchar(); 
    printf("\n========================= SEARCH CONTACT =========================\n");
    printf("Search By:\n1. Name\n2. Phone\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            getchar();
            printf("Enter name to search: ");
            scanf("%[^\n]", new_name);

            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strcasestr(addressBook->contacts[i].name, new_name) != NULL) {
                    printf("\n%-5d %-20s %-20s %-30s\n", found + 1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    indexlist[found++] = i;
                }
            }
            break;

        case 2:
            getchar();
            printf("Enter phone number to search: ");
            scanf("%[^\n]", new_phone);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].phone, new_phone) != NULL) {
                    printf("\n%-5d %-20s %-20s %-30s\n",found+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    indexlist[found++] = i;
                }
            }
            break;

        case 3:
            getchar();
            printf("Enter email to search: ");
            scanf("%[^\n]", new_email);
            for (int i = 0; i < addressBook->contactCount; i++) {
                if (strstr(addressBook->contacts[i].email, new_email) != NULL) {
                    printf("\n%-5d %-20s %-20s %-30s\n",found+1,
                        addressBook->contacts[i].name,
                        addressBook->contacts[i].phone,
                        addressBook->contacts[i].email);
                    indexlist[found++] = i;
                }
            }
            break;

        default:
            printf("Invalid choice.\n");
            return 0;
    }

    //If no matches found
    if (found == 0) {
        printf("==================================================================\n");
        printf("No matching contact found.\n");
        printf("==================================================================\n");
    }
    return found;
}


void editContact(AddressBook *addressBook)
{
    printf("\n========================= EDIT CONTACT =========================\n");
    int indexlist[10];
    int found=searchContact(addressBook,indexlist);
    if(found==0)
    return;


    int Choice;
    if(found>1){
        printf("Enter choice which contact you want to edit:");
        scanf("%d",&Choice);
        if(Choice < 1 || Choice > found){
            printf("Error: Please Enter correct index!!");
            return;
        }
    }
    else
    Choice = 1;

    int editIndex=indexlist[Choice-1];
    char New_name[20];
    char New_phone[10];
    char New_email[30];

    getchar();
    printf("1. Name\n2. Phone\n3. Email\n");
    printf("Which field you want to edit: ");
    int NewChoice;
    scanf("%d",&NewChoice);

    
    switch (NewChoice) {
        case 1:

            reEntername:
            getchar();
            printf("Enter New Name:");
            scanf("%[^\n]",New_name);
            int i;

            //Check name must be alphabate and space
            for(i = 0;i < strlen(New_name); i++){
                if(!isalpha(New_name[i]) && New_name[i] != ' '){
                     printf("Invalid name: Use letters and spaces only.\n");
                    goto reEntername;
                }
            }     
            
             strcpy(addressBook->contacts[editIndex].name,New_name);
             break;

        case 2:
                 reEnterphone:
                 getchar();
                 printf("Enter new phone number[10 digit]: ");
                 scanf("%[^\n]",New_phone);
    
                 //Check length of the phone number
                 if(strlen(New_phone)!=10){
                    printf("Error: Enter exact 10 digit!!\n");
                    goto reEnterphone;
                }

                //Check phone number must be digit
                for(i=0;i<strlen(New_phone);i++){
                    if(!isdigit(New_phone[i])){
                        printf("Error: Phone number must contain only digit.\n");
                        goto reEnterphone;
                    }
                }

                //Check must be phone number is unique
                for( i=0;i<addressBook->contactCount;i++){
                    if(i!=editIndex && strstr(addressBook->contacts[i].phone,New_phone)!=NULL){
                    printf("Error:This number already exists.\n");
                    goto reEnterphone;
                }
            }
            strcpy(addressBook->contacts[editIndex].phone,New_phone);
            break;

        case 3:
                 reEnteremail:
                 getchar();
                 printf("Enter new email: ");
                 scanf("%[^\n]",New_email);

                 //Check email must be in lowercase
                 for(i=0;i<strlen(New_email);i++){
                    if(isupper(New_email[i])||isspace(New_email[i])){
                        printf("Error:Email must be in lowercase contain no space.\n");
                        goto reEnteremail;
                    }
                    if (!(islower(New_email[i]) ||isdigit(New_email[i]) 
                          || New_email[i] == '.' || New_email[i] == '_'||New_email[i]=='@')) {
                        printf("Only letters, digits, dots, and underscores are allowed!\n");
                        goto reEnteremail;
                          }
                 }

               // Email must end with @gmail.com
               char *gmail_pos = strstr(New_email, "@gmail.com");

               // If "@gmail.com" not found OR not at the very end → error
               if (gmail_pos == NULL || strcmp(gmail_pos, "@gmail.com") != 0) {
               printf("Error: Email must end with '@gmail.com'.\n");
               goto reEnteremail;
               }

             // If email is only "@gmail.com" (no name before it)
             if (gmail_pos == New_email) {
             printf("Error: There must be at least one character before '@gmail.com'.\n");
             goto reEnteremail;
             }

             //Check email must be unique
             for(i=0;i<addressBook->contactCount;i++){
                if(i!=editIndex && strstr(addressBook->contacts[i].email,New_email)!=NULL){
                    printf("Error: This email already exists.\n");
                    goto reEnteremail;
                }
             }
        
            strcpy(addressBook->contacts[editIndex].email,New_email);
            break;


            default:
            printf("Invalid choice.\n");
            return;
        }
    printf("==================================================================\n");
    printf("Contact updated successfully.\n");
    printf("==================================================================\n");

}

void deleteContact(AddressBook *addressBook)
{
    int indexlist[20];
	int found=searchContact(addressBook,indexlist);

      if(found==0)
    return;

    rechoice:
    int Choice;
    if(found>1){
        printf("Enter choice which contact you want to delete: ");
        scanf("%d",&Choice);
        if(Choice < 1|| Choice > found){
            printf("Invalid selection. Please choose a valid contact.\n");
            goto rechoice;
        }
    }
    else
    Choice = 1;

    int delindex = indexlist[Choice-1];
    char Answer;
    reEnterchoice:
    getchar();
    printf("Do you want to delete contact:(Y/N):");
    scanf("%c",&Answer);

    //Confirmation for deletion
    if(Answer=='y'|| Answer=='Y'){
        for(int i=delindex;i<addressBook->contactCount-1;i++){
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
         addressBook->contactCount--;
        printf("==================================================================\n");
        printf("Contact Delete successfully.\n");
        printf("==================================================================\n");

    }
    else if(Answer=='n'|| Answer=='N'){
    printf("==================================================================\n");
    printf("Deletion cancelled.\n");  
    printf("==================================================================\n");
    }
    else{
    printf("Error: Invalid Choice.\n");
    goto reEnterchoice;
    }
}

