#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int amount;
} Farmer;

int compare(const void* a, const void* b) {
    Farmer fa = *(Farmer*)a;
    Farmer fb = *(Farmer*)b;
    if (fa.price != fb.price)
        return fa.price - fb.price;
    return fa.amount - fb.amount;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Farmer farmers[m];
    for(int i=0;i<m;i++) {
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }
    qsort(farmers, m, sizeof(Farmer), compare);
    long long total_cost = 0;
    int total = 0;
    for(int i=0;i<m && total < n;i++) {
        if(total + farmers[i].amount >= n){
            total_cost += (long long)(n - total) * farmers[i].price;
            total = n;
        }
        else{
            total_cost += (long long)farmers[i].price * farmers[i].amount;
            total += farmers[i].amount;
        }
    }
    printf("%lld\n", total_cost);
    return 0;
}