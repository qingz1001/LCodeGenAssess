#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 151
#define MAXM 501

long long grid[MAXN][MAXM];
long long prefix[MAXN][MAXM];
int n, m;

// Function to compute prefix sums
void compute_prefix() {
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            prefix[i][j] = grid[i][j] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }
}

// Function to get sum of rectangle from (x1,y1) to (x2,y2)
long long get_sum(int x1, int y1, int x2, int y2){
    if(x1 > x2 || y1 > y2) return 0;
    return prefix[y2][x2] - prefix[y1-1][x2] - prefix[y2][x1-1] + prefix[y1-1][x1-1];
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            scanf("%lld", &grid[i][j]);
        }
    }
    compute_prefix();
    long long max_sum = LLONG_MIN;
    
    // Iterate over possible N configurations
    for(int L1=1; L1<=m-2; L1++) {
        for(int B1=1; B1<=n-2; B1++) {
            for(int R1=L1; R1<=m-2; R1++) {
                for(int T1=B1; T1<=n-1; T1++) {
                    // Second rectangle
                    int L2 = R1 +1;
                    if(L2 > m-1) continue;
                    for(int B2=B1+1; B2<=n-1; B2++) {
                        int T2 = T1;
                        // Third rectangle onwards
                        for(int K=3; K<=m-L1+1; K++) {
                            // Simplified N shape: extend to the right with possible variations
                            // Compute N sum
                            long long sumN = 0;
                            for(int k=0; k<K; k++) {
                                int Lk = L1 + k;
                                int Rk = Lk;
                                int Bk = B1;
                                int Tk = T1;
                                sumN += get_sum(Lk, Bk, Rk, Tk);
                            }
                            // Place O
                            for(int u = R1 +2; u<=m-2; u++) {
                                for(int v=1; v<=n-2; v++) {
                                    for(int W=3; W<=m-u+1 && W<=m; W++) {
                                        for(int H=3; H<=n-v+1 && H<=n; H++) {
                                            // Sum O
                                            long long sumO = get_sum(u, v, u+W-1, v+H-1) - get_sum(u+1, v+1, u+W-2, v+H-2);
                                            // Place I
                                            for(int P = u+W+1; P<=m-2; P++) {
                                                for(int Q=1; Q<=n-2; Q++) {
                                                    // Assuming fixed I shape
                                                    long long sumI = get_sum(P, Q, P, Q) + get_sum(P, Q+1, P, Q+1) + get_sum(P, Q+2, P, Q+2);
                                                    long long total = sumN + sumO + sumI;
                                                    if(total > max_sum) max_sum = total;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n", max_sum);
    return 0;
}