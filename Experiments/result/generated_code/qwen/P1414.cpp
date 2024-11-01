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

void findMaxGCDs(int *abilities, int n) {
    for (int k = 1; k <= n; k++) {
        int maxGCD = 1;
        for (int i = 0; i < n - k + 1; i++) {
            int currentGCD = abilities[i];
            for (int j = 1; j < k; j++) {
                currentGCD = gcd(currentGCD, abilities[i + j]);
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
    int *abilities = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &abilities[i]);
    }
    findMaxGCDs(abilities, n);
    free(abilities);
    return 0;
}