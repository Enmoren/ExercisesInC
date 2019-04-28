/* Example code for Exercises in C

Copyright 2016 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

Started with ex-ghashtable-3.c from
http://www.ibm.com/developerworks/linux/tutorials/l-glib/section5.html

This program is modified by Enmo Ren to solve the leaking memory problems. In order
to avoid sharing allocated chunks between different data structures, I make copies
of data that should be added to a new data structures and free all the allocated
chunks at the end. 

make word_count
valgrind --leak-check=yes ./word_count

Result:
==14861== HEAP SUMMARY:
==14861==     in use at exit: 18,604 bytes in 6 blocks
==14861==   total heap usage: 497,782 allocs, 497,776 frees, 9,590,081 bytes allocated
==14861==
==14861== LEAK SUMMARY:
==14861==    definitely lost: 0 bytes in 0 blocks
==14861==    indirectly lost: 0 bytes in 0 blocks
==14861==      possibly lost: 0 bytes in 0 blocks
==14861==    still reachable: 18,604 bytes in 6 blocks
==14861==         suppressed: 0 bytes in 0 blocks
==14861== Reachable blocks (those to which a pointer was found) are not shown.
==14861== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==14861==
==14861== For counts of detected and suppressed errors, rerun with: -v
==14861== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
No error!!!


*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gstdio.h>

/* Represents a word-frequency pair. */
typedef struct {
    gint freq;
    gchar *word;
} Pair;

/* Compares two key-value pairs by frequency. */
gint compare_pair(gpointer v1, gpointer v2, gpointer user_data)
{
    Pair *p1 = (Pair *) v1;
    Pair *p2 = (Pair *) v2;
    return p1->freq - p2->freq;
}

/* Iterator that prints pairs. */
void pair_printor(gpointer value, gpointer user_data)
{
    Pair *pair = (Pair *) value;
    printf("%d\t %s\n", pair->freq, pair->word);
}


/* Iterator that prints keys and values. */
void kv_printor (gpointer key, gpointer value, gpointer user_data)
{
    printf(user_data, key, *(gint *) value);
}


/* Iterator that adds key-value pairs to a sequence. */
void accumulator(gpointer key, gpointer value, gpointer user_data)
{
    GSequence *seq = (GSequence *) user_data;
    Pair *pair = g_new(Pair, 1);
    // gint freq = *(gint *) value;
    // gint *freq1 = g_new(gint, 1);
    // *freq1 = freq;
    pair->word = g_strdup((gchar*)key); //Make copies of key to avoid sharing allocated chunks between data structures
    pair->freq = *(gint *) value;

    g_sequence_insert_sorted(seq,
        (gpointer) pair,
        (GCompareDataFunc) compare_pair,
        NULL);
}

/* Increments the frequency associated with key. */
void incr(GHashTable* hash, gchar *key)
{
    gint *val = (gint *) g_hash_table_lookup(hash, key);

    if (val == NULL) {
        gint *val1 = g_new(gint, 1);
        *val1 = 1;
        g_hash_table_insert(hash, g_strdup(key), val1); //Make copies of key to avoid sharing allocated chunks between data structures
    } else {
        *val += 1;
    }
}

/* Freed the allocated chunks associated with hash map. */
void destroy_hash(gpointer key, gpointer value, gpointer udata){
    g_free((char*)key);
    g_free((int*)value);
}

/* Freed the allocated chunks associated with sequence. */
void destroy_seq(gpointer value, gpointer user_data)
{
      Pair *pair = (Pair *) value;
      g_free(pair->word);
      g_free(pair);
}

int main(int argc, char** argv)
{
    gchar *filename;

    // open the file
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "emma.txt";
    }

    FILE *fp = g_fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        exit(-10);
    }

    /* string array is a(two-L) NULL terminated array of pointers to
    (one-L) NUL terminated strings */
    gchar **array;
    gchar line[128];
    GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

    // read lines from the file and build the hash table
    while (1) {
        gchar *res = fgets(line, sizeof(line), fp);
        if (res == NULL) break;

        array = g_strsplit(line, " ", 0);
        for (int i=0; array[i] != NULL; i++) {
            incr(hash, array[i]);
        }
        g_strfreev(array);//Freed allocated array of pointers
    }
    fclose(fp);

    // print the hash table
    // g_hash_table_foreach(hash, (GHFunc) kv_printor, "Word %s freq %d\n");

    // iterate the hash table and build the sequence
    GSequence *seq = g_sequence_new(NULL);
    g_hash_table_foreach(hash, (GHFunc) accumulator, (gpointer) seq);

    // iterate the sequence and print the pairs
    g_sequence_foreach(seq, (GFunc) pair_printor, NULL);

    // iterate the hash table and sequence using the helper functions to freed the memory
    g_sequence_foreach(seq, destroy_seq, NULL);
    g_hash_table_foreach(hash, destroy_hash, NULL);

    g_hash_table_destroy(hash);
    g_sequence_free(seq);

    return 0;
}
