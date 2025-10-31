/*This file handles file operations for the Address Book.
It includes functions to load contacts from a file and save contacts to a file*/

#include<stdio.h>
#include "file.h"

void loadContactsFromFile(AddressBook *addressBook){
     addressBook->contactCount=0;
    FILE *fp;
    fp=fopen("contacts.txt","r");

    if(fp==NULL){
        printf("Error:No contacts file found\n");
        return;
    }

    //Read how many contacts are present in the file
    fscanf(fp,"%d\n",&addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++){
    fscanf(fp,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,
    addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    printf("==================================================================\n");
    printf("Contacts loaded successfully from file.\n");
    printf("==================================================================\n");

}

void saveContactsToFile(AddressBook *addressBook){
    FILE *fp;
    fp=fopen("contacts.txt","w");

    if(fp == NULL){
        printf("Error:Unable to open file for writing!\n");
        return ;
    }

    //Save into file how many contacts are present
    fprintf(fp,"%d\n",addressBook->contactCount);

    for(int i=0;i<addressBook->contactCount;i++){
        fprintf(fp,"%s,%s,%s\n",
            addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
    }
    fclose(fp);
    printf("==================================================================\n");
    printf("Contacts saved successfully to file.\n");
    printf("==================================================================\n");
    
}
