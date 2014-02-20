//Steven Volocyk, Lecture 001
/* This program reads a file of human-readabl integers,
and reverses the contents via a stack and linked-list
implementation*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
 
// node creating struct. 
typedef struct node {
    int data;//data inside node
    struct node *next; //pointer 
} Node;
 
int pop(Node **topOfStack);
Node* push(Node *topOfStack, int valueToPush);

/* This function adds a new node to an existing,
or non-existant stack and creates new pointers
pointing at the top of the new and updated stack
params: Pointer to top of stack, value to put within
the new node being pushed 
returns: 0 relative to errors, or a pointer to 
the new node*/
Node* push(Node *topOfStack, int valueToPush) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) { 
        return 0; 
    }
    
    newNode->data = valueToPush;
    newNode->next = topOfStack;
    return newNode;
}
 /* This function removes a node from the top
 of the stack, and manipulates pointers in order
 to point at the NEW top of the stack after removing 
 a node. 
 Params: Pointer to a pointer at the top of the stack
 returns: 0 if errors, otherwise data inside node
 */
int pop(Node **topOfStack) {
    if (!topOfStack || !*topOfStack) {
        return 0;
    }
    
    Node *node = *topOfStack;
    int data = node->data;
    
    *topOfStack = (node->next);
    free(node);
    return data;    
}
//Implementation/building of stack and printing 
//functionality. 
int main(int argc, char *argv[]) {
    Node *stack = NULL;//new stack
    FILE *inputFile, *outputFile; //IO pointers

    int number;
 
    if (argc != 3) {
        fprintf(stderr, "Usage: strrev <inputfile> <outputfile> ");
        exit(1);
    }
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Error reading file\n");
    }
 
    while (!feof(inputFile) && fscanf(inputFile, "%d;", &number) > 0) {
        stack = push(stack, number);
        printf("%d\n", number);
        if (!stack) {
            printf("Error pushing %d\n", number);
            exit(1);
        }    
    }        
 
    int ret = 0; //return var
    int data = 0;// for function return values
    outputFile = fopen(argv[2], "w");
    if (outputFile) {   
        do {
            data = pop(&stack);
            if (data > 0) {
                fprintf(outputFile, "%d\n", data);
            }
        } while (data != 0);
    }       
    else {
        printf("could not open file %s\n", argv[2]);
        ret = 1;
    }
    fclose(inputFile);
    fclose(outputFile);
    return ret;
}