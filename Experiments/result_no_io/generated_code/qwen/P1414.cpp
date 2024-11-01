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

void findMaxGCD(int *values, int n) {
    for (int k = 1; k <= n; k++) {
        int maxGCD = 0;
        for (int i = 0; i < n - k + 1; i++) {
            int currentGCD = values[i];
            for (int j = i + 1; j < i + k; j++) {
                currentGCD = gcd(currentGCD, values[j]);
            }
            if (currentGCD > maxGCD) {
                maxGCD = currentGCD;
            }
        }
        printf("%d\n", maxGCD);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int *values = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }
    findMaxGCD(values, n);
    free(values);
    return 0;
}