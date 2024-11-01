#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int price;
    int amount;
} Farmer;

int cmp(const void *a, const void *b){
    Farmer fa = *(Farmer*)a;
    Farmer fb = *(Farmer*)b;
    if(fa.price != fb.price){
        return fa.price - fb.price;
    }
    return fa.amount - fb.amount;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Farmer farmers[m];
    for(int i=0;i<m;i++){
        scanf("%d %d", &farmers[i].price, &farmers[i].amount);
    }
    qsort(farmers, m, sizeof(Farmer), cmp);
    long total_cost=0;
    int needed = n;
    for(int i=0;i<m && needed >0;i++){
        if(farmers[i].amount >= needed){
            total_cost += (long)needed * farmers[i].price;
            needed =0;
        }
        else{
            total_cost += (long)farmers[i].amount * farmers[i].price;
            needed -= farmers[i].amount;
        }
    }
    printf("%ld\n", total_cost);
    return 0;
}