#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000
#define LOGN 17

int main(){
    int n;
    scanf("%d", &n);
    int *y = (int*)malloc(n * sizeof(int));
    int *r = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d %d", &y[i], &r[i]);
    
    // Build log table
    int log_table[MAXN+1];
    log_table[1] = 0;
    for(int i=2;i<=n;i++) log_table[i] = log_table[i/2] + 1;
    
    // Build sparse table
    int st[MAXN][LOGN];
    for(int i=0;i<n;i++) st[i][0] = r[i];
    for(int j=1; (1<<j) <= n; j++){
        for(int i=0; i + (1<<j) <= n; i++){
            if(st[i][j-1] > st[i + (1<<(j-1))][j-1])
                st[i][j] = st[i][j-1];
            else
                st[i][j] = st[i + (1<<(j-1))][j-1];
        }
    }
    
    // Function to find index using binary search
    // Returns index if found, -1 otherwise
    int find_index(int key){
        int left=0, right=n-1, mid;
        while(left <= right){
            mid = left + (right - left)/2;
            if(y[mid] == key) return mid;
            else if(y[mid] < key) left = mid +1;
            else right = mid -1;
        }
        return -1;
    }
    
    int m;
    scanf("%d", &m);
    while(m--){
        int Y, X;
        scanf("%d %d", &Y, &X);
        int idxY = find_index(Y);
        int idxX = find_index(X);
        if(idxY == -1 || idxX == -1){
            printf("maybe\n");
            continue;
        }
        int rY = r[idxY];
        int rX = r[idxX];
        if(rX > rY){
            printf("false\n");
            continue;
        }
        if(idxY +1 > idxX -1){
            // No Z between Y and X
            printf("true\n");
            continue;
        }
        // Query max in [idxY+1, idxX-1]
        int l = idxY +1;
        int rr = idxX -1;
        int length = rr - l +1;
        int j = log_table[length];
        int max_r = st[l][j] > st[rr - (1<<j) +1][j] ? st[l][j] : st[rr - (1<<j) +1][j];
        if(max_r >= rX){
            printf("false\n");
            continue;
        }
        long long total_possible = (long long)X - Y -1;
        int total_known = rr - l +1;
        if(total_possible == total_known){
            printf("true\n");
        }
        else{
            printf("maybe\n");
        }
    }
    
    free(y);
    free(r);
    return 0;
}