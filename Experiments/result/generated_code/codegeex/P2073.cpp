#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int beauty;
    int cost;
    struct Node *next;
    struct Node *prev;
} Node;

Node *head = NULL;
Node *tail = NULL;

void addFlower(int beauty, int cost) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->beauty = beauty;
    newNode->cost = cost;
    newNode->next = NULL;
    newNode->prev = tail;

    if (tail != NULL) {
        tail->next = newNode;
    } else {
        head = newNode;
    }
    tail = newNode;
}

void removeCheapestFlower() {
    if (head == NULL) return;
    Node *temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    } else {
        tail = NULL;
    }
    free(temp);
}

void removeCostliestFlower() {
    if (tail == NULL) return;
    Node *temp = tail;
    tail = tail->prev;
    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL;
    }
    free(temp);
}

int main() {
    int totalBeauty = 0;
    int totalCost = 0;

    while (1) {
        int op;
        scanf("%d", &op);
        if (op == -1) break;

        if (op == 1) {
            int beauty, cost;
            scanf("%d %d", &beauty, &cost);
            if (head == NULL) {
                addFlower(beauty, cost);
                totalBeauty += beauty;
                totalCost += cost;
            } else {
                Node *current = head;
                while (current != NULL) {
                    if (current->cost == cost) break;
                    current = current->next;
                }
                if (current == NULL) {
                    addFlower(beauty, cost);
                    totalBeauty += beauty;
                    totalCost += cost;
                }
            }
        } else if (op == 2) {
            removeCostliestFlower();
        } else if (op == 3) {
            removeCheapestFlower();
        }
    }

    printf("%d %d\n", totalBeauty, totalCost);
    return 0;
}