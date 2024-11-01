#include <stdio.h>
#include <string.h>

#define EPSILON 1e-6

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    char guesses[n][m + 1];
    for (int i = 0; i < n; ++i) {
        scanf("%s", guesses[i]);
    }
    
    double probabilities[n];
    memset(probabilities, 0, sizeof(probabilities));
    
    for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j <= 300 - m; ++j) {
            if (strncmp(guesses[i], &guesses[0][j], m) == 0) {
                ++count;
            }
        }
        probabilities[i] = (double)count / (1 << (m * n));
    }
    
    for (int i = 0; i < n; ++i) {
        printf("%.6f\n", probabilities[i]);
    }
    
    return 0;
}