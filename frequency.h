#ifndef __FREQUENCY__H
#define __FREQUENCY__H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_LETTERS ((int)27)
typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean;

typedef struct node
{
    char letter;
    long unsigned int count;
    struct node **children;
    char *unvisitedNodesAtPrintLoopRunTime;
} node;
char *get_word(int *i);
void tree_builder(char *c, int len, node *root);
node *node_builder(char c);
int hash_func(int i);
#endif