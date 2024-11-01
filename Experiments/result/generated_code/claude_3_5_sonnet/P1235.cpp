#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_N 301

double similarity[MAX_N][MAX_N];
int parent1[MAX_N], parent2[MAX_N];

void calculate_similarity(int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) {
                    similarity[i][j] = 1.0;
                } else if (parent1[k] == 0) {
                    continue;
                } else {
                    double new_sim = 0.5 * (similarity[i][parent1[k]] + similarity[i][parent2[k]]);
                    if (new_sim > similarity[i][k]) {
                        similarity[i][k] = similarity[k][i] = new_sim;
                    }
                }
            }
        }
    }
}

void print_percentage(double value) {
    if (fabs(value) < 1e-9) {
        printf("0%%\n");
    } else {
        int percentage = (int)(value * 1000000 + 0.5);
        if (percentage % 10000 == 0) {
            printf("%d%%\n", percentage / 10000);
        } else {
            printf("%.5g%%\n", value * 100);
        }
    }
}

int main() {
    int n, k, m;
    scanf("%d %d", &n, &k);

    memset(similarity, 0, sizeof(similarity));
    memset(parent1, 0, sizeof(parent1));
    memset(parent2, 0, sizeof(parent2));

    for (int i = 0; i < k; i++) {
        int child, p1, p2;
        scanf("%d %d %d", &child, &p1, &p2);
        parent1[child] = p1;
        parent2[child] = p2;
    }

    calculate_similarity(n);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        print_percentage(similarity[x][y]);
    }

    return 0;
}