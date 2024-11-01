#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_P 1000
#define MAX_R 200
#define MAX_C 500000
#define MAX_M 200000

// For R > 1
long long count_P_large[1001][201][201];

// For R = 1
int pos_all_size[1001];
int *pos_all[1001];
long long sum_all[1001];
int C_limit;

// Function to compare integers in descending order
int cmp_desc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main(){
    int R, C, M;
    scanf("%d %d %d", &R, &C, &M);
    
    if(R == 1){
        // Handle R = 1
        int *P = (int*)malloc((C+1) * sizeof(int));
        for(int j=1; j<=C; j++) {
            scanf("%d", &P[j]);
        }
        
        // Count number of each P
        int count_P[1001];
        memset(count_P, 0, sizeof(count_P));
        for(int j=1; j<=C; j++) {
            count_P[P[j]]++;
        }
        
        // Compute offsets
        int offset[1001];
        offset[1] = 0;
        for(int p=2; p<=MAX_P; p++) {
            offset[p] = offset[p-1] + count_P[p-1];
        }
        
        // Allocate pos_all arrays
        for(int p=1; p<=MAX_P; p++) {
            if(count_P[p] > 0){
                pos_all[p] = (int*)malloc(count_P[p] * sizeof(int));
            }
            else{
                pos_all[p] = NULL;
            }
            pos_all_size[p] = 0;
        }
        
        // Fill pos_all
        for(int j=1; j<=C; j++) {
            int p_val = P[j];
            if(pos_all[p_val] != NULL){
                pos_all[p_val][pos_all_size[p_val]++] = j;
            }
        }
        
        // Read and process queries
        for(int q=0; q<M; q++){
            int x1, y1, x2, y2;
            long long H;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &H);
            // Since R=1, x1 and x2 should be 1
            // Calculate total sum
            long long total = 0;
            // To calculate total sum, iterate P from 1 to 1000
            for(int p=1; p<=MAX_P; p++) {
                if(pos_all[p] != NULL){
                    // Binary search for number of p in [y1, y2]
                    // Using pos_all[p] which is sorted
                    int *arr = pos_all[p];
                    int size = pos_all_size[p];
                    // Find leftmost >= y1
                    int l = 0, r = size;
                    while(l < r){
                        int m = l + (r - l)/2;
                        if(arr[m] >= y1) r = m;
                        else l = m +1;
                    }
                    int left_idx = l;
                    // Find rightmost <= y2
                    l = 0; r = size;
                    while(l < r){
                        int m = l + (r - l)/2;
                        if(arr[m] > y2) r = m;
                        else l = m +1;
                    }
                    int right_idx = l;
                    int cnt = right_idx - left_idx;
                    total += (long long)p * cnt;
                }
            }
            if(total < H){
                printf("Poor QLW\n");
                continue;
            }
            // Binary search for minimal k
            int left = 1;
            int right = C;
            int answer = C +1;
            while(left <= right){
                int mid = left + (right - left)/2;
                long long sum = 0;
                int taken = 0;
                for(int p=MAX_P; p>=1; p--){
                    if(pos_all[p] != NULL){
                        // Binary search for number of p in [y1, y2]
                        int *arr = pos_all[p];
                        int size = pos_all_size[p];
                        // Find leftmost >= y1
                        int l_idx = 0, r_idx = size;
                        while(l_idx < r_idx){
                            int m = l_idx + (r_idx - l_idx)/2;
                            if(arr[m] >= y1) r_idx = m;
                            else l_idx = m +1;
                        }
                        int left_idx = l_idx;
                        // Find rightmost <= y2
                        l_idx = 0; r_idx = size;
                        while(l_idx < r_idx){
                            int m = l_idx + (r_idx - l_idx)/2;
                            if(arr[m] > y2) r_idx = m;
                            else l_idx = m +1;
                        }
                        int right_idx = l_idx;
                        int cnt = right_idx - left_idx;
                        if(cnt > 0){
                            int t = (cnt < (mid - taken)) ? cnt : (mid - taken);
                            sum += (long long)p * t;
                            taken += t;
                            if(taken == mid) break;
                        }
                    }
                }
                if(sum >= H){
                    answer = mid;
                    right = mid -1;
                }
                else{
                    left = mid +1;
                }
            }
            if(answer <= C){
                printf("%d\n", answer);
            }
            else{
                printf("Poor QLW\n");
            }
        }
        
        // Free allocated memory
        for(int p=1; p<=MAX_P; p++) {
            if(pos_all[p] != NULL){
                free(pos_all[p]);
            }
        }
        free(P);
    }
    else{
        // Handle R > 1
        if(R > 200 || C > 200){
            // To prevent excessive memory, assuming R and C up to 200
            // Adjust if necessary
        }
        int P_matrix[201][201];
        for(int i=1; i<=R; i++) {
            for(int j=1; j<=C; j++) {
                scanf("%d", &P_matrix[i][j]);
            }
        }
        // Build prefix sums for each P
        for(int p=1; p<=MAX_P; p++) {
            for(int i=1; i<=R; i++) {
                for(int j=1; j<=C; j++) {
                    count_P_large[p][i][j] = count_P_large[p][i-1][j] + count_P_large[p][i][j-1] - count_P_large[p][i-1][j-1];
                    if(P_matrix[i][j] == p){
                        count_P_large[p][i][j]++;
                    }
                }
            }
        }
        // Build total prefix sum
        long long total_prefix[201][201];
        for(int i=1; i<=R; i++) {
            for(int j=1; j<=C; j++) {
                total_prefix[i][j] = total_prefix[i-1][j] + total_prefix[i][j-1] - total_prefix[i-1][j-1] + P_matrix[i][j];
            }
        }
        // Process queries
        for(int q=0; q<M; q++){
            int x1, y1, x2, y2;
            long long H;
            scanf("%d %d %d %d %lld", &x1, &y1, &x2, &y2, &H);
            // Calculate total sum
            long long total = total_prefix[x2][y2] - total_prefix[x1-1][y2] - total_prefix[x2][y1-1] + total_prefix[x1-1][y1-1];
            if(total < H){
                printf("Poor QLW\n");
                continue;
            }
            // Gather counts for each P
            int c_p[1001];
            for(int p=1; p<=MAX_P; p++) {
                c_p[p] = count_P_large[p][x2][y2] - count_P_large[p][x1-1][y2] - count_P_large[p][x2][y1-1] + count_P_large[p][x1-1][y1-1];
            }
            // Binary search for minimal k
            int N = (x2 - x1 +1) * (y2 - y1 +1);
            int left = 1;
            int right = N;
            int answer = N +1;
            while(left <= right){
                int mid = left + (right - left)/2;
                long long sum = 0;
                int taken = 0;
                for(int p=MAX_P; p>=1; p--){
                    if(c_p[p] >0){
                        int t = (c_p[p] < (mid - taken)) ? c_p[p] : (mid - taken);
                        sum += (long long)p * t;
                        taken += t;
                        if(taken == mid) break;
                    }
                }
                if(sum >= H){
                    answer = mid;
                    right = mid -1;
                }
                else{
                    left = mid +1;
                }
            }
            if(answer <= N){
                printf("%d\n", answer);
            }
            else{
                printf("Poor QLW\n");
            }
        }
    }
    return 0;
}