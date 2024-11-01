#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 6005

typedef struct Node {
    int id;
    int happy;
    struct Node* parent;
    struct Node* children;
    struct Node* next;
} Node;

Node nodes[MAXN];
int dp[MAXN][2];

void dfs(Node* node) {
    dp[node->id][0] = 0;
    dp[node->id][1] = node->happy;

    Node* child = node->children;
    while (child != NULL) {
        dfs(child);
        dp[node->id][0] += (dp[child->id][1] > dp[child->id][0] ? dp[child->id][1] : dp[child->id][0]);
        dp[node->id][1] += dp[child->id][0];
        child = child->next;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &nodes[i].happy);
        nodes[i].id = i;
        nodes[i].parent = NULL;
        nodes[i].children = NULL;
        nodes[i].next = NULL;
    }

    for (int i = 1; i < n; i++) {
        int l, k;
        scanf("%d %d", &l, &k);
        nodes[l].parent = &nodes[k];
        nodes[l].next = nodes[k].children;
        nodes[k].children = &nodes[l];
    }

    Node* root = NULL;
    for (int i = 1; i <= n; i++) {
        if (nodes[i].parent == NULL) {
            root = &nodes[i];
            break;
        }
    }

    dfs(root);

    printf("%d\n", dp[root->id][1] > dp[root->id][0] ? dp[root->id][1] : dp[root->id][0]);

    return 0;
}