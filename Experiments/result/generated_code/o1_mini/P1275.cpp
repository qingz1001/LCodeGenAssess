#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to compare two strings for qsort
int compare_strings(const void *a, const void *b){
    const char *sa = *(const char **)a;
    const char *sb = *(const char **)b;
    return strcmp(sa, sb);
}

// Custom strdup implementation
char *my_strdup_custom(const char *s){
    int len = strlen(s);
    char *dup = (char *)malloc((len + 1) * sizeof(char));
    if(dup){
        strcpy(dup, s);
    }
    return dup;
}

int main(){
    int k;
    scanf("%d", &k);
    while(k--){
        int n, m;
        scanf("%d %d", &n, &m);
        // Allocate grids
        int **A = (int **)malloc(n * sizeof(int *));
        int **Bgrid = (int **)malloc(n * sizeof(int *));
        for(int i=0; i<n; i++){
            A[i] = (int *)malloc(m * sizeof(int));
            for(int j=0; j<m; j++){
                scanf("%d", &A[i][j]);
            }
        }
        for(int i=0; i<n; i++){
            Bgrid[i] = (int *)malloc(m * sizeof(int));
            for(int j=0; j<m; j++){
                scanf("%d", &Bgrid[i][j]);
            }
        }
        // Extract column patterns for A and B
        char **colA = (char **)malloc(m * sizeof(char *));
        char **colB = (char **)malloc(m * sizeof(char *));
        for(int j=0; j<m; j++){
            colA[j] = (char *)malloc((n + 1) * sizeof(char));
            colB[j] = (char *)malloc((n + 1) * sizeof(char));
            for(int i=0; i<n; i++){
                colA[j][i] = A[i][j] + '0';
                colB[j][i] = Bgrid[i][j] + '0';
            }
            colA[j][n] = '\0';
            colB[j][n] = '\0';
        }
        // Create sorted list of B's columns
        char **sortedColB = (char **)malloc(m * sizeof(char *));
        for(int j=0; j<m; j++){
            sortedColB[j] = my_strdup_custom(colB[j]);
        }
        qsort(sortedColB, m, sizeof(char *), compare_strings);
        int success = 0;
        // Iterate over all possible F by pairing A's and B's columns
        for(int i=0; i<m && !success; i++){
            for(int j=0; j<m && !success; j++){
                // Compute F as XOR of A's column i and B's column j
                int *F = (int *)malloc(n * sizeof(int));
                for(int x=0; x<n; x++){
                    F[x] = (colA[i][x] - '0') ^ (colB[j][x] - '0');
                }
                // Apply F to all columns of A to get transformed columns
                char **transformed_col = (char **)malloc(m * sizeof(char *));
                for(int k=0; k<m; k++){
                    transformed_col[k] = (char *)malloc((n + 1) * sizeof(char));
                    for(int x=0; x<n; x++){
                        transformed_col[k][x] = ((colA[k][x] - '0') ^ F[x]) + '0';
                    }
                    transformed_col[k][n] = '\0';
                }
                // Sort transformed columns
                char **sortedTransCol = (char **)malloc(m * sizeof(char *));
                for(int k=0; k<m; k++){
                    sortedTransCol[k] = my_strdup_custom(transformed_col[k]);
                }
                qsort(sortedTransCol, m, sizeof(char *), compare_strings);
                // Compare sorted transformed columns with sorted B's columns
                int match = 1;
                for(int k=0; k<m && match; k++){
                    if(strcmp(sortedTransCol[k], sortedColB[k]) != 0){
                        match = 0;
                    }
                }
                if(match){
                    success = 1;
                }
                // Free transformed columns
                for(int k=0; k<m; k++){
                    free(transformed_col[k]);
                    free(sortedTransCol[k]);
                }
                free(F);
                free(transformed_col);
                free(sortedTransCol);
            }
        }
        if(success){
            printf("YES\n");
        }
        else{
            printf("NO\n");
        }
        // Free all allocated memory for this test case
        for(int j=0; j<m; j++){
            free(A[j]);
            free(Bgrid[j]);
            free(colA[j]);
            free(colB[j]);
            free(sortedColB[j]);
        }
        free(A);
        free(Bgrid);
        free(colA);
        free(colB);
        free(sortedColB);
    }
    return 0;
}