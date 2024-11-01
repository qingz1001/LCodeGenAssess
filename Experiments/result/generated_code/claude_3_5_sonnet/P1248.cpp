#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int index;
    int a;
    int b;
} Product;

int compare(const void *a, const void *b) {
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;
    return (p1->a < p2->a) ? -1 : 1;
}

int main() {
    int n;
    Product products[MAX_N];
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        products[i].index = i + 1;
        scanf("%d", &products[i].a);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].b);
    }
    
    qsort(products, n, sizeof(Product), compare);
    
    int total_time = 0;
    int time_a = 0;
    int time_b = 0;
    
    for (int i = 0; i < n; i++) {
        time_a += products[i].a;
        time_b = (time_b > time_a ? time_b : time_a) + products[i].b;
        total_time = (total_time > time_b ? total_time : time_b);
    }
    
    printf("%d\n", total_time);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].index);
    }
    
    return 0;
}