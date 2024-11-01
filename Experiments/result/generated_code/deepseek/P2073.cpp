#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int W;
    int C;
} Flower;

typedef struct Node {
    Flower flower;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} DoublyLinkedList;

void initList(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

void addFlower(DoublyLinkedList* list, int W, int C) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->flower.W = W;
    newNode->flower.C = C;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        Node* current = list->head;
        while (current != NULL) {
            if (current->flower.C == C) {
                free(newNode);
                return;
            }
            current = current->next;
        }

        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

void removeMostExpensive(DoublyLinkedList* list) {
    if (list->head == NULL) return;

    Node* current = list->head;
    Node* mostExpensive = list->head;

    while (current != NULL) {
        if (current->flower.C > mostExpensive->flower.C) {
            mostExpensive = current;
        }
        current = current->next;
    }

    if (mostExpensive == list->head) {
        list->head = mostExpensive->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    } else if (mostExpensive == list->tail) {
        list->tail = mostExpensive->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    } else {
        mostExpensive->prev->next = mostExpensive->next;
        mostExpensive->next->prev = mostExpensive->prev;
    }

    free(mostExpensive);
}

void removeCheapest(DoublyLinkedList* list) {
    if (list->head == NULL) return;

    Node* current = list->head;
    Node* cheapest = list->head;

    while (current != NULL) {
        if (current->flower.C < cheapest->flower.C) {
            cheapest = current;
        }
        current = current->next;
    }

    if (cheapest == list->head) {
        list->head = cheapest->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
    } else if (cheapest == list->tail) {
        list->tail = cheapest->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
    } else {
        cheapest->prev->next = cheapest->next;
        cheapest->next->prev = cheapest->prev;
    }

    free(cheapest);
}

void calculateTotal(DoublyLinkedList* list, int* totalW, int* totalC) {
    Node* current = list->head;
    *totalW = 0;
    *totalC = 0;

    while (current != NULL) {
        *totalW += current->flower.W;
        *totalC += current->flower.C;
        current = current->next;
    }
}

int main() {
    DoublyLinkedList list;
    initList(&list);
    int totalW = 0, totalC = 0;
    int op, W, C;

    while (1) {
        scanf("%d", &op);
        if (op == -1) break;

        if (op == 1) {
            scanf("%d %d", &W, &C);
            addFlower(&list, W, C);
        } else if (op == 2) {
            removeMostExpensive(&list);
        } else if (op == 3) {
            removeCheapest(&list);
        }
    }

    calculateTotal(&list, &totalW, &totalC);
    printf("%d %d\n", totalW, totalC);

    // Free the list
    Node* current = list.head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    return 0;
}