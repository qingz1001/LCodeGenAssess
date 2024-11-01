#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2000
#define MAX_LEN 30000

typedef struct Node {
    struct Node *children[2];
    int is_end;
} Node;

Node* create_node() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->children[0] = node->children[1] = NULL;
    node->is_end = 0;
    return node;
}

void insert(Node* root, char* str) {
    Node* curr = root;
    for (int i = 0; str[i]; i++) {
        int index = str[i] - '0';
        if (!curr->children[index]) {
            curr->children[index] = create_node();
        }
        curr = curr->children[index];
    }
    curr->is_end = 1;
}

int dfs(Node* node) {
    if (node->is_end) return 0;
    if (!node->children[0] && !node->children[1]) return 1;
    int res = 0;
    if (node->children[0]) res |= dfs(node->children[0]);
    if (node->children[1]) res |= dfs(node->children[1]);
    return res;
}

int main() {
    int n;
    char virus[MAX_LEN + 1];
    Node* root = create_node();

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