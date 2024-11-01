#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int rates[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &rates[i]);
    }

    double dollars = 100.0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            dollars = dollars / rates[i] * 100.0;
        } else {
            dollars = dollars * rates[i] / 100.0;
        }
    }

    printf("%.2f\n", dollars);
    return 0;
}