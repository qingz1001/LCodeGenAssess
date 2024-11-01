#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int p1[n+1], p2[n+1], pos[n+1];
    
    // Read the permutations
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p1[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p2[i]);
    }
    
    // Find the position of each element in the second permutation
    for (int i = 1; i <= n; i++) {
        pos[p2[i]] = i;
    }
    
    int lis[n+1];
    int len = 0;
    
    // Compute the LIS using the position array
    for (int i = 1; i <= n; i++) {
        int j = pos[p1[i]];
        if (j > lis[len]) {
            lis[++len] = j;
        } else {
            int *k = lower_bound(lis + 1, lis + len + 1, j);
            *k = j;
        }
    }
    
    // Output the length of the LIS
    printf("%d\n", len);
    
    return 0;
}