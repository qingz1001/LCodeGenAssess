#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum number of sticks
#define MAX_N 65

int n;
int a[MAX_N];
int bins[MAX_N];
int total_bins;
int L;

// Comparator for sorting in descending order
int cmp_desc(const void* a_, const void* b_) {
    return (*(int*)b_ - *(int*)a_);
}

// Depth-first search to try to assign sticks to bins
int dfs(int stick) {
    if (stick == n)
        return 1;
    for(int j = 0; j < total_bins; j++) {
        if (bins[j] + a[stick] > L)
            continue;
        if (j > 0 && bins[j] == bins[j-1])
            continue;
        bins[j] += a[stick];
        if (dfs(stick + 1))
            return 1;
        bins[j] -= a[stick];
        if (bins[j] == 0)
            break;
    }
    return 0;
}

int main(){
    // Read number of sticks
    scanf("%d", &n);
    // Read lengths of sticks
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    
    // Calculate total length and find the maximum stick length
    int sum = 0, max = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
        if(a[i] > max)
            max = a[i];
    }
    
    // Sort the sticks in descending order
    qsort(a, n, sizeof(int), cmp_desc);
    
    // Try all possible original lengths from max to sum
    for(L = max; L <= sum; L++){
        if(sum % L != 0)
            continue;
        total_bins = sum / L;
        memset(bins, 0, sizeof(bins));
        if(dfs(0)){
            printf("%d\n", L);
            return 0;
        }
    }
    
    return 0;
}