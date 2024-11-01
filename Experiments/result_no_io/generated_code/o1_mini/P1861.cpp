#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int **Ini = (int **)malloc(N * sizeof(int *));
    int **Fin = (int **)malloc(N * sizeof(int *));
    for(int i=0;i<N;i++){
        Ini[i] = (int *)malloc(M * sizeof(int));
        for(int j=0;j<M;j++) scanf("%d", &Ini[i][j]);
    }
    // Read empty line
    char c;
    while((c = getchar()) != '\n' && c != EOF);
    for(int i=0;i<N;i++){
        Fin[i] = (int *)malloc(M * sizeof(int));
        for(int j=0;j<M;j++) scanf("%d", &Fin[i][j]);
    }
    // Compute D = Ini - Fin
    int **D = (int **)malloc(N * sizeof(int *));
    for(int i=0;i<N;i++){
        D[i] = (int *)malloc(M * sizeof(int));
        for(int j=0;j<M;j++) D[i][j] = Ini[i][j] - Fin[i][j];
    }
    ll total_magic =0;
    // Maximum possible magic is max(N,M)-1
    int max_magic = (N > M ? N : M) -1;
    for(int magic = max_magic; magic >=1; magic--){
        // Rows
        for(int i=0;i<N;i++){
            // Distance = magic +1
            int distance = magic +1;
            if(distance > M) continue;
            for(int j=0; j + distance < M; j++){
                int a = D[i][j];
                int b = D[i][j + distance];
                if(a >0 && b >0){
                    int cnt = a < b ? a : b;
                    D[i][j] -= cnt;
                    D[i][j + distance] -= cnt;
                    total_magic += (ll)cnt * magic;
                }
            }
        }
        // Columns
        for(int j=0;j<M;j++){
            int distance = magic +1;
            if(distance > N) continue;
            for(int i=0; i + distance < N; i++){
                int a = D[i][j];
                int b = D[i + distance][j];
                if(a >0 && b >0){
                    int cnt = a < b ? a : b;
                    D[i][j] -= cnt;
                    D[i + distance][j] -= cnt;
                    total_magic += (ll)cnt * magic;
                }
            }
        }
    }
    printf("%lld\n", total_magic);
    // Free memory
    for(int i=0;i<N;i++){
        free(Ini[i]);
        free(Fin[i]);
        free(D[i]);
    }
    free(Ini);
    free(Fin);
    free(D);
    return 0;
}