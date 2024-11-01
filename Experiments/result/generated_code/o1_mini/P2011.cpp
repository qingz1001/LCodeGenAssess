#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 201
#define MAXK 201
#define EPS 1e-9

int main(){
    int n, m, k, q;
    scanf("%d %d %d %d", &n, &m, &k, &q);
    
    // Voltage for nodes, -1 means unknown
    double voltage[MAXN];
    for(int i=0;i<=n;i++) voltage[i] = -1.0;
    // Read voltage sources
    for(int i=0;i<k;i++){
        int x;
        double u;
        scanf("%d %lf", &x, &u);
        voltage[x] = u;
    }
    // Conductance matrix
    double G[MAXN][MAXN];
    memset(G, 0, sizeof(G));
    // For node 0
    for(int i=0;i<m;i++){
        int v, w;
        double r;
        scanf("%d %d %lf", &v, &w, &r);
        double g = 1.0 / r;
        if(w != 0 && voltage[w]==-1){
            G[v][w] -= g;
            G[w][v] -= g;
        }
        if(v != 0 && voltage[v]==-1){
            G[w][v] -= g;
            G[v][v] += g;
        }
        if(w ==0 || voltage[w]!=-1){
            G[v][v] += g;
        }
        if(v ==0 || voltage[v]!=-1){
            G[w][w] += g;
        }
    }
    
    // Identify unknown nodes
    int idx[MAXN];
    int cnt=0;
    for(int i=1;i<=n;i++) {
        if(voltage[i]==-1){
            idx[i] = cnt;
            cnt++;
        }
    }
    int unknown = cnt;
    // Build augmented matrix
    double A[MAXN][MAXN+1];
    memset(A, 0, sizeof(A));
    for(int i=1;i<=n;i++){
        if(voltage[i]==-1){
            int row = idx[i];
            for(int j=1;j<=n;j++){
                if(G[i][j] !=0 && voltage[j]==-1){
                    A[row][idx[j]] = G[i][j];
                }
                else if(G[i][j] !=0 && voltage[j]!=-1){
                    A[row][unknown] += G[i][j] * voltage[j];
                }
            }
            A[row][unknown] = -A[row][unknown];
        }
    }
    // Gaussian elimination
    for(int i=0;i<unknown;i++){
        // Partial pivot
        int pivot = i;
        for(int j=i+1;j<unknown;j++) if(fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        if(fabs(A[pivot][i]) < EPS){
            // No unique solution
            // Not expected per problem statement
            continue;
        }
        // Swap
        for(int j=i;j<=unknown;j++) {
            double tmp = A[i][j];
            A[i][j] = A[pivot][j];
            A[pivot][j] = tmp;
        }
        // Eliminate
        for(int j=i+1;j<unknown;j++){
            double factor = A[j][i] / A[i][i];
            for(int l=i;l<=unknown;l++) A[j][l] -= factor * A[i][l];
        }
    }
    // Back substitution
    double sol[MAXN];
    for(int i=0;i<unknown;i++) sol[i] =0.0;
    for(int i=unknown-1;i>=0;i--){
        double sum = A[i][unknown];
        for(int j=i+1;j<unknown;j++) sum -= A[i][j] * sol[j];
        sol[i] = sum / A[i][i];
    }
    // Assign voltages
    for(int i=1;i<=n;i++) {
        if(voltage[i]==-1){
            voltage[i] = sol[idx[i]];
        }
    }
    // Process queries
    for(int i=0;i<q;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        double diff = voltage[a] - voltage[b];
        printf("%.2lf\n", diff);
    }
    return 0;
}