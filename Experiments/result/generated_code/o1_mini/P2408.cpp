#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100005
#define MAXSTATES (2 * MAXLEN)

typedef struct State {
    int next[26];
    int link;
    int len;
} State;

State st[MAXSTATES];
int size, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
    size = 1;
    last = 0;
}

void sa_extend(char c) {
    int curr = size++;
    st[curr].len = st[last].len + 1;
    memset(st[curr].next, -1, sizeof(st[curr].next));
    int p = last;
    while (p != -1 && st[p].next[c] == -1) {
        st[p].next[c] = curr;
        p = st[p].link;
    }
    if (p == -1) {
        st[curr].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[curr].link = q;
        } else {
            int clone = size++;
            st[clone].len = st[p].len + 1;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].link;
            }
            st[q].link = clone;
            st[curr].link = clone;
        }
    }
    last = curr;
}

int main(){
    int n;
    scanf("%d", &n);
    char s[MAXLEN];
    scanf("%s", s);
    sa_init();
    for(int i = 0; i < n; i++) {
        sa_extend(s[i] - 'a');
    }
    unsigned long long res = 0;
    for(int i = 1; i < size; i++) {
        res += (unsigned long long)(st[i].len - st[st[i].link].len);
    }
    printf("%llu\n", res);
    return 0;
}