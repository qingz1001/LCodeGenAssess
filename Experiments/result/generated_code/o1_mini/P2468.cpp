#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 1001
#define MAX_R 200
#define MAX_C 500000

int main(){
    int R, C, M;
    scanf("%d %d %d", &R, &C, &M);
    
    int **P_matrix;
    if(R >1){
        // Allocate P_matrix
        P_matrix = (int **)malloc((R+1) * sizeof(int *));
        for(int i=0;i<=R;i++) P_matrix[i] = (int *)malloc((C+1)*sizeof(int));
        for(int i=1;i<=R;i++) {
            for(int j=1;j<=C;j++) {
                scanf("%d", &P_matrix[i][j]);
            }
        }
    }
    else{
        // R ==1, allocate single row
        // To handle large C, use 1-based indexing
        P_matrix = (int **)malloc(2 * sizeof(int *));
        P_matrix[1] = (int *)malloc((C+1)*sizeof(int));
        for(int j=1;j<=C;j++) {
            scanf("%d", &P_matrix[1][j]);
        }
    }
    
    // Initialize prefix sums
    // Since P <=1000
    // For R==1, use 2D prefix_p[P][C+1]
    // For R>1, use 3D prefix_p[P][R+1][C+1]
    // To save memory, use 1D arrays and access accordingly
    
    // For R >1
    int ***prefix = NULL;
    if(R >1){
        prefix = (int ***)malloc((MAX_P) * sizeof(int **));
        for(int p=1;p<MAX_P;p++){
            prefix[p] = (int **)malloc((R+1) * sizeof(int *));
            for(int i=0;i<=R;i++) {
                prefix[p][i] = (int *)malloc((C+1)*sizeof(int));
                memset(prefix[p][i], 0, (C+1)*sizeof(int));
            }
        }
        for(int p=1;p<MAX_P;p++){
            for(int i=1;i<=R;i++){
                for(int j=1;j<=C;j++){
                    prefix[p][i][j] = prefix[p][i-1][j] + prefix[p][i][j-1] - prefix[p][i-1][j-1] + (P_matrix[i][j] == p ? 1 : 0);
                }
            }
        }
    }
    else{
        // R ==1
        // Allocate prefix_p[P][C+1]
        // To save memory, use a 2D array
        // We can use a 1D array of pointers
        int **prefix_p = (int **)malloc(MAX_P * sizeof(int *));
        for(int p=1;p<MAX_P;p++){
            prefix_p[p] = (int *)malloc((C+1)*sizeof(int));
            prefix_p[p][0] = 0;
            for(int j=1;j<=C;j++){
                prefix_p[p][j] = prefix_p[p][j-1] + ((P_matrix[1][j] == p) ? 1 : 0);
            }
        }
        
        // Process queries
        for(int q=0; q<M; q++){
            int x1, y1, x2, y2;
            long long H;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &H);
            // Since R==1, x1 and x2 must be 1
            // y1 to y2
            long long sum =0;
            int count =0;
            for(int p=1000;p>=1;p--){
                int cnt = prefix_p[p][y2] - prefix_p[p][y1-1];
                if(cnt ==0) continue;
                long long add = (long long)p * cnt;
                if(sum + add >= H){
                    long long need = H - sum;
                    if(need <=0){
                        break;
                    }
                    long long k = (need + p -1)/p;
                    if(k > cnt) k = cnt;
                    count += k;
                    sum += k * (long long)p;
                    break;
                }
                else{
                    sum += add;
                    count += cnt;
                }
            }
            if(sum >= H){
                printf("%d\n", count);
            }
            else{
                printf("Poor QLW\n");
            }
        }
        
        // Free prefix_p
        for(int p=1;p<MAX_P;p++) free(prefix_p[p]);
        free(prefix_p);
    }
    
    if(R >1){
        // Allocate a temporary array for query
        for(int q=0; q<M; q++){
            int x1, y1, x2, y2;
            long long H;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &H);
            long long sum =0;
            int count =0;
            for(int p=1000;p>=1;p--){
                int cnt = prefix[p][x2][y2] - prefix[p][x1-1][y2] - prefix[p][x2][y1-1] + prefix[p][x1-1][y1-1];
                if(cnt ==0) continue;
                long long add = (long long)p * cnt;
                if(sum + add >= H){
                    long long need = H - sum;
                    if(need <=0){
                        break;
                    }
                    long long k = (need + p -1)/p;
                    if(k > cnt) k = cnt;
                    count += k;
                    sum += k * (long long)p;
                    break;
                }
                else{
                    sum += add;
                    count += cnt;
                }
            }
            if(sum >= H){
                printf("%d\n", count);
            }
            else{
                printf("Poor QLW\n");
            }
        }
        // Free prefix
        for(int p=1;p<MAX_P;p++){
            for(int i=0;i<=R;i++) free(prefix[p][i]);
            free(prefix[p]);
        }
        free(prefix);
    }
    
    // Free P_matrix
    if(R >1){
        for(int i=0;i<=R;i++) free(P_matrix[i]);
    }
    else{
        free(P_matrix[1]);
    }
    free(P_matrix);
    
    return 0;
}