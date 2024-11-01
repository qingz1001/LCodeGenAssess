#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 500005
#define MAX_M 500005

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* arr[MAX_N];
int sorted[MAX_N * 2];
int n, m;

void insert(int i, int k) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = k;
    newNode->next = NULL;
    
    if (arr[i] == NULL) {
        arr[i] = newNode;
    } else {
        Node* curr = arr[i];
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int min_gap() {
    int min = INT_MAX;
    int prev = -1;
    
    for (int i = 0; i < n; i++) {
        Node* curr = arr[i];
        while (curr != NULL) {
            if (prev != -1) {
                int diff = abs(curr->value - prev);
                if (diff < min) {
                    min = diff;
                }
            }
            prev = curr->value;
            curr = curr->next;
        }
    }
    
    return min;
}

int min_sort_gap() {
    int index = 0;
    for (int i = 0; i < n; i++) {
        Node* curr = arr[i];
        while (curr != NULL) {
            sorted[index++] = curr->value;
            curr = curr->next;
        }
    }
    
    qsort(sorted, index, sizeof(int), compare);
    
    int min = INT_MAX;
    for (int i = 1; i < index; i++) {
        int diff = sorted[i] - sorted[i-1];
        if (diff < min) {
            min = diff;
        }
    }
    
    return min;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        insert(i, value);
    }
    
    char operation[15];
    for (int i = 0; i < m; i++) {
        scanf("%s", operation);
        
        if (strcmp(operation, "INSERT") == 0) {
            int index, value;
            scanf("%d %d", &index, &value);
            insert(index - 1, value);
        } else if (strcmp(operation, "MIN_GAP") == 0) {
            printf("%d\n", min_gap());
        } else if (strcmp(operation, "MIN_SORT_GAP") == 0) {
            printf("%d\n", min_sort_gap());
        }
    }
    
    return 0;
}