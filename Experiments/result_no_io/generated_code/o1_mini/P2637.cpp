#include <stdio.h>
#include <stdlib.h>

int cmp_desc(const void *a, const void *b){
    int x = *((int*)b);
    int y = *((int*)a);
    if(x > y) return 1;
    else if(x < y) return -1;
    else return 0;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int p[m];
    for(int i=0;i<m;i++) scanf("%d", &p[i]);
    qsort(p, m, sizeof(int), cmp_desc);
    long long max_income = 0;
    int best_price = 0;
    for(int i=0;i<m;i++){
        int price = p[i];
        int count = m - i;
        if(count > n) count = n;
        long long income = (long long)price * count;
        if(income > max_income || (income == max_income && price < best_price)){
            max_income = income;
            best_price = price;
        }
    }
    printf("%d %lld\n", best_price, max_income);
    return 0;
}