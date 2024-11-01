#include <stdio.h>
#include <math.h>
#include <string.h>

long long dp_cache[11][1002];
int m_global, n_global;

// Recursive function to count the number of ways
long long count_ways(int k, int c, int m) {
    if (k == m + 1) {
        return (c >= n_global) ? 1 : 0;
    }
    if (dp_cache[k][c] != -1) {
        return dp_cache[k][c];
    }
    long long ways = 0;
    int start = (k == 1) ? 1 : (c == 0 ? 1 : (1));
    int lower = (k == 1) ? 1 : 0;
    int previous = (k == 1) ? 0 : 1;
    // The next number should be greater than the previous number
    // and less than or equal to c + 1
    int min_s = (k == 1) ? 1 : 1;
    int max_s = c + 1;
    for(int s = (k == 1) ? 1 : 1; s <= max_s; s++) {
        if(k ==1 || s > (c - s)) { // Ensure increasing
            ways += count_ways(k + 1, c + s, m);
        }
    }
    dp_cache[k][c] = ways;
    return ways;
}

int main(){
    int n;
    scanf("%d", &n);
    n_global = n;
    // Calculate m = ceil(log2(n + 1))
    double log_val = log2((double)(n + 1));
    int m = ceil(log_val);
    m_global = m;
    memset(dp_cache, -1, sizeof(dp_cache));
    // Initialize coverage to 0 and step to 1
    // Start with k=1 and c=0
    // First number must be 1
    // So s1=1, c=1
    // Then count ways for k=2 to m
    // Modify the count_ways function to enforce s1=1
    // Reset dp_cache
    memset(dp_cache, -1, sizeof(dp_cache));
    // Set first number to 1
    int initial_k = 2;
    int initial_c = 1;
    // Now count ways from k=2 with c=1
    // But need to handle m=1 case
    long long total_ways;
    if(m ==1){
        total_ways = (1 >= n) ? 1 : 0;
    }
    else{
        total_ways = 0;
        // Choose s2 from 2 to c+1=2
        for(int s2 = 2; s2 <= initial_c +1; s2++){
            total_ways += count_ways(initial_k, initial_c + s2, m);
        }
    }
    printf("%d %lld\n", m, total_ways);
    return 0;
}