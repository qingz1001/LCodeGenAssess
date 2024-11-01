#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1001
#define MAX_M 100001
#define EPSILON 1e-6

double A[MAX_N][MAX_N];
double b[MAX_N];
double x[MAX_N];
int N, M;

void gaussian_elimination() {
    for (int i = 0; i < N; i++) {
        int max_row = i;
        for (int j = i + 1; j < N; j++) {
            if (abs(A[j][i]) > abs(A[max_row][i])) {
                max_row = j;
            }
        }
        
        for (int k = i; k < N; k++) {
            double temp = A[i][k];
            A[i][k] = A[max_row][k];
            A[max_row][k] = temp;
        }
        double temp = b[i];
        b[i] = b[max_row];
        b[max_row] = temp;
        
        for (int j = i + 1; j < N; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < N; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }
    
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

int main() {
    scanf("%d %d", &N, &M);
    
    memset(A, 0, sizeof(A));
    memset(b, 0, sizeof(b));
    
    for (int i = 0; i < M; i++) {
        int u, v;
        double sum;
        scanf("%d %d %lf", &u, &v, &sum);
        u--; v--;
        A[u][u] += 1;
        A[v][v] += 1;
        A[u][v] -= 1;
        A[v][u] -= 1;
        b[u] += sum;
        b[v] += sum;
    }
    
    for (int i = 0; i < N; i++) {
        A[N-1][i] = 1;
    }
    b[N-1] = 0;
    
    gaussian_elimination();
    
    int possible = 1;
    for (int i = 0; i < N; i++) {
        if (x[i] < -EPSILON) {
            possible = 0;
            break;
        }
    }
    
    if (possible) {
        for (int i = 0; i < N; i++) {
            printf("%.2f\n", x[i]);
        }
    } else {
        printf("IMPOSSIBLE\n");
    }
    
    return 0;
}