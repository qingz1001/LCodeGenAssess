#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int aa = *(const int *)a;
    int bb = *(const int *)b;
    if (aa < bb) return -1;
    else if (aa > bb) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n, sizeof(int), cmp);

    for(int i = 0; i < n; ){
        int current = a[i];
        int count = 0;
        while(i < n && a[i] == current){
            count++;
            i++;
        }
        printf("%d %d\n", current, count);
    }

    free(a);
    return 0;
}