#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int index;
    int A;
    int B;
    int diff;
} Product;

int compare(const void *a, const void *b) {
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;
    if (p1->diff != p2->diff) {
        return p2->diff - p1->diff;
    } else {
        return p1->A - p2->A;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Product products[n];

    for (int i = 0; i < n; i++) {
        products[i].index = i + 1;
        scanf("%d", &products[i].A);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].B);
        products[i].diff = products[i].A - products[i].B;
    }

    qsort(products, n, sizeof(Product), compare);

    int total_time = 0;
    int A_time = 0;
    for (int i = 0; i < n; i++) {
        A_time += products[i].A;
        total_time = A_time + products[i].B;
    }

    printf("%d\n", total_time);
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].index);
    }
    printf("\n");

    return 0;
}