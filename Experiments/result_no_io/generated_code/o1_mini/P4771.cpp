#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_K 100000

int cmp_int(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return ia - ib;
}

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    
    // Allocate height array with 1-based indexing
    int h[MAX_N +2][MAX_M +2];
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            scanf("%d", &h[i][j]);
        }
    }
    
    // Allocate mountains arrays
    int mountains[MAX_N +1][MAX_M];
    int count_rows[MAX_N +1];
    for(int i=1;i<=N;i++) count_rows[i] =0;
    
    // Identify mountains
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            int is_mountain =1;
            if(i >1 && h[i-1][j] > h[i][j]) is_mountain =0;
            if(i <N && h[i+1][j] > h[i][j]) is_mountain =0;
            if(j >1 && h[i][j-1] > h[i][j]) is_mountain =0;
            if(j <M && h[i][j+1] > h[i][j]) is_mountain =0;
            if(is_mountain){
                mountains[i][count_rows[i]++] = j;
            }
        }
        if(count_rows[i] >0){
            qsort(mountains[i], count_rows[i], sizeof(int), cmp_int);
        }
    }
    
    // Read K queries
    int query_a[MAX_K];
    int query_b[MAX_K];
    for(int q=0; q<K; q++){
        scanf("%d %d", &query_a[q], &query_b[q]);
    }
    
    // Process each query
    for(int q=0; q<K; q++){
        int a = query_a[q];
        int b = query_b[q];
        int low =0;
        int high = a -1;
        int answer = -1;
        while(low <= high){
            int mid = low + (high - low)/2;
            int x = a - mid;
            int l = b - mid;
            if(l <1) l =1;
            int r = b + mid;
            if(r > M) r = M;
            if(count_rows[x] ==0){
                low = mid +1;
                continue;
            }
            // Binary search for first y >= l
            int left =0, right = count_rows[x]-1, pos = count_rows[x];
            while(left <= right){
                int m = left + (right - left)/2;
                if(mountains[x][m] >= l){
                    pos = m;
                    right = m -1;
                }
                else{
                    left = m +1;
                }
            }
            if(pos < count_rows[x] && mountains[x][pos] <= r){
                answer = mid;
                high = mid -1;
            }
            else{
                low = mid +1;
            }
        }
        if(answer != -1){
            printf("%d\n", answer);
        }
        else{
            printf("Pool Babingbaboom!\n");
        }
    }
    
    return 0;
}