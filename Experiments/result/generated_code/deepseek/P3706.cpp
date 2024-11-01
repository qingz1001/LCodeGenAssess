#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 300
#define MAXM 300

int n, m;
char patterns[MAXN][MAXM + 1];
double prob[MAXN];

void calculate_probabilities() {
    double total_prob = 0.0;
    for (int i = 0; i < n; i++) {
        prob[i] = 1.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                int match_count = 0;
                for (int k = 0; k < m; k++) {
                    if (patterns[i][k] == patterns[j][k]) {
                        match_count++;
                    }
                }
                prob[i] *= pow(0.5, match_count);
            }
        }
        total_prob += prob[i];
    }

    for (int i = 0; i < n; i++) {
        prob[i] /= total_prob;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", patterns[i]);
    }

    calculate_probabilities();

    for (int i = 0; i < n; i++) {
        printf("%.10f\n", prob[i]);
    }

    return 0;
}