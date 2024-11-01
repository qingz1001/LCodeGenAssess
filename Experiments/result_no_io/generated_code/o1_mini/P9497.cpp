#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int aa = *(int*)a;
    int bb = *(int*)b;
    if(aa < bb) return -1;
    if(aa > bb) return 1;
    return 0;
}

int lower_bound_search(int *a, int size, int v){
    int l = 0, r = size;
    while(l < r){
        int m = l + (r - l) / 2;
        if(a[m] >= v)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    int total = n * n;
    int *a = (int*)malloc(sizeof(int) * total);
    for(int i=0; i<total; i++) {
        scanf("%d", &a[i]);
    }
    qsort(a, total, sizeof(int), cmp);
    for(int i=0; i<q; i++){
        int v;
        scanf("%d", &v);
        int idx = lower_bound_search(a, total, v);
        int cnt = total - idx;
        if(cnt > n) cnt = n;
        printf("%d\n", cnt);
    }
    free(a);
    return 0;
}