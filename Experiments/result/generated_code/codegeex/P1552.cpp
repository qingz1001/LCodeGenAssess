#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 1000000000

typedef struct Node {
    int c, l;
    struct Node *next;
} Node;

int n, m;
int dp[MAXM + 1];
Node *tree[MAXN];

void addNode(int u, int c, int l) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->c = c;
    newNode->l = l;
    newNode->next = tree[u];
    tree[u] = newNode;
}

void dfs(int u) {
    Node *v = tree[u];
    while (v != NULL) {
        dfs(v->c);
        v = v->next;
    }
    v = tree[u];
    while (v != NULL) {
        int c = v->c;
        Node *w = tree[c];
        while (w != NULL) {
            int lc = w->c;
            for (int j = m; j >= 0; j--) {
                if (dp[j] < dp[j - v->c] + w->l) {
                    dp[j] = dp[j - v->c] + w->l;
                }
            }
            w = w->next;
        }
        v = v->next;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int b, c, l;
        scanf("%d %d %d", &b, &c, &l);
        addNode(i, c, l);
    }
    dfs(0);
    int max = 0;
    for (int i = 0; i <= m; i++) {
        if (dp[i] > max) {
            max = dp[i];
        }
    }
    printf("%d\n", max);
    return 0;
}