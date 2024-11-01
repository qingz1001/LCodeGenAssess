#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXK 20005

typedef struct Edge {
    int to, next;
    int cost;
    char *password;
} Edge;

Edge edges[MAXN << 1];
int head[MAXN], edgeIndex;
int n, m, k;

struct TrieNode {
    struct TrieNode *children[26];
    char *password;
};

struct TrieNode *root;

void addEdge(int from, int to, int cost, char *password) {
    edges[edgeIndex].to = to;
    edges[edgeIndex].next = head[from];
    edges[edgeIndex].cost = cost;
    edges[edgeIndex].password = password;
    head[from] = edgeIndex++;
}

void insertTrie(char *word) {
    struct TrieNode *node = root;
    for (int i = 0; word[i]; i++) {
        if (!node->children[word[i] - 'a']) {
            node->children[word[i] - 'a'] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            memset(node->children[word[i] - 'a'], 0, sizeof(struct TrieNode));
        }
        node = node->children[word[i] - 'a'];
    }
    node->password = strdup(word);
}

int lcp(char *s1, char *s2) {
    int len = 0;
    while (s1[len] && s2[len] && s1[len] == s2[len]) len++;
    return len;
}

void dfs(int u, int parent, int *dist) {
    dist[u] = 0;
    struct TrieNode *node = root;
    for (int e = head[u]; ~e; e = edges[e].next) {
        int v = edges[e].to;
        if (v != parent) {
            dfs(v, u, dist);
            int lcpLen = lcp(dist[v], edges[e].password);
            dist[u] += edges[e].cost + lcpLen;
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &k);
        for (int i = 0; i <= n; i++) head[i] = -1;
        edgeIndex = 0;
        free(root);
        root = (struct TrieNode *)malloc(sizeof(struct TrieNode));
        memset(root, 0, sizeof(struct TrieNode));

        for (int i = 0; i < m; i++) {
            int a, b, c;
            char password[20005];
            scanf("%d %d %d %s", &a, &b, &c, password);
            addEdge(a, b, c, password);
            insertTrie(password);
        }

        for (int i = 0; i < k - 1; i++) {
            int u, v;
            char w;
            scanf("%d %d %c", &u, &v, &w);
            insertTrie((char[]){w, '\0'});
        }

        int *dist = (int *)calloc(n + 1, sizeof(int));
        dfs(1, -1, dist);

        for (int i = 2; i <= n; i++) {
            printf("%d\n", dist[i]);
        }

        free(dist);
    }
    return 0;
}