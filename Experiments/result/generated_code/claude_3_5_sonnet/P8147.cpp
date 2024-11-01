#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005
#define MAX_L 500005

typedef long long ll;

char s[MAX_N][55];
int v[MAX_N];
char S[MAX_L];
int n, m;

ll cnt[MAX_N], w[MAX_N];

int cmp(const void *a, const void *b) {
    return *(ll*)b - *(ll*)a;
}

void kmp_preprocess(char *p, int *next, int len) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < len) {
        if (j == -1 || p[i] == p[j]) {
            i++; j++;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int kmp_count(char *s, char *p) {
    int slen = strlen(s), plen = strlen(p);
    int next[55], i = 0, j = 0, count = 0;
    kmp_preprocess(p, next, plen);
    while (i < slen) {
        if (j == -1 || s[i] == p[j]) {
            i++; j++;
        } else {
            j = next[j];
        }
        if (j == plen) {
            count++;
            j = next[j];
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s %d", s[i], &v[i]);
    }
    
    while (m--) {
        int k;
        scanf("%s %d", S, &k);
        
        for (int i = 0; i < n; i++) {
            cnt[i] = kmp_count(S, s[i]);
            w[i] = cnt[i] * (ll)v[i];
        }
        
        qsort(w, n, sizeof(ll), cmp);
        
        printf("%lld\n", w[k-1]);
    }
    
    return 0;
}