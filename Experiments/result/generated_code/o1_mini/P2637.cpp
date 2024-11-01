#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int *p = (int*)malloc(m * sizeof(int));
    for(int i=0;i<m;i++) scanf("%d", &p[i]);
    qsort(p, m, sizeof(int), cmp_desc);
    long long max_revenue = 0;
    int best_price = 0;
    for(int i=0;i<m;i++){
        if(i >0 && p[i] == p[i-1]) continue;
        int sales = (n < (i+1)) ? n : (i+1);
        long long revenue = (long long)p[i] * sales;
        if(revenue > max_revenue || (revenue == max_revenue && p[i] < best_price)){
            max_revenue = revenue;
            best_price = p[i];
        }
    }
    printf("%d %lld\n", best_price, max_revenue);
    free(p);
    return 0;
}