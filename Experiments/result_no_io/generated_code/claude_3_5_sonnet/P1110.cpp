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
        Node* current = arr[i];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int min_gap() {
    int min = INT_MAX;
    int prev = -1;
    
    for (int i = 0; i < n; i++) {
        Node* current = arr[i];
        while (current != NULL) {
            if (prev != -1) {
                int gap = abs(current->value - prev);
                if (gap < min) {
                    min = gap;
                }
            }
            prev = current->value;
            current = current->next;
        }
    }
    
    return min;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int min_sort_gap() {
    int index = 0;
    for (int i = 0; i < n; i++) {
        Node* current = arr[i];
        while (current != NULL) {
            sorted[index++] = current->value;
            current = current->next;
        }
    }
    
    qsort(sorted, index, sizeof(int), compare);
    
    int min = INT_MAX;
    for (int i = 1; i < index; i++) {
        int gap = sorted[i] - sorted[i-1];
        if (gap < min) {
            min = gap;
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
    
    for (int i = 0; i < m; i++) {
        char command[15];
        scanf("%s", command);
        
        if (strcmp(command, "INSERT") == 0) {
            int index, value;
            scanf("%d %d", &index, &value);
            insert(index - 1, value);
        } else if (strcmp(command, "MIN_GAP") == 0) {
            printf("%d\n", min_gap());
        } else if (strcmp(command, "MIN_SORT_GAP") == 0) {
            printf("%d\n", min_sort_gap());
        }
    }
    
    return 0;
}