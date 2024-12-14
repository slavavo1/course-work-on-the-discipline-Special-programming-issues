#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> 

#define MAX_SIZE_TEXT 60 


/**
 * @brief      { структура узла }
 */
struct node {
   char* data;
   int key;
   struct node *next;
};
