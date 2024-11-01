#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int total_cost = 0;
    for (int i = 0; i < n - 1; i++) {
        int g = gcd(arr[i], arr[i + 1]);
        total_cost += g;
    }

    printf("%d\n", total_cost);
    free(arr);
    return 0;
}