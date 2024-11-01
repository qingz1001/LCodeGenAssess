#include <stdio.h>
#include <stdlib.h>

int min_steps;

// Function to find the index of x using binary search
int find_idx(int *arr, int len, int x) {
    int l = 0, r = len - 1, m;
    while(l <= r){
        m = l + (r - l)/2;
        if(arr[m] == x)
            return m;
        else if(arr[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

// Function to compute the minimum number of steps
int compute_min_steps(int l, int r, int target_idx) {
    if(l == r)
        return 0;
    int floor_mid = (l + r) / 2;
    int ceil_mid = (l + r + 1) / 2;
    int steps1, steps2;
    
    // Choice 1: floor_mid
    if(target_idx <= floor_mid)
        steps1 = 1 + compute_min_steps(l, floor_mid, target_idx);
    else
        steps1 = 1 + compute_min_steps(floor_mid + 1, r, target_idx);
    
    // Choice 2: ceil_mid
    if(target_idx <= ceil_mid)
        steps2 = 1 + compute_min_steps(l, ceil_mid, target_idx);
    else
        steps2 = 1 + compute_min_steps(ceil_mid + 1, r, target_idx);
    
    return (steps1 < steps2) ? steps1 : steps2;
}

int main(){
    int n;
    scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    int q;
    scanf("%d", &q);
    while(q--){
        int x;
        scanf("%d", &x);
        int idx = find_idx(arr, n, x);
        if(idx == -1){
            printf("0\n");
            continue;
        }
        int steps = compute_min_steps(0, n-1, idx);
        printf("%d\n", steps);
    }
    free(arr);
    return 0;
}