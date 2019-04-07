/*  This program is used to count word frequencies in GLib.
You can run this program by compile makefile

Author: Enmo Ren
Copyright (c) Enmo Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software.

*/

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

gchar* getContents(gchar* filename){
  gssize length;
  gchar* content;
  GError *error = NULL;
  if (g_file_get_contents (filename, &content, &length, &error)) {
        return g_strdup(content);
        // g_free (content);
  }
  // Error checking if the file can not be read
  else{
      g_error("g_file_get_contents() failed: %s\n", error->message);
      g_error_free (error);
      exit(EXIT_FAILURE);
  }
}
/*
  Helper function to format key-value pair
*/
void print_hashes(gpointer key, gpointer value, gpointer udata){
  printf("%s: %d\n", (char*)key, GPOINTER_TO_INT(value));
}

void processText(gchar* content){
  GHashTable* hash_table = g_hash_table_new(g_str_hash, g_str_equal);
  // Split string based on whitespace
  gchar **ptrWord = g_strsplit(content, " ", -1);
  // Tranverse through gchar pointer array
  for (gchar **ptr = ptrWord; *ptr; ptr++){
    if (g_hash_table_contains (hash_table, *ptr)==FALSE){
      // if the key does not exist in the hashtable, insert new key value pair
      g_hash_table_insert(hash_table, g_strdup(*ptr), g_hash_table_lookup(hash_table, g_strdup(*ptr))+1);
    }
    else{
      // if the key already exists in the hashtable, update key value pair
      g_hash_table_insert(hash_table, g_strdup(*ptr), GINT_TO_POINTER(1));
    }
  }
  // Loop through hash table and print every key-value pair
  g_hash_table_foreach (hash_table, print_hashes, NULL);
}

int main(int argc, char** argv) {
  // Default text file
  gchar* filename = "ebook.txt";
  gchar* content = getContents(filename);
  processText(content);
  return 0;
}
