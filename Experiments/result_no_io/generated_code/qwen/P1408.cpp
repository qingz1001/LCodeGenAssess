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
    
    int *sequence = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &sequence[i]);
    }

    long long min_cost = 0;

    for (int i = 0; i < n - 1; i++) {
        int current_gcd = gcd(sequence[i], sequence[i + 1]);
        min_cost += current_gcd;
        sequence[i + 1] /= current_gcd;
    }

    printf("%lld\n", min_cost);

    free(sequence);
    return 0;
}