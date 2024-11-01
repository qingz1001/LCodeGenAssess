#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 250000
#define MAX_WORD_LENGTH 11

typedef struct Node {
    char color[MAX_WORD_LENGTH];
    int count;
    struct Node *next;
} Node;

Node *nodes[MAX_WORDS];
int nodeCount = 0;

void addColor(char *color) {
    for (int i = 0; i < nodeCount; i++) {
        if (strcmp(nodes[i]->color, color) == 0) {
            nodes[i]->count++;
            return;
        }
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->color, color);
    newNode->count = 1;
    newNode->next = NULL;
    nodes[nodeCount++] = newNode;
}

int main() {
    char color1[MAX_WORD_LENGTH], color2[MAX_WORD_LENGTH];
    while (scanf("%s %s", color1, color2) != EOF) {
        addColor(color1);
        addColor(color2);
    }

    int oddCount = 0;
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i]->count % 2 != 0) {
            oddCount++;
        }
    }

    if (oddCount == 0) {
        printf("Possible\n");
    } else {
        printf("Impossible\n");
    }

    for (int i = 0; i < nodeCount; i++) {
        free(nodes[i]);
    }

    return 0;
}