#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int A;
    int B;
    int index;
} Product;

int compare(const void *a, const void *b) {
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;
    int diff1 = p1->A - p1->B;
    int diff2 = p2->A - p2->B;
    if (diff1 != diff2) {
        return diff1 - diff2;
    } else {
        return p1->A - p2->A;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Product products[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].A);
        products[i].index = i + 1;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &products[i].B);
    }

    qsort(products, n, sizeof(Product), compare);

    int timeA = 0, timeB = 0;
    for (int i = 0; i < n; i++) {
        timeA += products[i].A;
        timeB = timeA > timeB ? timeA : timeB;
        timeB += products[i].B;
    }

    printf("%d\n", timeB);
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].index);
    }
    printf("\n");

    return 0;
}