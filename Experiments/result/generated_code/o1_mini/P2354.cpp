#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXK 4001 // Maximum N + M -1
#define MAXNM 1001 // Maximum N and M

typedef struct {
    int *data;
    int size;
} List;

// Function to compare two lists lex order
int compare_lists(int *a, int *b, int size) {
    for(int i = 0; i < size; i++) {
        if(a[i] < b[i]) return -1;
        if(a[i] > b[i]) return 1;
    }
    return 0;
}

// Function to copy list src to dest
void copy_list(int *src, int *dest, int size) {
    memcpy(dest, src, sizeof(int)*size);
}

// Function to insert and sort
void insert_and_sort(int *src, int src_size, int val, int *dest, int *dest_size) {
    int temp[MAXK];
    int i=0, j=0;
    while(i < src_size && src[i] < val) {
        temp[j++] = src[i++];
    }
    temp[j++] = val;
    while(i < src_size) {
        temp[j++] = src[i++];
    }
    memcpy(dest, temp, sizeof(int)*j);
    *dest_size = j;
}

int main(){
    unsigned long long x0, a, b, c, d;
    scanf("%llu %llu %llu %llu %llu", &x0, &a, &b, &c, &d);
    int N, M, Q;
    scanf("%d %d %d", &N, &M, &Q);
    int K = N * M;
    unsigned long long x[K];
    x[0] = x0;
    for(int i =1;i<K;i++) {
        x[i] = (a * x[i-1] * x[i-1] + b * x[i-1] + c) % d;
    }
    // Initialize T
    int T[K];
    for(int i=0;i<K;i++) T[i] = i+1;
    // Perform initial K swaps
    for(int i=1;i<=K;i++) {
        int pos = (x[i-1] % i);
        // Swap T[i-1] and T[pos]
        int temp_val = T[i-1];
        T[i-1] = T[pos];
        T[pos] = temp_val;
    }
    // Perform Q additional swaps
    for(int i=0;i<Q;i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        // Swap T[u-1] and T[v-1]
        int temp_val = T[u-1];
        T[u-1] = T[v-1];
        T[v-1] = temp_val;
    }
    // Fill the grid
    int grid[N+1][M+1];
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            grid[i][j] = T[(i-1)*M + (j-1)];
        }
    }
    // Initialize DP arrays
    // Using a 2D array of int[MAXK]
    int dp[N+1][M+1][MAXK];
    int dp_size[N+1][M+1];
    memset(dp_size, 0, sizeof(dp_size));
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            if(i ==1 && j ==1){
                dp[i][j][0] = grid[i][j];
                dp_size[i][j] =1;
            }
            else {
                if(i ==1){
                    // From left
                    int temp[MAXK];
                    insert_and_sort(dp[i][j-1], dp[i][j-1][0], grid[i][j], temp, &(temp[0]));
                    // Merge
                    insert_and_sort(dp[i][j-1], dp_size[i][j-1], grid[i][j], dp[i][j], &dp_size[i][j]);
                }
                else if(j ==1){
                    // From top
                    insert_and_sort(dp[i-1][j], dp_size[i-1][j], grid[i][j], dp[i][j], &dp_size[i][j]);
                }
                else{
                    // From top
                    int temp1[MAXK];
                    int size1;
                    insert_and_sort(dp[i-1][j], dp_size[i-1][j], grid[i][j], temp1, &size1);
                    // From left
                    int temp2[MAXK];
                    int size2;
                    insert_and_sort(dp[i][j-1], dp_size[i][j-1], grid[i][j], temp2, &size2);
                    // Compare temp1 and temp2
                    if(compare_lists(temp1, temp2, size1) <=0 ){
                        copy_list(temp1, dp[i][j], size1);
                        dp_size[i][j] = size1;
                    }
                    else{
                        copy_list(temp2, dp[i][j], size2);
                        dp_size[i][j] = size2;
                    }
                }
            }
        }
    }
    // Now dp[N][M] contains the sorted path sequence
    // Sort it to ensure
    int result[MAXK];
    memcpy(result, dp[N][M], sizeof(int)*dp_size[N][M]);
    // Sort the result
    for(int i=0;i<dp_size[N][M]-1;i++) {
        for(int j=i+1;j<dp_size[N][M];j++) {
            if(result[i] > result[j]){
                int tmp = result[i];
                result[i] = result[j];
                result[j] = tmp;
            }
        }
    }
    // Print the result
    for(int i=0;i<dp_size[N][M];i++) {
        if(i>0) printf(" ");
        printf("%d", result[i]);
    }
    return 0;
}