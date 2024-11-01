#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int m;
    int v;
    double ratio;
} Item;

int compare(const void *a, const void *b) {
    double r1 = ((Item*)b)->ratio;
    double r2 = ((Item*)a)->ratio;
    if (r1 < r2) return -1;
    else if (r1 > r2) return 1;
    else return 0;
}

int main(){
    int N, T;
    scanf("%d %d", &N, &T);
    Item items[N];
    for(int i=0;i<N;i++){
        scanf("%d %d", &items[i].m, &items[i].v);
        items[i].ratio = (double)items[i].v / items[i].m;
    }
    qsort(items, N, sizeof(Item), compare);
    double total = 0.0;
    int capacity = T;
    for(int i=0;i<N && capacity >0;i++){
        if(items[i].m <= capacity){
            total += items[i].v;
            capacity -= items[i].m;
        }
        else{
            total += items[i].ratio * capacity;
            capacity =0;
        }
    }
    printf("%.2lf\n", total);
    return 0;
}