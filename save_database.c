#include <stdio.h>
#include "main.h"

int save_database(hash_t arr[], char *filename)
{
    FILE *fp;
    int i;

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Unable to open file %s\n", filename);
        return FAILURE;
    }

    for (i = 0; i < TOTAL_BUCKETS; i++)
    {
        main_node *mtemp = arr[i].link;

        while (mtemp)
        {
            
            fprintf(fp, "index[%d] %s %d",
                    i,
                    mtemp->word,
                    mtemp->file_count);

            sub_node *stemp = mtemp->sublink;

            while (stemp)
            {
                fprintf(fp, " %s %d",
                        stemp->filename,
                        stemp->word_count);

                stemp = stemp->slink;
            }

            fprintf(fp, "\n");

            mtemp = mtemp->mlink;
        }
    }

    fclose(fp);

    printf("\nDatabase saved successfully.\n");

    return SUCCESS;
}