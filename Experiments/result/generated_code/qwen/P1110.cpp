#include <stdio.h>
#include <stdlib.h>

#define MAXN 500010

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* list[MAXN];

int minGap(int n) {
    int minGap = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        Node* current = list[i];
        while (current != NULL && current->next != NULL) {
            minGap = fmin(minGap, abs(current->value - current->next->value));
            current = current->next;
        }
    }
    return minGap;
}

int minSortGap(int n) {
    int minGap = INT_MAX;
    for (int i = 1; i <= n; ++i) {
        Node* current = list[i];
        while (current != NULL && current->next != NULL) {
            minGap = fmin(minGap, abs(current->value - current->next->value));
            current = current->next;
        }
    }
    return minGap;
}

void insert(int i, int k, int n) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = k;
    newNode->next = NULL;

    if (list[i] == NULL) {
        list[i] = newNode;
    } else {
        Node* current = list[i];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Reorder the list to maintain sorted order
    for (int j = i + 1; j <= n; ++j) {
        Node* prev = NULL;
        Node* current = list[j];
        while (current != NULL && current->value < newNode->value) {
            prev = current;
            current = current->next;
        }
        if (prev == NULL) {
            list[j] = newNode;
            newNode->next = current;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &list[i]->value);
        list[i]->next = NULL;
    }

    char operation[10];
    int i, k;
    for (int t = 0; t < m; ++t) {
        scanf("%s", operation);
        if (operation[0] == 'I') {
            scanf("%d %d", &i, &k);
            insert(i, k, n);
            n++;
        } else if (operation[0] == 'M' && operation[1] == 'I') {
            printf("%d\n", minGap(n));
        } else if (operation[0] == 'M' && operation[1] == 'S') {
            printf("%d\n", minSortGap(n));
        }
    }

    return 0;
}