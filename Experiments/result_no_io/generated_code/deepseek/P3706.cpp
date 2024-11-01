#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 300
#define MAXM 300

int n, m;
char sequences[MAXN][MAXM + 1];
double probability[MAXN];

void calculateProbabilities() {
    // Initialize probabilities to 0
    for (int i = 0; i < n; i++) {
        probability[i] = 0.0;
    }

    // Calculate the probability for each sequence
    for (int i = 0; i < n; i++) {
        // For simplicity, we assume each sequence has an equal probability of appearing
        // This is a placeholder calculation and should be replaced with a more accurate method
        probability[i] = 1.0 / n;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", sequences[i]);
    }

    calculateProbabilities();

    for (int i = 0; i < n; i++) {
        printf("%.6f\n", probability[i]);
    }

    return 0;
}