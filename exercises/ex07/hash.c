/*  Implementations of linked list in c

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
#include <string.h>


// VALUE: represents a value in a key-value pair

/* Here's one way of making a polymorphic object in C */

typedef struct {
    enum Type {INT, STRING} type;
    union {
        int i;
        char *s;
    };
} Value;


/* Makes a Value object that contains an int.
*
* i: value to store.
*
* returns: pointer to a new Value
*/
Value *make_int_value(int i)
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = INT;
    value->i = i;
    return value;
}


/* Makes a Value object that contains a string.
*
* s: value to store.
*
* returns: pointer to a new Value
*/
Value *make_string_value(char *s)
{
    Value *value = (Value *) malloc (sizeof (Value));
    value->type = STRING;
    value->s = s;
    return value;
}


/* Prints a value object.
*
* value: pointer to Value
*
*/
void print_value (Value *value)
{
    if (value == NULL) {
        printf ("%p", value);
        return;
    }
    switch (value->type) {
        case INT:
        printf ("%d", value->i);
        break;
        case STRING:
        printf ("%s", value->s);
        break;
    }
}

// HASHABLE: Represents a key in a key-value pair.

/* Here's another way to make a polymorphic object.

The key can be any pointer type.  It's stored as a (void *), so
when you extract it, you have to cast it back to whatever it is.

`hash` is a pointer to a function that knows how to hash the key.
`equal` is a pointer to a function that knows how to compare keys.

*/

typedef struct {
    void *key;
    int (*hash) (void *);
    int (*equal) (void *, void *);
} Hashable;


/* Makes a Hashable object.
*
* key: pointer to anything
* hash: function that can hash keys
* equal: function that compares keys
*
* returns: pointer to Hashable
*
*/
Hashable *make_hashable(void *key,
    int (*hash) (void *),
    int (*equal) (void *, void *))
{
    Hashable *hashable = (Hashable *) malloc (sizeof (Hashable));
    hashable->key = key;
    hashable->hash = hash;
    hashable->equal = equal;
    return hashable;
}


/* Prints a Hashable object.
*
* hashable: pointer to hashable
*/
void print_hashable(Hashable *hashable)
{
    printf ("key %p\n", hashable->key);
    printf ("hash %p\n", hashable->hash);
}


/* Hashes an integer.
*
* p: pointer to integer
*
* returns: integer hash value
*/
int hash_int(void *p)
{
    return *(int *)p;
}


/* Hashes a string.
*
* p: pointer to first char of a string
*
* returns: integer hash value
*/
int hash_string(void *p)
{
    char *s = (char *) p;
    int total = 0;
    int i = 0;

    while (s[i] != 0) {
        total += s[i];
        i++;
    }
    return total;
}


/* Hashes any Hashable.
*
* hashable: Hashable object
*
* returns: int hash value
*/
int hash_hashable(Hashable *hashable)
{
    return hashable->hash (hashable->key);
}


/* Compares integers.
*
* ip: pointer to int
* jp: pointer to int
*
* returns: 1 if equal, 0 otherwise
*/
int equal_int (void *ip, void *jp)
{
    int i = *(int *)ip; //cast void pointer to int pointer and then dereference it
    int j = *(int *)jp;
    if (i != j)         //return 0 if two integers are not equal
    {
      return 0;
    }
    return 1;
}


/* Compares strings.
*
* s1: pointer to first char of a string
* s2: pointer to first char of a string
*
* returns: 1 if equal, 0 otherwise
*/
int equal_string (void *s1, void *s2)
{
    char *c1 = (char *)s1;  //cast void pointer to string pointer
    char *c2 = (char *)s2;
    for(int i = 0; i < strlen(c1); i++)
    {
        char *ptr = strchr(c1, c2[i]);
        if (!ptr)           //return 0 if two string are not equal
        {
          return 0;
        }
    }
    return 1;
}


/* Compares Hashables.
*
* h1: Hashable
* h2: Hashable of the same type
*
* returns: 1 if equal, 0 otherwise
*
*/
int equal_hashable(Hashable *h1, Hashable *h2)
{
    return h1->equal(h1->key, h2->key);
}


/* Makes a Hashable int.
*
* Allocates space and copies the int.
*
* x: integer to store
*
* returns: Hashable
*/
Hashable *make_hashable_int (int x)
{
    int *p = (int *) malloc (sizeof (int));
    *p = x;
    return make_hashable((void *) p, hash_int, equal_int);
}


