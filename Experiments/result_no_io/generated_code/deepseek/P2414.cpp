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
int trie_size = 1;
int pos[MAXN];
int end[MAXN];
int q[MAXN];
int q_front = 0, q_rear = 0;

void insert(char *s, int idx) {
    int p = 0;
    for (int i = 0; s[i]; i++) {
        int c = s[i] - 'a';
        if (!trie[p].next[c]) {
            trie[p].next[c] = trie_size++;
        }
        p = trie[p].next[c];
    }
    end[idx] = p;
}

void build_fail() {
    q_front = q_rear = 0;
    q[q_rear++] = 0;
    while (q_front < q_rear) {
        int p = q[q_front++];
        for (int i = 0; i < 26; i++) {
            int next = trie[p].next[i];
            if (next) {
                if (p == 0) trie[next].fail = 0;
                else {
                    int f = trie[p].fail;
                    while (f && !trie[f].next[i]) f = trie[f].fail;
                    trie[next].fail = trie[f].next[i];
                }
                q[q_rear++] = next;
            }
        }
    }
}

void query(char *s, int x, int y) {
    int p = end[y];
    while (p) {
        pos[p] = x;
        p = trie[p].fail;
    }
}

int main() {
    char input[MAXN];
    int m, x, y;
    scanf("%s", input);
    scanf("%d", &m);

    int idx = 0;
    int p = 0;
    for (int i = 0; input[i]; i++) {
        if (input[i] == 'P') {
            pos[p] = ++idx;
            end[idx] = p;
        } else if (input[i] == 'B') {
            p = trie[p].fail;
        } else {
            int c = input[i] - 'a';
            if (!trie[p].next[c]) {
                trie[p].next[c] = trie_size++;
            }
            p = trie[p].next[c];
        }
    }

    build_fail();

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        query(input, x, y);
        printf("%d\n", trie[end[x]].count);
    }

    return 0;
}