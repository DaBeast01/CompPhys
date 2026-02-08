#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

FILE *file;
FILE *a;

typedef struct node {
    char direction;
    int turn;
    struct node* next;
} node;

node *fileParsor(FILE *file);
void freeList(node *start);
int power(int base, int factor);

int main(void) {
    
    int position = 50;
    int counter = 0;

    file = fopen("test.txt", "r");
    a = fopen("filedump.txt", "w");

    if (file == NULL) {
        printf("ts is NOT here");
        return 1;
    }

    printf("ts is here\n");

    node *operation = fileParsor(file);
    node *start = operation;

    while (operation != 0) {
        // if the direction if left, you want to subtract numbers from the count
        if (operation->direction == 'L')
            operation->turn = operation->turn * -1;

        position = (position + operation->turn) % 100;
        if (position < 0)
            position += 100;
        fprintf(a, "%i\n", position);
        if (position == 0)
            counter++;

        operation = operation->next;
    }

    printf("%i\n", counter);
    freeList(start);
    fclose(file);
    return 1;
}

// This function makes the linked list of operations needed
node *fileParsor(FILE *file) {
    node *tempnode = calloc(1, sizeof(node));
    node *start = tempnode;
    char buffer[6] = {'A', 'A', 'A', 'A', 'A', 'A'};
    int i = 0;

    // This is to show the first node created (base case conditon)
    tempnode->direction = 'F';

    // Iterates over buffer until new line, then splits string into parts and puts the properties into a node
    while (fread(&buffer[i], sizeof(char), 1, file) != 0) {
        if (buffer[i] != '\n')
            i++;

        else if (buffer[i] == '\0')
            break;

        else {
            printf("%i\n", i);
            if (tempnode->direction != 'F') {
                tempnode->next = calloc(1, sizeof(node));
                tempnode = tempnode->next;
            }

            tempnode->direction = buffer[0];

            for (int j = 0; j < i - 2; j++) {
                tempnode->turn = tempnode->turn + ((buffer[j+1] - '0') * power(10, i - j - 3));
            }

            tempnode->next = 0;

            fprintf(a, "Direction: %c\nTurn: %i\n\n", tempnode->direction, tempnode->turn);

            // Wipes the buffer array
            for (int j = 0; j < 4; j++)
                buffer[j] = 'A';
            i = 0;
        }
    }
    return start;
}

void freeList(node *start) {
    node *tempnode = start;
    if (tempnode->next != 0)
        freeList(tempnode->next);
    free(tempnode);
    return;
}

int power(int base, int factor) {
    int result = 1;
    for (int i = 0; i < factor; i++)
        result *= base;
    return result;
}