/* Makes a Hashable int.
*
* Stores a reference to the string (not a copy).
*
* s: string to store
*
* returns: Hashable
*/
Hashable *make_hashable_string (char *s)
{
    return make_hashable((void *) s, hash_string, equal_string);
}


// NODE: a node in a list of key-value pairs

typedef struct node {
    Hashable *key;
    Value *value;
    struct node *next;
} Node;


/* Makes a Node. */
Node *make_node(Hashable *key, Value *value, Node *next)
{
    Node *node = (Node *) malloc (sizeof (Node));
    node->key = key;
    node->value = value;
    node->next = next;
    return node;
}


/* Prints a Node. */
void print_node(Node *node)
{
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    printf ("next %p\n", node->next);
}


/* Prints all the Nodes in a list. */
void print_list(Node *node)
{
    if (node == NULL) {
        return;
    }
    print_hashable(node->key);
    printf ("value %p\n", node->value);
    print_list(node->next);
}


/* Prepends a new key-value pair onto a list.

This is actually a synonym for make_node.
*/
Node *prepend(Hashable *key, Value *value, Node *rest)
{
    return make_node(key, value, rest);
}


/* Looks up a key and returns the corresponding value, or NULL */
Value *list_lookup(Node *list, Hashable *key)
{
    while (list != NULL)    //tranverse the node list
    {
      if (list->key == key) //match keys in the list
      {
        return list->value;
      }
      list = list->next;
    }
    return NULL;
}


// MAP: a map is an array of lists of key-value pairs

typedef struct map {
    int n;
    Node **lists;
} Map;


/* Makes a Map with n lists. */
Map *make_map(int n)
{
    int i;

    Map *map = (Map *) malloc (sizeof (Map));
    map->n = n;
    map->lists = (Node **) malloc (sizeof (Node *) * n);
    for (i=0; i<n; i++) {
        map->lists[i] = NULL;
    }
    return map;
}


/* Prints a Map. */
void print_map(Map *map)
{
    int i;

    for (i=0; i<map->n; i++) {
        if (map->lists[i] != NULL) {
            printf ("%d\n", i);
            print_list (map->lists[i]);
        }
    }
}


/* Adds a key-value pair to a map. */
void map_add(Map *map, Hashable *key, Value *value)
{
    int index = key->hash(key->key) % map->n;   //calculate legal index for lists
    Node *list = map->lists[index];             //get list in the map to store new key-value pair
    Node *new_list = prepend(key, value, list); //add new node to the list
    map->lists[index] = new_list;
}


/* Looks up a key and returns the corresponding value, or NULL. */
Value *map_lookup(Map *map, Hashable *key)
{
    int index = key->hash(key->key) % map->n;
    Node *list = map->lists[index];
    Value *value = list_lookup(list, key);
    if (value == NULL)
    {
      return NULL;
    }
    return value;
}


/* Prints the results of a test lookup. */
void print_lookup(Value *value)
{
    printf ("Lookup returned ");
    print_value (value);
    printf ("\n");
}


int main ()
{
    Hashable *hashable1 = make_hashable_int (1);
    Hashable *hashable2 = make_hashable_string ("Apple");
    Hashable *hashable3 = make_hashable_int (2);

    // make a list by hand
    Value *value1 = make_int_value (17);
    Node *node1 = make_node(hashable1, value1, NULL);
    print_node (node1);

    Value *value2 = make_string_value ("Orange");
    Node *list = prepend(hashable2, value2, node1);
    print_list (list);

    // run some test lookups
    Value *value = list_lookup (list, hashable1);
    print_lookup(value);

    value = list_lookup (list, hashable2);
    print_lookup(value);

    value = list_lookup (list, hashable3);
    print_lookup(value);

    // make a map
    Map *map = make_map(10);
    map_add(map, hashable1, value1);
    map_add(map, hashable2, value2);

    printf ("Map\n");
    print_map(map);

    // run some test lookups
    value = map_lookup(map, hashable1);
    print_lookup(value);

    value = map_lookup(map, hashable2);
    print_lookup(value);

    value = map_lookup(map, hashable3);
    print_lookup(value);

    return 0;
}
