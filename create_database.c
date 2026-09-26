#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

/*
 * create_database.c
 * -----------------
 * creates the inverted search database from valid text files.
 *
 */

int create_database(hash_t arr[], flist *head)
{
    FILE *fp;
    char word[SIZE], filename[SIZE];
    int i, index;

    /* initialize every bucket: set its index, no words yet */
    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        arr[i].index = i;
        arr[i].link = NULL;
    }

    /* pointer to traverse validated file list */
    flist *temp = head;

    /* loop through all valid files, one by one */
    while (temp)
    {
        strcpy(filename, temp->filename);

        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            /* file might be deleted later, so skip */
            temp = temp->link;
            continue;
        }

        /* read each word from file till eof */
        while (fscanf(fp, "%s", word) != EOF)
        {
    
            index = tolower(word[0]) % 97;
            if (index > 25)
                index = SPECIAL_INDEX;

            /* traverse main_node chain in this bucket to find the word */
            main_node *mtemp = arr[index].link;
            main_node *mprev = NULL;

            while (mtemp)
            {
                if (strcmp(mtemp->word, word) == 0)
                    break;

                mprev = mtemp;
                mtemp = mtemp->mlink;
            }

            /* word not present in this bucket yet -> create new main_node */
            if (mtemp == NULL)
            {
                main_node *new_word = malloc(sizeof(main_node));
                if (new_word == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_word->word, word);
                new_word->file_count = 1;      // first file for this word
                new_word->mlink = NULL;
                new_word->sublink = NULL;

                /* create the file entry (sub_node) for this word */
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

                /* attach word node to the bucket's main_node chain */
                if (mprev == NULL)
                    arr[index].link = new_word;
                else
                    mprev->mlink = new_word;
            }
            else /* word already exists in this bucket */
            {
                sub_node *stemp = mtemp->sublink;
                sub_node *sprev = NULL;

                /* check if same file already present for this word */
                while (stemp)
                {
                    if (strcmp(stemp->filename, filename) == 0)
                        break;

                    sprev = stemp;
                    stemp = stemp->slink;
                }

                if (stemp)   // same word, same file
                {
                    stemp->word_count++;
                }
                else        // same word, but a new file
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

        fclose(fp);          // close current file
        temp = temp->link;   // move to next file
    }

    return SUCCESS;
}