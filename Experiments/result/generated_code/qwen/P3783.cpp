#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50005
#define MAXK 20005
#define INF 0x3f3f3f3f

typedef struct {
    int to, cost;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edgeIndex;
int degree[MAXN];

void addEdge(int from, int to, int cost) {
    edges[edgeIndex].to = to;
    edges[edgeIndex].cost = cost;
    edges[edgeIndex].next = head[from];
    head[from] = edgeIndex++;
}

struct TrieNode {
    int fail;
    int len;
    char ch;
    int child[26];
};

struct TrieNode trie[MAXK * 2];
int trieSize;

void insert(const char* s, int len, int id) {
    int p = 1;
    for (int i = 0; i < len; ++i) {
        int u = s[i] - 'a';
        if (!trie[p].child[u]) {
            trie[p].child[u] = ++trieSize;
        }
        p = trie[p].child[u];
    }
    trie[p].fail = id;
}

void buildFail() {
    queue<int> q;
    for (int i = 0; i < 26; ++i) {
        if (trie[1].child[i]) {
            trie[trie[1].child[i]].fail = 1;
            q.push(trie[1].child[i]);
        } else {
            trie[1].child[i] = 1;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < 26; ++i) {
            if (trie[u].child[i]) {
                int v = trie[u].child[i];
                int f = trie[u].fail;
                while (f && !trie[f].child[i]) {
                    f = trie[f].fail;
                }
                trie[v].fail = trie[f].child[i];
                q.push(v);
            } else {
                trie[u].child[i] = trie[trie[u].fail].child[i];
            }
        }
    }
}

int getLCP(int u, int v) {
    int ans = 0;
    while (v != 1) {
        int uLen = trie[u].len;
        int vLen = trie[v].len;
        if (uLen <= vLen) {
            if (strncmp(trie[v].ch, trie[u].ch + vLen - uLen, uLen) == 0) {
                ans += uLen;
            }
            break;
        } else {
            if (strncmp(trie[u].ch, trie[v].ch + uLen - vLen, vLen) == 0) {
                ans += vLen;
            }
            u = trie[u].fail;
        }
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        memset(head, -1, sizeof(head));
        edgeIndex = 0;
        memset(degree, 0, sizeof(degree));
        trieSize = 1;
        memset(trie, 0, sizeof(trie));

        for (int i = 0; i < m; ++i) {
            int a, b, c, d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            addEdge(a, b, c);
            degree[b]++;
        }

        for (int i = 0; i < k; ++i) {
            char s[MAXK];
            int len;
            scanf("%d %s", &len, s);
            insert(s, len, i + 1);
        }

        buildFail();

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (int i = 2; i <= n; ++i) {
            pq.push({degree[i], i});
        }

        int dist[n + 1];
        memset(dist, 0x3f3f3f3f, sizeof(dist));
        dist[1] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].to;
                int cost = edges[e].cost;
                int lcp = getLCP(u, v);
                if (dist[v] > dist[u] + cost + lcp) {
                    dist[v] = dist[u] + cost + lcp;
                    pq.push({dist[v], v});
                }
            }
        }

        for (int i = 2; i <= n; ++i) {
            printf("%d\n", dist[i]);
        }
    }
    return 0;
}