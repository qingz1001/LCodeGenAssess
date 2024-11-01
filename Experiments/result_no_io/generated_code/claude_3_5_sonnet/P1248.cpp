#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int index;
    int A;
    int B;
} Product;

int compare(const void* a, const void* b) {
    Product* p1 = (Product*)a;
    Product* p2 = (Product*)b;
    return (p1->A < p2->A) - (p1->A > p2->A);
}

int main() {
    int n;
    Product products[MAX_N];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        products[i].index = i + 1;
        scanf("%d", &products[i].A);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].B);
    }
    
    qsort(products, n, sizeof(Product), compare);
    
    int total_time = 0;
    int time_A = 0;
    int time_B = 0;
    
    for (int i = 0; i < n; i++) {
        time_A += products[i].A;
        time_B = (time_B > time_A ? time_B : time_A) + products[i].B;
        total_time = (total_time > time_B ? total_time : time_B);
    }
    
    printf("%d\n", total_time);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].index);
    }
    
    return 0;
}