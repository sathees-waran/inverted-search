#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/* 
 * validate.c
 * -----------
 * validates input files before database creation
 * checks for:
 *   - file existence
 *   - empty files
 *   - duplicate files
 * keeps a validated list of files (flist) for processing
 */

int validate_files(int argc, char *argv[], flist **head)
{
    FILE *fp;
    int i;
    flist *temp, *prev;

    if (argc < 2)
    {
        printf("Error: No input files provided\n");
        return FAILURE;
    }

    for (i = 1; i < argc; i++)
    {
        /* check duplicate */
        temp = *head;
        while (temp)
        {
            if (strcmp(temp->filename, argv[i]) == 0)
            {
                printf("Duplicate file ignored: %s\n", argv[i]);
                break;
            }
            temp = temp->link;
        }
        if (temp)
            continue;

        /* check file existence */
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("File not found: %s\n", argv[i]);
            continue;
        }

        /* check file empty */
        fseek(fp, 0, SEEK_END);
        if (ftell(fp) == 0)
        {
            printf("Empty file ignored: %s\n", argv[i]);
            fclose(fp);
            continue;
        }
        fclose(fp);

        /* add valid file to list */
        flist *new = malloc(sizeof(flist));
        if (new == NULL)
            return FAILURE;

        strcpy(new->filename, argv[i]);
        new->link = NULL;

        if (*head == NULL)
            *head = new;
        else
        {
            prev = *head;
            while (prev->link)
                prev = prev->link;
            prev->link = new;
        }

        printf("Valid file added: %s\n", argv[i]);
    }

    return (*head != NULL) ? SUCCESS : FAILURE;
