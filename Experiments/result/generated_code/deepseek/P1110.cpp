#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAXN 500005

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* head = NULL;
Node* tail = NULL;
Node* nodes[MAXN];
int min_gap = INT_MAX;
int min_sort_gap = INT_MAX;
int sorted_array[MAXN];
int sorted_size = 0;

void insert_node(int index, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;

    if (nodes[index] == NULL) {
        nodes[index] = new_node;
    } else {
        Node* temp = nodes[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }

    if (index < sorted_size) {
        int gap = abs(sorted_array[index] - value);
        if (gap < min_sort_gap) {
            min_sort_gap = gap;
        }
    }

    if (index > 0) {
        Node* prev_node = nodes[index - 1];
        while (prev_node->next != NULL) {
            prev_node = prev_node->next;
        }
        int gap = abs(prev_node->value - value);
        if (gap < min_gap) {
            min_gap = gap;
        }
    }

    sorted_array[sorted_size++] = value;
}

void min_gap_query() {
    printf("%d\n", min_gap);
}

void min_sort_gap_query() {
    printf("%d\n", min_sort_gap);
}

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        insert_node(i, value);
    }

    qsort(sorted_array, sorted_size, sizeof(int), cmp);

    for (int i = 1; i < sorted_size; i++) {
        int gap = sorted_array[i] - sorted_array[i - 1];
        if (gap < min_sort_gap) {
            min_sort_gap = gap;
        }
    }

    char command[10];
    int index, value;
    for (int i = 0; i < m; i++) {
        scanf("%s", command);
        if (strcmp(command, "INSERT") == 0) {
            scanf("%d %d", &index, &value);
            insert_node(index - 1, value);
        } else if (strcmp(command, "MIN_GAP") == 0) {
            min_gap_query();
        } else if (strcmp(command, "MIN_SORT_GAP") == 0) {
            min_sort_gap_query();
        }
    }

    return 0;
}