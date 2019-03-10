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

typedef struct node {
    int val;
    struct node *next;
} Node;


/* Makes a new node structure.
*
* val: value to store in the node.
* next: pointer to the next node
*
* returns: pointer to a new node
*/
Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}


/* Prints the values in a list.
*
* list: pointer to pointer to Node
*/
void print_list(Node **list) {
    Node *current = *list;

    printf("[ ");
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("]\n");
}


/* Removes and returns the first element of a list.
*
* list: pointer to pointer to Node
*
* returns: int or -1 if the list is empty
*/
int pop(Node **list) {
    Node *curr = *list;
    // Return -1 when the list is empty
    if (curr == NULL){
      return -1;
    }
    // Make the double pointer points to the new head
    *list = curr->next;
    return 0;
}


/* Adds a new element to the beginning of the list.
*
* list: pointer to pointer to Node
* val: value to add
*/
void push(Node **list, int val) {
    Node *newHead = make_node(val, *list);
    // Make the double pointer points to the new head
    *list = newHead;
}


/* Removes the first element with the given value
*
* Frees the removed node.
*
* list: pointer to pointer to Node
* val: value to remove
*
* returns: number of nodes removed
*/
int remove_by_value(Node **list, int val) {
    Node *curr = *list;
    Node *prev;
    // If the head node holds the value to be removed
    if (curr != NULL && curr->val == val){
      *list = curr->next;   // Change head node
      free(curr);           // Free removed node
      return 1;
    }
    // Search for the first occurance of node to be removed
    while (curr != NULL && curr->val != val) {
        prev = curr;        // Keep track of previous node
        curr = curr->next;  // Traverse the rest of node
    }
    if (curr == NULL){      // If val is not found in the list
      return 0;
    }
    prev->next = curr->next;// Build new connection for nodes
    free(curr);
    return 1;
}


/* Reverses the elements of the list.    free(curr);
    return 1;
}
*
* Does not allocate or free nodes.
*
* list: pointer to pointer to Node
*/
void reverse(Node **list) {
    Node *curr = *list;
    Node *prev = NULL;
    Node *next;
    // Loop through every element of the list
    while (curr != NULL){
        next = curr->next;  // Store next node
        curr->next = prev;  // Reverse current node's pointer
        prev = curr;        // Update previous and current node
        curr = next;
    }
    // Link new head to pointer
    *list = prev;
}


int main() {
    Node *head = make_node(1, NULL);
    head->next = make_node(2, NULL);
    head->next->next = make_node(3, NULL);
    head->next->next->next = make_node(4, NULL);

    Node **list = &head;
    print_list(list);

    int retval = pop(list);
    print_list(list);

    push(list, retval+10);
    print_list(list);

    remove_by_value(list, 3);
    print_list(list);

    remove_by_value(list, 7);
    print_list(list);

    reverse(list);
    print_list(list);
}
