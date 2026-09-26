#include <stdio.h>
#include "main.h"

void display_database(hash_t arr[])
{
    int i;

    printf("-------------------------------------------------------------------------------\n");
    printf("%-12s%-16s%-16s%-16s%-10s\n",
           "index",
           "word",
           "filecount",
           "filename",
           "wordcount");
    printf("-------------------------------------------------------------------------------\n");

    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        main_node *mtemp = arr[i].link;

        
        while (mtemp != NULL)
        {
            sub_node *stemp = mtemp->sublink;

          
            if (stemp != NULL)
            {
                printf("%-12d%-16s%-16d%-16s%-10d\n",
                       i,
                       mtemp->word,
                       mtemp->file_count,
                       stemp->filename,
                       stemp->word_count);

                stemp = stemp->slink;
            }

            while (stemp != NULL)
            {
                printf("%-12s%-16s%-16s%-16s%-10d\n",
                       "",
                       "",
                       "",
                       stemp->filename,
                       stemp->word_count);

                stemp = stemp->slink;
            }

            mtemp = mtemp->mlink;

            printf("\n");
        }
    }

    printf("-------------------------------------------------------------------------------\n");
}