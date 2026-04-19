#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "populate.h"


// To Initialize address book by reading from file
void initialize(AddressBook *addressBook)
{
    // populateAddressBook(addressBook);

    FILE *fptr = fopen("contact.txt", "r");

    if (fptr == NULL)
    {
        printf("Not able to open file ");
        return;
    }

    fscanf(fptr, "%d\n", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],",  addressBook->contacts[i].name);//comma after brackets is because 'there is comma after each name so to ignore that , is written
        fscanf(fptr, "%[^,],",  addressBook->contacts[i].phone);
        fscanf(fptr, "%[^\n]\n", addressBook->contacts[i].email);
    }

    fclose(fptr);
}


// To Display all contacts
void listContacts(AddressBook *addressBook)
{
    printf("\nNAME\t\tMOBILE NUM\t\tMAIL ID\n\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d %s\t",  (i + 1), addressBook->contacts[i].name);
        printf("%s\t",     addressBook->contacts[i].phone);
        printf("%s\n",     addressBook->contacts[i].email);
    }

    printf("\n");
}


// To Create a new contact
void createContact(AddressBook *addressBook)
{
    int index = addressBook->contactCount;

    if (index >= 100)
    {
        printf("\n\t------ADDRESSBOOK FULL!------\n");
        return;
    }

    else
    {


    printf("\tEnter name: ");
    scanf(" %[^\n]", addressBook->contacts[index].name);

    printf("\tEnter phone num: ");
    char phoneno[20];
    scanf(" %[^\n]", phoneno);

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phoneno) == 0)//compares phone num already exists?
        {
            found = 1;//if exits  found=1
             break;
        }
    }

    if (found)
    {
        printf("\n\t***PHONE NUMBER EXISTS***\n");
        return;
    }
    else
    {
        strcpy(addressBook->contacts[index].phone, phoneno);
    }

    printf("\tEnter Mail-ID: ");
    char mail[50];
    scanf(" %[^\n]", mail);

    if (strstr(mail, "@example.com") || strstr(mail, "@gmail.com") )
    {
        strcpy(addressBook->contacts[index].email, mail);
        addressBook->contactCount++;

        printf("\n\t***CONTACT ADDED SUCCESSFULLY***\n\n");
    }
    else
    {
        printf("\n\t---ERROR: ENTER VALID MAIL-ID---\n\n");
    }
}
}


// To Search a contact by name
void searchContact(AddressBook *addressBook)
{
    int found = 0;
    char name[50];

    printf("\n\tContact name to search: ");
    scanf(" %[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            found = 1;
            printf("\n\tName  : %s\n", addressBook->contacts[i].name);
            printf("\tPhone : %s\n", addressBook->contacts[i].phone);
            printf("\tMail  : %s\n", addressBook->contacts[i].email);
            break;
        }
    }

    if (!found)
    {
        printf("\n\t***CONTACT NOT FOUND***\n\n");
    }
}


// To Edit contact details
void editContact(AddressBook *addressBook)
{
    listContacts(addressBook);

    int index;
    printf("\tSelect contact to edit: ");
    scanf("%d", &index);

    if ( (index >=1 ) && (index <= addressBook->contactCount) )
    {
        index--;   // displayed from 1, array starts from 0

        int option;
        printf("\t1. Name\n");
        printf("\t2. Phone\n");
        printf("\t3. Mail ID\n");
        printf("\tSelect to edit: ");
        scanf("%d", &option);

        switch (option)
        {
            case 1:
            {
                char Cname[50];
                printf("\tEnter name: ");
                scanf("%s", Cname);
                strcpy(addressBook->contacts[index].name, Cname);
                printf("\n\t***SUCCESSFULLY EDITED NAME***\n");
                break;
            }

            case 2:
            {
                char Cphone[50];
                printf("\tEnter phone number: ");
                scanf("%s", Cphone);
                strcpy(addressBook->contacts[index].phone, Cphone);
                printf("\n\t***SUCCESSFULLY EDITED PHONE NUMBER***\n");
                break;
            }

            case 3:
            {
                char Cmail[50];
                printf("\tEnter mail id: ");
                scanf("%s", Cmail);

                if (strstr(Cmail, "@example.com") || strstr(Cmail, "@gmail.com"))
                {
                    strcpy(addressBook->contacts[index].email, Cmail);
                    printf("\n\t***SUCCESSFULLY EDITED MAIL-ID***\n");
                }
                else
                {
                    printf("\n\t---ERROR: ENTER VALID MAIL-ID---\n\n");
                }
                break;
            }

            default:
                printf("\n\t---ERROR: SELECT VALID OPTION---\n");
        }
    }
    else
    {
        printf("\n\t---ERROR: SELECT VALID CONTACT---\n");
    }
}


// To Delete a contact
void deleteContact(AddressBook *addressBook)
{
    listContacts(addressBook);

    getchar();   // clear newline

    char name[50];
    printf("\n\tEnter Contact name to be deleted: ");
    scanf("%[^\n]", name);

    int flag = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0)
        {
            for (int j = i; j < addressBook->contactCount - 1; j++)
            {
                strcpy(addressBook->contacts[j].name,addressBook->contacts[j + 1].name);
                strcpy(addressBook->contacts[j].phone,addressBook->contacts[j + 1].phone);
                strcpy(addressBook->contacts[j].email,addressBook->contacts[j + 1].email);
            }

            addressBook->contactCount--;
            printf("\n\t***CONTACT DELETED SUCCESSFULLY***\n");
            flag = 1;
            break;
        }
    }

    if (!flag)
    {
        printf("\n\t----ERROR: CONTACT NAME NOT FOUND!----\n\n");
    }
}


// Save contacts to file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contact.txt", "w");

    if (fptr == NULL)
    {
        printf("Failed to open\n\n");
        return;
    }

          fprintf(fptr, "%d\n", addressBook->contactCount);

          if(addressBook->contactCount > 100 )
          {
              printf("\n\t******ADDRESS BOOK IS FULL!******");
              return;
          }

          else
          {

                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    fprintf(fptr, "%s,%s,%s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone,addressBook->contacts[i].email);

                    //   fprintf(fptr, "%s,%s,%s\n",
                    //         addressBook->contacts[i].name,
                    //         addressBook->contacts[i].phone,
                    //          addressBook->contacts[i].email);
          }

          fclose(fptr);

          printf("\n\t***CONTACTS SAVED SUCCESSFULLY***\n\n");
    }
}
