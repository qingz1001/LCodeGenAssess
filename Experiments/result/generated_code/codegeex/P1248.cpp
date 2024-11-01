#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
    int index;
} Product;

int compare(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    if (productA->a + productB->b == productB->a + productA->b) {
        return productA->a - productB->a;
    } else {
        return (productA->a + productB->b) - (productB->a + productA->b);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Product products[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].a);
        products[i].index = i + 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].b);
    }

    qsort(products, n, sizeof(Product), compare);

    int total_time = 0;
    int a_time = 0, b_time = 0;
    for (int i = 0; i < n; i++) {
        a_time += products[i].a;
        if (a_time > b_time) {
            b_time = a_time;
        }
        b_time += products[i].b;
        total_time = b_time;
    }

    printf("%d\n", total_time);
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].index);
    }
    printf("\n");

    return 0;
}