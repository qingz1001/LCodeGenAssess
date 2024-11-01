#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 30000
#define MAX_N 2000

typedef struct Node {
    struct Node *next[2];
    int is_end;
} Node;

Node *create_node() {
    Node *node = (Node *)malloc(sizeof(Node));
    node->next[0] = node->next[1] = NULL;
    node->is_end = 0;
    return node;
}

void insert(Node *root, char *str) {
    Node *p = root;
    for (int i = 0; str[i]; i++) {
        int idx = str[i] - '0';
        if (!p->next[idx]) {
            p->next[idx] = create_node();
        }
        p = p->next[idx];
    }
    p->is_end = 1;
}

int dfs(Node *node) {
    if (node->is_end) return 0;
    if (node->next[0] && !dfs(node->next[0])) return 1;
    if (node->next[1] && !dfs(node->next[1])) return 1;
    return 0;
}

int main() {
    int n;
    char virus[MAX_LEN + 1];
    Node *root = create_node();

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", virus);
        insert(root, virus);
    }

    if (dfs(root)) {
        printf("TAK\n");
    } else {
        printf("NIE\n");
    }

    return 0;
}