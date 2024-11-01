#include <stdio.h>
#include <stdlib.h>

// Comparator for ascending order
int cmp(const void *a, const void *b){
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    long long *w = (long long*)malloc(n * sizeof(long long));
    for(int i=0;i<n;i++) scanf("%lld", &w[i]);
    long long *m_j = (long long*)malloc(m * sizeof(long long));
    for(int i=0;i<m;i++) scanf("%lld", &m_j[i]);
    
    qsort(w, n, sizeof(long long), cmp);
    qsort(m_j, m, sizeof(long long), cmp);
    
    long long count = 0;
    int ptr = 0;
    for(int i=0;i<n && ptr<m;i++){
        long long remaining = w[i];
        while(ptr < m && m_j[ptr] <= remaining){
            remaining -= m_j[ptr];
            count++;
            ptr++;
        }
    }
    printf("%lld", count);
    free(w);
    free(m_j);
    return 0;
}