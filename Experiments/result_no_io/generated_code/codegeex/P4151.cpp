#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXM 100005

typedef long long ll;

struct Edge {
    int to;
    ll weight;
    int next;
} edges[MAXM * 2];

int head[MAXN];
int edgeCount;

void addEdge(int from, int to, ll weight) {
    edges[edgeCount].to = to;
    edges[edgeCount].weight = weight;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

struct Node {
    ll value;
    int next;
} nodes[65 * MAXN];

int nodeCount;
int trie[65 * MAXN][2];

void insert(ll value) {
    int current = 0;
    for (int i = 64; i >= 0; --i) {
        int bit = (value >> i) & 1;
        if (!trie[current][bit]) {
            trie[current][bit] = nodeCount++;
        }
        current = trie[current][bit];
    }
    nodes[current].value = value;
}

ll query(ll value) {
    int current = 0;
    ll result = 0;
    for (int i = 64; i >= 0; --i) {
        int bit = (value >> i) & 1;
        if (trie[current][!bit]) {
            result |= (1LL << i);
            current = trie[current][!bit];
        } else {
            current = trie[current][bit];
        }
    }
    return result ^ value;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));
    edgeCount = 0;

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    nodeCount = 1;
    memset(trie, 0, sizeof(trie));

    insert(0);

    for (int i = 1; i <= n; ++i) {
        for (int j = head[i]; j != -1; j = edges[j].next) {
            ll weight = edges[j].weight;
            ll xorValue = query(weight);
            insert(xorValue);
        }
    }

    ll result = query(0);
    printf("%lld\n", result);

    return 0;
}