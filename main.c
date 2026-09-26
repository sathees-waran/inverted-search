/*
 * Project Name : Inverted Search
 * Author       : Satheeswaran M
 * Filename     : main.c
 *
 * Description  : Main driver program for the Inverted Search project.
 *                Provides a menu-driven interface to create, display,
 *                search, update, and save the inverted search database.
 */

#include "main.h"

int main(int argc, char *argv[])
{
    hash_t arr[TOTAL_BUCKETS] = {0};   /* zero-inits index=0, link=NULL for all */
    flist *valid_files = NULL;

    int choice;
    char word[SIZE];
    char filename[SIZE];

    /* Validate input files */
    if (validate_files(argc, argv, &valid_files) == FAILURE)
    {
        printf("No valid files to create database\n");
        return FAILURE;
    }

    while (1)
    {
        printf("------------------------------------------------------------MENU------------------------------------------------------------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. exit\n");
        printf("---------------------------------------------------------------------------------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nCreate database selected.\n\n");

                if (create_database(arr, valid_files) == SUCCESS)
                    printf("Database created successfully.\n");
                else
                    printf("Database creation failed.\n");

                break;

            case 2:
                printf("\nDisplay database selected.\n\n");

                display_database(arr);

                break;

            case 3:
                printf("\nSearch database selected.\n\n");

                printf("Enter the word you want to search: ");
                scanf("%s", word);

                search_database(arr, word);

                break;

            case 4:
                printf("\nUpdate database selected.\n\n");

                printf("Enter a new file name: ");
                scanf("%s", filename);

                if (update_database(arr, filename) == SUCCESS)
                {
                    printf("Successfully inserted file %s into file linked list.\n",
                           filename);

                    printf("\nDatabase updated successfully.\n");
                }

                break;

            case 5:
                printf("\nSave database selected.\n\n");

                printf("Enter the filename to save: ");
                scanf("%s", filename);

                save_database(arr, filename);

                break;

            case 6:
                printf("\nExit selected.\n");
                return SUCCESS;

            default:
                printf("\nInvalid choice.\n");
        }

        printf("\n");
    }

    return SUCCESS;
}