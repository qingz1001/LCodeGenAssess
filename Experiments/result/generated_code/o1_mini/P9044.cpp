#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (y != x)
        return y - x;
    else
        return 0;
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int a[2000];
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    qsort(a, n, sizeof(int), cmp_desc);
    int count = 0;
    int i = 0;
    while(i < n && count < k){
        int current = a[i];
        int j = i;
        while(j < n && a[j] == current) j++;
        count += (j - i);
        i = j;
    }
    printf("%d\n", count);
    return 0;
}