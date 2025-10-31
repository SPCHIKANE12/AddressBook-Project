#ifndef CONTACT_H
#define CONTACT_H

//Maximum number of contacts to allowed in addressBook
#define MAX_CONTACTS 100

//Definition of structure
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

//Function prototype
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook,int *indexlist);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void intialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

#endif
