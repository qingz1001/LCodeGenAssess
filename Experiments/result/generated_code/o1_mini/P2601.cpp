#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    // Allocate memory for matrix
    long long **a = (long long **)malloc(n * sizeof(long long *));
    for(int i = 0; i < n; i++){
        a[i] = (long long *)malloc(m * sizeof(long long));
        for(int j = 0; j < m; j++){
            scanf("%lld", &a[i][j]);
        }
    }
    int min_dim = n < m ? n : m;
    long long ans = 0;
    for(int s = 1; s <= min_dim; s++){
        for(int i = 0; i <= n - s; i++){
            for(int j = 0; j <= m - s; j++){
                int symmetric = 1;
                // Check horizontal symmetry
                for(int k = 0; k < s / 2 && symmetric; k++){
                    for(int l = 0; l < s; l++){
                        if(a[i + k][j + l] != a[i + s - 1 - k][j + l]){
                            symmetric = 0;
                            break;
                        }
                    }
                }
                if(!symmetric) continue;
                // Check vertical symmetry
                for(int p = 0; p < s && symmetric; p++){
                    for(int q = 0; q < s / 2; q++){
                        if(a[i + p][j + q] != a[i + p][j + s - 1 - q]){
                            symmetric = 0;
                            break;
                        }
                    }
                }
                if(symmetric){
                    ans++;
                }
            }
        }
    }
    printf("%lld\n", ans);
    // Free memory
    for(int i = 0; i < n; i++) free(a[i]);
    free(a);
    return 0;
}