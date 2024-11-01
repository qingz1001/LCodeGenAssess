#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

typedef struct Node {
    int next[26];
    int fail;
    int count;
} Node;

Node trie[MAXN];
int pos[MAXN], idx = 1;
char input[MAXN];
int m, queries[MAXN][2], answers[MAXN];

void buildTrie(char *s) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == 'P') {
            pos[idx++] = p;
        } else if (s[i] == 'B') {
            p = trie[p].fail;
        } else {
            int c = s[i] - 'a';
            if (!trie[p].next[c]) {
                trie[p].next[c] = idx++;
            }
            p = trie[p].next[c];
        }
    }
}

void buildFail() {
    int queue[MAXN], front = 0, rear = 0;
    queue[rear++] = 0;
    while (front < rear) {
        int p = queue[front++];
        for (int i = 0; i < 26; i++) {
            int u = trie[p].next[i];
            if (!u) continue;
            if (p == 0) {
                trie[u].fail = 0;
            } else {
                int v = trie[p].fail;
                while (v && !trie[v].next[i]) v = trie[v].fail;
                trie[u].fail = trie[v].next[i];
            }
            queue[rear++] = u;
        }
    }
}

void query(int x, int y) {
    int p = pos[y];
    while (p) {
        if (trie[p].count) {
            answers[trie[p].count]++;
        }
        p = trie[p].fail;
    }
}

int main() {
    scanf("%s", input);
    buildTrie(input);
    buildFail();
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }
    for (int i = 0; i < m; i++) {
        query(queries[i][0], queries[i][1]);
    }
    for (int i = 0; i < m; i++) {
        printf("%d\n", answers[queries[i][0]]);
    }
    return 0;
}