#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 201
#define EPS 1e-8

int main(){
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);
    
    // Initialize conductance matrix
    double G[MAXN][MAXN];
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=n;j++) {
            G[i][j] = 0.0;
        }
    }
    
    // Voltage constraints
    int hasV[MAXN];
    double Vcon[MAXN];
    for(int i=1;i<=n;i++) hasV[i] = 0;
    for(int i=0;i<k;i++){
        int node;
        double u;
        scanf("%d %lf", &node, &u);
        hasV[node] = 1;
        Vcon[node] = u;
    }
    
    // Read resistors and build conductance matrix
    for(int i=0;i<m;i++){
        int v, w;
        double r;
        scanf("%d %d %lf", &v, &w, &r);
        double g = 1.0 / r;
        if(w !=0 && v !=0){
            G[v][v] += g;
            G[w][w] += g;
            G[v][w] -= g;
            G[w][v] -= g;
        }
        else{
            if(v ==0){
                G[w][w] += g;
            }
            else{
                G[v][v] += g;
            }
        }
    }
    
    // Set up augmented matrix
    double A[MAXN][MAXN+1];
    for(int i=1;i<=n;i++){
        if(hasV[i]){
            for(int j=1;j<=n;j++) {
                A[i][j] = 0.0;
            }
            A[i][i] = 1.0;
            A[i][n+1] = Vcon[i];
        }
        else{
            for(int j=1;j<=n;j++) {
                A[i][j] = G[i][j];
            }
            A[i][n+1] = 0.0;
        }
    }
    
    // Gaussian elimination
    for(int i=1;i<=n;i++){
        // Partial pivot
        int pivot = i;
        for(int j=i+1;j<=n;j++) {
            if(fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        }
        if(fabs(A[pivot][i]) < EPS){
            // Singular matrix
            // Assign zero
            A[i][i] = 1.0;
            A[i][n+1] = 0.0;
            continue;
        }
        // Swap rows if needed
        if(pivot != i){
            for(int j=i;j<=n+1;j++) {
                double temp = A[i][j];
                A[i][j] = A[pivot][j];
                A[pivot][j] = temp;
            }
        }
        // Eliminate below
        for(int j=i+1;j<=n;j++) {
            double factor = A[j][i] / A[i][i];
            for(int k=i;k<=n+1;k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }
    
    // Back substitution
    double V[MAXN];
    for(int i=1;i<=n;i++) V[i] = 0.0;
    for(int i=n;i>=1;i--){
        if(hasV[i]){
            V[i] = A[i][n+1];
            continue;
        }
        double sum = A[i][n+1];
        for(int j=i+1;j<=n;j++) {
            sum -= A[i][j] * V[j];
        }
        if(fabs(A[i][i]) < EPS){
            V[i] = 0.0;
        }
        else{
            V[i] = sum / A[i][i];
        }
    }
    
    // Answer queries
    for(int i=0;i<q;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        double diff = V[a] - V[b];
        printf("%.2lf\n", diff);
    }
    return 0;
}