#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100
#define MAXM 100

typedef struct {
    int a, b, c;
} Distillery;

typedef struct {
    int capacity;
} Storage;

int n, m;
Distillery distilleries[MAXN];
Storage storages[MAXM];
int connections[MAXN][MAXM];

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void simplifyFraction(int *numerator, int *denominator) {
    int commonDivisor = gcd(*numerator, *denominator);
    *numerator /= commonDivisor;
    *denominator /= commonDivisor;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &distilleries[i].a, &distilleries[i].b, &distilleries[i].c);
    }

    for (int j = 0; j < m; j++) {
        scanf("%d", &storages[j].capacity);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &connections[i][j]);
        }
    }

    int maxStorage = 0;
    int minManaNumerator = 0, minManaDenominator = 1;

    // Placeholder logic for calculating max storage and min mana
    // This is a simplified version and should be replaced with a proper algorithm
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (connections[i][j]) {
                int storageCapacity = storages[j].capacity;
                int distilleryCapacity = distilleries[i].c;
                int maxCapacity = storageCapacity < distilleryCapacity ? storageCapacity : distilleryCapacity;
                maxStorage += maxCapacity;

                int a = distilleries[i].a;
                int b = distilleries[i].b;
                int manaNumerator = a * maxCapacity * maxCapacity + b * maxCapacity;
                int commonDenominator = 1;

                simplifyFraction(&manaNumerator, &commonDenominator);

                // Add the fractions
                int lcmDenominator = minManaDenominator * commonDenominator / gcd(minManaDenominator, commonDenominator);
                int newNumerator = minManaNumerator * (lcmDenominator / minManaDenominator) + manaNumerator * (lcmDenominator / commonDenominator);
                minManaNumerator = newNumerator;
                minManaDenominator = lcmDenominator;

                simplifyFraction(&minManaNumerator, &minManaDenominator);
            }
        }
    }

    printf("%d\n", maxStorage);
    if (minManaNumerator == 0) {
        printf("0/1\n");
    } else {
        printf("%d/%d\n", minManaNumerator, minManaDenominator);
    }

    return 0;
}