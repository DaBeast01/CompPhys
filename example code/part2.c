#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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
    int poschange = 50;
    int counter = 0;
    bool ZeroCheck = false;

    file = fopen("part1text.txt", "r");
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
            operation->turn *= -1;

        position += operation->turn;
        poschange += operation->turn;
        fprintf(a, "\nCounter: %i\n", counter);
        fprintf(a, "Cumulative: %i\n", poschange);
        if (position < 0) {
            if (ZeroCheck)
                counter--;
            counter += (abs(position/100) + 1);
        }
        else if (position > 0) {
            counter += (abs(position/100));
        }

        if (position == 0) {
            counter++;
        }
        ZeroCheck = false;
        position = (poschange % 100 + 100) % 100;

        if (position == 0) {
            ZeroCheck = true;
        }

        fprintf(a, "Position: %i\n", position);
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
            if (tempnode->direction != 'F') {
                tempnode->next = calloc(1, sizeof(node));
                tempnode = tempnode->next;
            }

            tempnode->direction = buffer[0];

            for (int j = 0; j < i - 2; j++) {
                tempnode->turn = tempnode->turn + ((buffer[j+1] - '0') * power(10, i - j - 3));
            }

            tempnode->next = 0;

            // fprintf(a, "Direction: %c\nTurn: %i\n\n", tempnode->direction, tempnode->turn);

            // Wipes the buffer array
            for (int j = 0; j < 6; j++)
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