#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

int update_database(hash_t arr[], char *filename)
{
    FILE *fp;
    char word[SIZE];
    int index;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Unable to open file %s\n", filename);
        return FAILURE;
    }

    while (fscanf(fp, "%s", word) != EOF)
    {
       
        index = tolower(word[0]) % 97;
        if (index > 25)
            index = SPECIAL_INDEX;

        
        main_node *mtemp = arr[index].link;
        main_node *mprev = NULL;

        while (mtemp)
        {
            if (strcmp(mtemp->word, word) == 0)
                break;

            mprev = mtemp;
            mtemp = mtemp->mlink;
        }

        /* word not present in this bucket yet */
        if (mtemp == NULL)
        {
            main_node *new_word = malloc(sizeof(main_node));

            if (new_word == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            strcpy(new_word->word, word);
            new_word->file_count = 1;
            new_word->mlink = NULL;
            new_word->sublink = NULL;

            sub_node *new_file = malloc(sizeof(sub_node));

            if (new_file == NULL)
            {
                free(new_word);
                fclose(fp);
                return FAILURE;
            }

            strcpy(new_file->filename, filename);
            new_file->word_count = 1;
            new_file->slink = NULL;

            new_word->sublink = new_file;

            if (mprev == NULL)
                arr[index].link = new_word;
            else
                mprev->mlink = new_word;
        }

        /* word already exists in this bucket */
        else
        {
            sub_node *stemp = mtemp->sublink;
            sub_node *sprev = NULL;

            while (stemp)
            {
                if (strcmp(stemp->filename, filename) == 0)
                    break;

                sprev = stemp;
                stemp = stemp->slink;
            }

            /* same word + same file */
            if (stemp)
            {
                stemp->word_count++;
            }

            /* same word + new file */
            else
            {
                sub_node *new_file = malloc(sizeof(sub_node));

                if (new_file == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_file->filename, filename);
                new_file->word_count = 1;
                new_file->slink = NULL;

                if (sprev == NULL)        
                    mtemp->sublink = new_file;
                else
                    sprev->slink = new_file;

                mtemp->file_count++;
            }
        }
    }

    fclose(fp);

    return SUCCESS;
}