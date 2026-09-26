#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

int search_database(hash_t arr[], char *search_word)
{
    int index;
    char word[SIZE];

   
    strcpy(word, search_word);

   
    index = tolower(word[0]) % 97;
    if (index > 25)
        index = SPECIAL_INDEX;

    /* traverse the main_node chain in this bucket */
    main_node *mtemp = arr[index].link;

    while (mtemp)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("\nWord %s is present in %d files.\n",
                   word,
                   mtemp->file_count);

            /* display file information */
            sub_node *stemp = mtemp->sublink;

            while (stemp)
            {
                printf("\nIn file %s %d times.\n",
                       stemp->filename,
                       stemp->word_count);

                stemp = stemp->slink;
            }

            return SUCCESS;
        }

        mtemp = mtemp->mlink;
    }

    printf("\nWord %s is not present in database.\n", word);

    return FAILURE;
}