#include <stdio.h>
#include <stdlib.h>

long long global_min = 1000000000;
long long global_max = -1;

int n, m;
int list_original[50];
int line[50];
long prefix_sum[51];

void recurse(int seg, int pos, long product, int total_segments, int n_segments, int m_segments, int *current_min, int *current_max) {
    if (seg == m_segments) {
        long sum = prefix_sum[n_segments] - prefix_sum[pos];
        int s_mod = ((sum % 10) + 10) % 10;
        long final_product = product * s_mod;
        if (final_product < *current_min) *current_min = final_product;
        if (final_product > *current_max) *current_max = final_product;
        return;
    }
    for(int next_pos = pos + 1; next_pos <= n_segments - (m_segments - seg); next_pos++) {
        long sum = prefix_sum[next_pos] - prefix_sum[pos];
        int s_mod = ((sum % 10) + 10) % 10;
        long new_product;
        if(seg ==1){
            new_product = s_mod;
        }
        else{
            new_product = product * s_mod;
        }
        recurse(seg +1, next_pos, new_product, total_segments, n_segments, m_segments, current_min, current_max);
    }
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i=0;i<n;i++) scanf("%d", &list_original[i]);
    for(int start=0; start<n; start++){
        // Build linear list
        for(int i=0;i<n;i++) line[i] = list_original[(start + i)%n];
        // Compute prefix sums
        prefix_sum[0] =0;
        for(int i=1;i<=n;i++) prefix_sum[i] = prefix_sum[i-1] + line[i-1];
        // Initialize current min and max
        int current_min = 1000000000;
        int current_max = -1;
        // Start recursion
        recurse(1, 0, 0, m, n, m, &current_min, &current_max);
        if(current_min < global_min) global_min = current_min;
        if(current_max > global_max) global_max = current_max;
    }
    printf("%lld\n%lld\n", global_min, global_max);
    return 0;
}