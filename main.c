#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "populate.h"

int main() 
{ 
    AddressBook var;
  
    initialize(&var);
    
    printf("%d\n",var.contactCount);
    int choice;

do
{
    printf("\n");
    printf("1. Add contact\n");
    printf("2. Edit contact\n");
    printf("3. Search contact\n");
    printf("4. Delete contact\n");
    printf("5. List  contact\n");
    printf("6. Save contact\n");
    printf("7. Exit\n");

    printf("\n-->Enter your choice:");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
        createContact(&var);
        break;

        case 2:
        editContact(&var);
        break;

        case 3:
        searchContact(&var);
        break;

        case 4:
        deleteContact(&var);
        break;

        case 5:
        listContacts(&var);
        break;

        case 6:
        saveContactsToFile(&var);
        break;
        
        
        case 7:
        printf("\t\nEXITING................\n\n");
        return 0 ;
        break;


        default:
        printf("Invalid choice, enter choice from 1 to 7");
        break;

    }

} while( choice != 7);

    return 0;

}
