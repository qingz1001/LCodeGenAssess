#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
    int k;
    scanf("%d", &k);
    while(k--)
    {
        int n, m;
        scanf("%d %d", &n, &m);
        int grid1[MAX_N][MAX_M], grid2[MAX_N][MAX_M];
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                scanf("%d", &grid1[i][j]);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                scanf("%d", &grid2[i][j]);
        char *grid1_cols[MAX_M];
        for(int j=0; j<m; j++){
            grid1_cols[j] = (char*)malloc(n+1);
            for(int i=0;i<n;i++)
                grid1_cols[j][i] = grid1[i][j] ? '1' : '0';
            grid1_cols[j][n] = '\0';
        }
        qsort(grid1_cols, m, sizeof(char*), cmp);
        int flag=0;
        for(int j=0; j<m && !flag; j++){
            char F[MAX_N];
            for(int i=0;i<n;i++){
                F[i] = grid1[i][0] ^ grid2[i][j];
            }
            char *trans_cols[MAX_M];
            for(int cj=0; cj<m; cj++){
                trans_cols[cj] = (char*)malloc(n+1);
                for(int i=0;i<n;i++){
                    trans_cols[cj][i] = (grid2[i][cj] ^ F[i]) ? '1' : '0';
                }
                trans_cols[cj][n] = '\0';
            }
            qsort(trans_cols, m, sizeof(char*), cmp);
            int match=1;
            for(int cj=0; cj<m && match; cj++){
                if(strcmp(grid1_cols[cj], trans_cols[cj]) != 0){
                    match=0;
                }
            }
            for(int cj=0; cj<m; cj++){
                free(trans_cols[cj]);
            }
            if(match){
                flag=1;
            }
        }
        for(int j=0; j<m; j++) free(grid1_cols[j]);
        printf("%s\n", flag ? "YES" : "NO");
    }
}