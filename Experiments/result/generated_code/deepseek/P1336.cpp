#include <stdio.h>
#include <limits.h>
#include <math.h>

#define MAX_N 200
#define MAX_M 20

int n, m;
int A[MAX_M], B[MAX_M];

long long calculateTime(int x, int a, int b) {
    return (long long)a * pow(x, b);
}

long long minTime(int remainingPapers, int currentTopic) {
    if (remainingPapers == 0) return 0;
    if (currentTopic == m) return INT_MAX;

    long long minCost = INT_MAX;
    for (int x = 0; x <= remainingPapers; x++) {
        long long cost = calculateTime(x, A[currentTopic], B[currentTopic]) + minTime(remainingPapers - x, currentTopic + 1);
        if (cost < minCost) {
            minCost = cost;
        }
    }
    return minCost;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &A[i], &B[i]);
    }

    long long result = minTime(n, 0);
    printf("%lld\n", result);

    return 0;
}