#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define INF 18446744073709551615ULL

typedef unsigned long long ull;

// Function to compute power with overflow check
ull power_pow(ull base, int exp) {
    ull result = 1;
    for(int i=0;i<exp;i++) {
        if(result > INF / base) return INF;
        result *= base;
    }
    return result;
}

// Function to find the j with sum_plus_j[j] closest to target
int find_closest_j(ull* sum_plus_j, int left, int right, ull target) {
    if(left > right) return -1;
    int best = left;
    while(left <= right) {
        int mid = left + (right - left) /2;
        if(sum_plus_j[mid] == target) {
            return mid;
        }
        if(sum_plus_j[mid] < target) {
            left = mid +1;
        }
        else {
            right = mid -1;
        }
    }
    // Now left is the first greater than target
    if(left > 0 && left <= right +1) {
        if(left == (right +1)) {
            if(left <0) return best;
            if(left >=0) best = left;
        }
        if(left <0) return best;
        if(left <0) return best;
        if(left >=1 && left <= right +1) {
            if(left <0) return best;
            ull diff1 = (left < (int)(right +1)) ? 0 : INF;
            ull diff2 = (left-1 >=0)? (target > sum_plus_j[left-1] ? target - sum_plus_j[left-1] : sum_plus_j[left-1] - target) : INF;
            if(left <0) return best;
            if(left <= right +1 && left >=0 && (left <0 || (diff2 < diff1))) {
                best = left-1;
            }
            else {
                best = left;
            }
        }
    }
    // Now compare best and best+1
    if(best <0) best =0;
    if(best > right) best = right;
    if(best < right) {
        if(sum_plus_j[best+1] - target < target - sum_plus_j[best]) {
            best = best+1;
        }
    }
    return best;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int N, L, P;
        scanf("%d %d %d", &N, &L, &P);
        // Allocate memory
        char **sentences = (char **)malloc(N * sizeof(char *));
        int *lengths = (int *)malloc(N * sizeof(int));
        for(int i=0;i<N;i++){
            // Read a line
            char buffer[35];
            scanf(" %[^\n]", buffer);
            int len = strlen(buffer);
            lengths[i] = len;
            sentences[i] = (char *)malloc((len+1)*sizeof(char));
            strcpy(sentences[i], buffer);
        }
        // Compute sum_len and sum_plus_j
        ull *sum_len = (ull *)malloc((N+1)*sizeof(ull));
        sum_len[0] =0;
        for(int i=1;i<=N;i++) {
            sum_len[i] = sum_len[i-1] + (ull)lengths[i-1];
        }
        ull *sum_plus_j = (ull *)malloc((N+1)*sizeof(ull));
        for(int j=0;j<=N;j++) {
            sum_plus_j[j] = sum_len[j] + (ull)j;
        }
        // Initialize dp and prev
        ull *dp = (ull *)malloc((N+1)*sizeof(ull));
        int *prev = (int *)malloc((N+1)*sizeof(int));
        dp[0] =0;
        for(int i=1;i<=N;i++) {
            ull target = sum_len[i] + (ull)(i) -1 - (ull)L;
            // Binary search to find j
            int left =0, right = i-1;
            int j =0;
            if(left <= right){
                int low = left, high = right, mid;
                j = left;
                while(low <= high){
                    mid = low + (high - low)/2;
                    if(sum_plus_j[mid] == target){
                        j = mid;
                        break;
                    }
                    if(sum_plus_j[mid] < target){
                        low = mid +1;
                    }
                    else{
                        high = mid -1;
                    }
                }
                if(sum_plus_j[j] != target){
                    // Find the closest
                    if(j == i-1){
                        // Compare j and j-1
                        if(j >0){
                            if( (sum_plus_j[j] > target ? sum_plus_j[j]-target : target - sum_plus_j[j]) >= 
                                (sum_plus_j[j-1] > target ? sum_plus_j[j-1]-target : target - sum_plus_j[j-1]) ){
                                j = j-1;
                            }
                        }
                    }
                    else{
                        // Compare j and j+1
                        if(j+1 <= right){
                            ull diff1 = sum_plus_j[j] > target ? sum_plus_j[j]-target : target - sum_plus_j[j];
                            ull diff2 = sum_plus_j[j+1] > target ? sum_plus_j[j+1]-target : target - sum_plus_j[j+1];
                            if(diff2 < diff1){
                                j = j+1;
                            }
                        }
                    }
                }
            }
            // Now j is the best
            ull diff = (sum_plus_j[j] > target) ? (sum_plus_j[j] - target) : (target - sum_plus_j[j]);
            ull mismatch = power_pow(diff, P);
            if(dp[j] == INF || mismatch == INF || dp[j] > INF - mismatch){
                dp[i] = INF;
                prev[i] = -1;
            }
            else{
                dp[i] = dp[j] + mismatch;
                prev[i] = j;
            }
        }
        if(dp[N] > 1000000000000000000ULL){
            printf("Too hard to arrange\n");
        }
        else{
            printf("%llu\n", dp[N]);
            // Reconstruct the path
            int *breaks = (int *)malloc((N+1)*sizeof(int));
            int cnt=0;
            int pos = N;
            while(pos >0){
                breaks[cnt++] = pos;
                pos = prev[pos];
                if(pos == -1){
                    break;
                }
            }
            // Now breaks[0..cnt-1] has the end positions in reverse
            // Collect the lines
            char ***lines = (char ***)malloc(cnt * sizeof(char **));
            int *line_counts = (int *)malloc(cnt * sizeof(int));
            for(int i=0;i<cnt;i++) {
                lines[i] = NULL;
                line_counts[i] =0;
            }
            // Collect the lines from last to first
            for(int i=cnt-1;i>=0;i--){
                int end = breaks[i];
                int start = prev[end];
                line_counts[i] = end - start;
                lines[i] = (char **)malloc(line_counts[i] * sizeof(char *));
                for(int j=start, k=0; j < end; j++,k++){
                    lines[i][k] = sentences[j];
                }
            }
            // Print the lines
            for(int i=0;i<cnt;i++){
                for(int j=0; j < line_counts[i]; j++){
                    printf("%s", lines[i][j]);
                    if(j != line_counts[i]-1) printf(" ");
                }
                printf("\n");
                free(lines[i]);
            }
            // Free allocated memory for lines
            free(lines);
            free(line_counts);
            free(breaks);
        }
        printf("--------------------\n");
        // Free memory
        for(int i=0;i<N;i++) {
            free(sentences[i]);
        }
        free(sentences);
        free(lengths);
        free(sum_len);
        free(sum_plus_j);
        free(dp);
        free(prev);
    }
}