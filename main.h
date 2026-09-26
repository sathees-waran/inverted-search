#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

#define SIZE 50
#define TABLE_SIZE 26          /* buckets 0-25 : 'a' to 'z'          */
#define SPECIAL_INDEX 26       /* bucket 26    : digits/symbols/etc. */
#define TOTAL_BUCKETS (TABLE_SIZE + 1)


/* sub_node : one FILE entry for a given word */
typedef struct sub_node
{
    int word_count;
    char filename[SIZE];
    struct sub_node *slink;      /* next file this word appears in */

} sub_node;


/* main_node : one WORD entry inside a hash bucket */
typedef struct main_node
{
    int file_count;               /* how many different files this word is in */
    char word[SIZE];
    sub_node *sublink;            /* -> per-file counts for this word */
    struct main_node *mlink;      /* -> next word that hashed to the SAME bucket */

} main_node;


/* hash_t : one bucket of the hash table array */
typedef struct hash_t
{
    int index;
    main_node *link;              /* -> first word (main_node) in this bucket */

} hash_t;


/* flist : validated filename list (built before database creation) */
typedef struct flist
{
    char filename[SIZE];
    struct flist *link;

} flist;


/* Function prototypes */

int create_database(hash_t arr[], flist *head);

void display_database(hash_t arr[]);

int search_database(hash_t arr[], char *word);

int update_database(hash_t arr[], char *filename);

int save_database(hash_t arr[], char *filename);

int validate_files(int argc, char *argv[], flist **head);

#endif