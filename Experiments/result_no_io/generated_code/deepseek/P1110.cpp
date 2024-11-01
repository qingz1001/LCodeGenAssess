#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAXN 500005

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertAfter(Node* prev, int value) {
    if (prev == NULL) return;
    Node* newNode = createNode(value);
    newNode->next = prev->next;
    prev->next = newNode;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int absDiff(int a, int b) {
    return abs(a - b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Node* head = createNode(0); // Dummy head node
    Node* tail = head;

    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        tail->next = createNode(value);
        tail = tail->next;
    }

    int minGap = INT_MAX;
    int minSortGap = INT_MAX;

    Node* prev = head;
    Node* curr = head->next;
    while (curr != NULL && curr->next != NULL) {
        minGap = min(minGap, absDiff(curr->value, curr->next->value));
        prev = curr;
        curr = curr->next;
    }

    int* sortedArray = (int*)malloc(sizeof(int) * (n + m));
    curr = head->next;
    for (int i = 0; i < n; i++) {
        sortedArray[i] = curr->value;
        curr = curr->next;
    }

    for (int i = 0; i < n - 1; i++) {
        minSortGap = min(minSortGap, absDiff(sortedArray[i], sortedArray[i + 1]));
    }

    for (int i = 0; i < m; i++) {
        char command[10];
        scanf("%s", command);

        if (command[0] == 'I') {
            int pos, value;
            scanf("%d %d", &pos, &value);

            curr = head;
            for (int j = 0; j < pos; j++) {
                curr = curr->next;
            }

            insertAfter(curr, value);

            if (curr->next != NULL) {
                minGap = min(minGap, absDiff(curr->value, curr->next->value));
            }
            if (curr->next->next != NULL) {
                minGap = min(minGap, absDiff(curr->next->value, curr->next->next->value));
            }

            // Update sorted array
            int index = 0;
            while (index < n + i && sortedArray[index] < value) {
                index++;
            }
            for (int j = n + i; j > index; j--) {
                sortedArray[j] = sortedArray[j - 1];
            }
            sortedArray[index] = value;

            minSortGap = min(minSortGap, absDiff(sortedArray[index], sortedArray[index - 1]));
            minSortGap = min(minSortGap, absDiff(sortedArray[index], sortedArray[index + 1]));

        } else if (command[0] == 'M' && command[4] == 'G') {
            printf("%d\n", minGap);
        } else if (command[0] == 'M' && command[4] == 'S') {
            printf("%d\n", minSortGap);
        }
    }

    free(sortedArray);
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}