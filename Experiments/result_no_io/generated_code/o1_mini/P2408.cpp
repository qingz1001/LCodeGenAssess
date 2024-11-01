#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 200005
#define ALPHABET 26

typedef struct State {
    int next[ALPHABET];
    int link;
    int len;
} State;

State st[MAXN];
int sz, last;

void sa_init(){
    st[0].len = 0;
    st[0].link = -1;
    for(int i=0;i<ALPHABET;i++) st[0].next[i] = -1;
    sz = 1;
    last = 0;
}

void sa_extend(char c){
    int curr = sz++;
    st[curr].len = st[last].len +1;
    for(int i=0;i<ALPHABET;i++) st[curr].next[i] = -1;
    int p = last;
    int c_idx = c - 'a';
    while(p != -1 && st[p].next[c_idx] == -1){
        st[p].next[c_idx] = curr;
        p = st[p].link;
    }
    if(p == -1){
        st[curr].link = 0;
    }
    else{
        int q = st[p].next[c_idx];
        if(st[p].len +1 == st[q].len){
            st[curr].link = q;
        }
        else{
            int clone = sz++;
            st[clone].len = st[p].len +1;
            for(int i=0;i<ALPHABET;i++) st[clone].next[i] = st[q].next[i];
            st[clone].link = st[q].link;
            while(p != -1 && st[p].next[c_idx] == q){
                st[p].next[c_idx] = clone;
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
    char *s = (char*)malloc((n+1)*sizeof(char));
    scanf("%s", s);
    sa_init();
    for(int i=0;i<n;i++) sa_extend(s[i]);
    free(s);
    uint64_t res=0;
    for(int i=1;i<sz;i++) {
        res += (uint64_t)(st[i].len - st[st[i].link].len);
    }
    printf("%llu\n", res);
    return 0;
}