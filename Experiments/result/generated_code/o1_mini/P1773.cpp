#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define INF 1000000000

int main(){
    char s[1001];
    scanf("%s", s);
    int m;
    scanf("%d", &m);
    int n = strlen(s);
    int digits[1000];
    for(int i=0;i<n;i++) digits[i] = s[i] - '0';
    
    // Initialize current and next DP arrays
    int current_dp[50][50];
    int next_dp[50][50];
    for(int p=0;p<m;p++) {
        for(int nn=0; nn<m; nn++) {
            current_dp[p][nn] = INF;
            next_dp[p][nn] = INF;
        }
    }
    
    // Initialize with first digit
    int first_n = digits[0] % m;
    int initial_p = 1 % m;
    current_dp[initial_p][first_n] = 0;
    
    // Process each digit
    for(int i=1;i<n;i++){
        // Reset next_dp
        for(int p=0;p<m;p++) {
            for(int nn=0; nn<m; nn++) {
                next_dp[p][nn] = INF;
            }
        }
        
        for(int p=0; p<m; p++) {
            for(int nn=0; nn<m; nn++) {
                if(current_dp[p][nn] < INF){
                    // Option 1: Extend the current number
                    int new_n = (nn * 10 + digits[i]) % m;
                    if(current_dp[p][nn] < next_dp[p][new_n]){
                        next_dp[p][new_n] = current_dp[p][nn];
                    }
                    
                    // Option 2: Insert a split
                    int p_new = (p * nn) % m;
                    int new_digit = digits[i] % m;
                    int k_new = current_dp[p][nn] + 1;
                    if(k_new < next_dp[p_new][new_digit]){
                        next_dp[p_new][new_digit] = k_new;
                    }
                }
            }
        }
        
        // Swap current_dp and next_dp
        for(int p=0; p<m; p++) {
            for(int nn=0; nn<m; nn++) {
                current_dp[p][nn] = next_dp[p][nn];
            }
        }
    }
    
    // Find min and max x with their minimal k
    int min_x = m, k_min = INF;
    int max_x = -1, k_max = INF;
    
    for(int p=0; p<m; p++) {
        for(int nn=0; nn<m; nn++) {
            if(current_dp[p][nn] < INF){
                int r = (p * nn) % m;
                // Update min_x and k_min
                if(r < min_x){
                    min_x = r;
                    k_min = current_dp[p][nn];
                }
                else if(r == min_x && current_dp[p][nn] < k_min){
                    k_min = current_dp[p][nn];
                }
                // Update max_x and k_max
                if(r > max_x){
                    max_x = r;
                    k_max = current_dp[p][nn];
                }
                else if(r == max_x && current_dp[p][nn] < k_max){
                    k_max = current_dp[p][nn];
                }
            }
        }
    }
    
    printf("%d %d %d %d\n", min_x, k_min, max_x, k_max);
    return 0;
}