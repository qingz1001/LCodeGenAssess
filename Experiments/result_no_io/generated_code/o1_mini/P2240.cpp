#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double m;
    double v;
    double ratio;
} Item;

// Comparator for sorting in descending order of value per unit weight
int cmp(const void *a, const void *b) {
    double r1 = ((Item*)b)->ratio;
    double r2 = ((Item*)a)->ratio;
    if (r1 > r2) return 1;
    else if (r1 < r2) return -1;
    else return 0;
}

int main(){
    int N;
    double T;
    scanf("%d %lf", &N, &T);
    Item items[N];
    for(int i=0;i<N;i++){
        scanf("%lf %lf", &items[i].m, &items[i].v);
        items[i].ratio = items[i].v / items[i].m;
    }
    qsort(items, N, sizeof(Item), cmp);
    double total = 0.0;
    double capacity = T;
    for(int i=0;i<N;i++){
        if(capacity <= 0) break;
        if(items[i].m <= capacity){
            total += items[i].v;
            capacity -= items[i].m;
        }
        else{
            total += items[i].ratio * capacity;
            capacity = 0;
        }
    }
    printf("%.2lf\n", total);
    return 0;
}