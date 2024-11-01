#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    if(y != x) return y - x;
    return 0;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int a[n];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp_desc);
    int total = 0;
    int current = 0;
    while(current < n){
        int cnt = 1;
        while(current + cnt < n && a[current + cnt] == a[current]) cnt++;
        if(total + cnt >= k){
            total += cnt;
            break;
        }
        total += cnt;
        current += cnt;
    }
    printf("%d\n", total);
    return 0;
}