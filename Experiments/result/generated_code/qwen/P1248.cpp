#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int timeA;
    int timeB;
} Product;

int compare(const void *a, const void *b) {
    return ((Product *)a)->timeA - ((Product *)b)->timeA;
}

int main() {
    int n;
    scanf("%d", &n);
    Product products[n];
    for (int i = 0; i < n; i++) {
        products[i].id = i + 1;
        scanf("%d", &products[i].timeA);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].timeB);
    }

    qsort(products, n, sizeof(Product), compare);

    int total_time = 0;
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < products[i].timeA) {
            current_time = products[i].timeA;
        }
        current_time += products[i].timeB;
        total_time = current_time;
    }

    printf("%d\n", total_time);
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].id);
    }
    printf("\n");

    return 0;
}