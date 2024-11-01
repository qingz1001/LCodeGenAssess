#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int timeA;
    int timeB;
} Product;

int compare(const void *a, const void *b) {
    Product *productA = (Product *)a;
    Product *productB = (Product *)b;
    if (productA->timeA + productB->timeB < productB->timeA + productA->timeB) {
        return -1;
    } else if (productA->timeA + productB->timeB > productB->timeA + productA->timeB) {
        return 1;
    } else {
        return 0;
    }
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

    int totalTime = 0;
    int maxATime = 0;
    for (int i = 0; i < n; i++) {
        maxATime = (maxATime + products[i].timeA > totalTime) ? maxATime + products[i].timeA : totalTime;
        totalTime += products[i].timeA + products[i].timeB;
    }

    printf("%d\n", totalTime);
    for (int i = 0; i < n; i++) {
        printf("%d ", products[i].id);
    }
    printf("\n");

    return 0;
}