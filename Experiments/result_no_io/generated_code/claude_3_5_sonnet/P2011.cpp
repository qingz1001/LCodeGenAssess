#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 201
#define MAX_M 200001
#define EPSILON 1e-6

double A[MAX_N][MAX_N], b[MAX_N], x[MAX_N];
int n, m, k, q;

void add_edge(int u, int v, double r) {
    A[u][u] += 1.0 / r;
    A[v][v] += 1.0 / r;
    A[u][v] -= 1.0 / r;
    A[v][u] -= 1.0 / r;
}

void gaussian_elimination() {
    for (int i = 1; i <= n; i++) {
        int max_row = i;
        for (int j = i + 1; j <= n; j++)
            if (fabs(A[j][i]) > fabs(A[max_row][i]))
                max_row = j;
        
        if (max_row != i) {
            for (int j = 1; j <= n; j++) {
                double temp = A[i][j];
                A[i][j] = A[max_row][j];
                A[max_row][j] = temp;
            }
            double temp = b[i];
            b[i] = b[max_row];
            b[max_row] = temp;
        }

        for (int j = i + 1; j <= n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k <= n; k++)
                A[j][k] -= factor * A[i][k];
            b[j] -= factor * b[i];
        }
    }

    for (int i = n; i >= 1; i--) {
        x[i] = b[i];
        for (int j = i + 1; j <= n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
}

int main() {
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int i = 0; i < k; i++) {
        int node;
        double voltage;
        scanf("%d %lf", &node, &voltage);
        A[node][node] = 1.0;
        b[node] = voltage;
    }

    for (int i = 0; i < m; i++) {
        int u, v, r;
        scanf("%d %d %d", &u, &v, &r);
        add_edge(u, v, r);
    }

    gaussian_elimination();

    for (int i = 0; i < q; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%.2f\n", x[a] - x[b]);
    }

    return 0;
}