#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

typedef struct Node {
    int value;
    struct Node* next;
} Node;

Node* head[MAXN];
int minGap[MAXN];
int minSortGap[MAXN];

void init(int n) {
    for (int i = 0; i <= n; i++) {
        head[i] = NULL;
        minGap[i] = INT_MAX;
        minSortGap[i] = INT_MAX;
    }
}

void insert(int pos, int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = val;
    newNode->next = NULL;

    if (head[pos] == NULL) {
        head[pos] = newNode;
    } else {
        Node* current = head[pos];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Update minGap and minSortGap
    updateMinGap(pos);
    updateMinSortGap();
}

void updateMinGap(int pos) {
    if (pos > 0 && head[pos - 1] != NULL) {
        Node* prev = head[pos - 1];
        Node* current = head[pos];
        int gap = abs(prev->value - current->value);
        if (gap < minGap[pos]) {
            minGap[pos] = gap;
        }
    }
    if (pos < MAXN - 1 && head[pos + 1] != NULL) {
        Node* current = head[pos];
        Node* next = head[pos + 1];
        int gap = abs(current->value - next->value);
        if (gap < minGap[pos + 1]) {
            minGap[pos + 1] = gap;
        }
    }
}

void updateMinSortGap() {
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    for (int i = 0; i < MAXN; i++) {
        Node* current = head[i];
        while (current != NULL) {
            if (current->value < minVal) {
                minVal = current->value;
            }
            if (current->value > maxVal) {
                maxVal = current->value;
            }
            current = current->next;
        }
    }
    minSortGap[0] = minVal;
    minSortGap[MAXN] = maxVal;
    for (int i = 1; i < MAXN; i++) {
        minSortGap[i] = INT_MAX;
        Node* current = head[i - 1];
        while (current != NULL) {
            Node* next = head[i];
            while (next != NULL) {
                int gap = abs(current->value - next->value);
                if (gap < minSortGap[i]) {
                    minSortGap[i] = gap;
                }
                next = next->next;
            }
            current = current->next;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    init(n);

    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insert(i, val);
    }

    char op[10];
    for (int i = 0; i < m; i++) {
        scanf("%s", op);
        if (op[0] == 'I') {
            int pos, val;
            scanf("%d %d", &pos, &val);
            insert(pos - 1, val);
        } else if (op[0] == 'M' && op[1] == 'I') {
            printf("%d\n", minGap[n]);
        } else if (op[0] == 'M' && op[1] == 'S') {
            printf("%d\n", minSortGap[n]);
        }
    }

    return 0;
}