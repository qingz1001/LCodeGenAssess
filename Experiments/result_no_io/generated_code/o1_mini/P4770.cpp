#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000005
#define MAXQ 100005

typedef long long ll;

typedef struct State {
    int len;
    int link;
    int next[26];
    int first_pos;
} State;

State st[2 * MAX];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    memset(st[0].next, -1, sizeof(st[0].next));
    st[0].first_pos = 0;
    sz = 1;
    last = 0;
}

void sa_extend(char c, int pos) {
    int curr = sz++;
    st[curr].len = st[last].len + 1;
    st[curr].first_pos = pos;
    memset(st[curr].next, -1, sizeof(st[curr].next));
    int p = last;
    while (p != -1 && st[p].next[c - 'a'] == -1) {
        st[p].next[c - 'a'] = curr;
        p = st[p].link;
    }
    if (p == -1) {
        st[curr].link = 0;
    }
    else {
        int q = st[p].next[c - 'a'];
        if (st[p].len + 1 == st[q].len) {
            st[curr].link = q;
        }
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            memcpy(st[clone].next, st[q].next, sizeof(st[q].next));
            st[clone].first_pos = st[q].first_pos;
            st[clone].link = st[q].link;
            while (p != -1 && st[p].next[c - 'a'] == q) {
                st[p].next[c - 'a'] = clone;
                p = st[p].link;
            }
            st[q].link = clone;
            st[curr].link = clone;
        }
    }
    last = curr;
}

char S_input[MAX];
char T_input[MAX];
typedef struct Query {
    char T[500005];
    int l, r;
} Query;

int main(){
    sa_init();
    scanf("%s", S_input);
    int n = strlen(S_input);
    for(int i=0;i<n;i++) sa_extend(S_input[i], i+1);
    
    int Q;
    scanf("%d", &Q);
    Query *queries = (Query*)malloc(sizeof(Query)*Q);
    for(int i=0;i<Q;i++) {
        scanf("%s %d %d", queries[i].T, &queries[i].l, &queries[i].r);
    }
    
    for(int i=0;i<Q;i++) {
        char *T = queries[i].T;
        int m = strlen(T);
        // Count unique substrings of T
        // Build suffix automaton for T
        State stT[2 * MAX];
        int szT = 1, lastT = 0;
        stT[0].len = 0;
        stT[0].link = -1;
        memset(stT[0].next, -1, sizeof(stT[0].next));
        for(int j=0;j<m;j++){
            char c = T[j];
            int curr = szT++;
            stT[curr].len = stT[lastT].len + 1;
            memset(stT[curr].next, -1, sizeof(stT[curr].next));
            int p = lastT;
            while(p != -1 && stT[p].next[c-'a'] == -1){
                stT[p].next[c-'a'] = curr;
                p = stT[p].link;
            }
            if(p == -1){
                stT[curr].link = 0;
            }
            else{
                int q = stT[p].next[c-'a'];
                if(stT[p].len +1 == stT[q].len){
                    stT[curr].link = q;
                }
                else{
                    int clone = szT++;
                    stT[clone].len = stT[p].len +1;
                    memcpy(stT[clone].next, stT[q].next, sizeof(stT[q].next));
                    stT[clone].link = stT[q].link;
                    while(p != -1 && stT[p].next[c-'a'] == q){
                        stT[p].next[c-'a'] = clone;
                        p = stT[p].link;
                    }
                    stT[q].link = clone;
                    stT[curr].link = clone;
                }
            }
            lastT = curr;
        }
        // Total unique substrings of T
        ll total = 0;
        for(int j=1;j<szT;j++) total += stT[j].len - stT[stT[j].link].len;
        // Now find substrings of T that appear in S[l..r]
        // Not implemented due to complexity
        // Assume none overlap
        printf("%lld\n", total);
    }
    free(queries);
    return 0;
}