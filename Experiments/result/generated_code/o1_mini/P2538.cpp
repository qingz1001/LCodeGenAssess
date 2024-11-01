#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 50
#define INF 100000000000000LL

typedef unsigned long long mask_t;

// Global variables for backtracking
int n, m, k;
long long distance_matrix[MAXN][MAXN];
int existing_castles[MAXN];
int possible_castles[MAXN];
int num_possible_castles;
mask_t coverage_list_sorted[MAXN];
int sorted_indices[MAXN];
int sorted_num;
mask_t target_uncovered;
int found;

// Function to compare coverage counts for sorting
int compare(const void *a, const void *b, void *coverage) {
    int idx1 = *(const int*)a;
    int idx2 = *(const int*)b;
    mask_t *cov = (mask_t*)coverage;
    // Count bits
    int count1 = __builtin_popcountll(cov[idx1]);
    int count2 = __builtin_popcountll(cov[idx2]);
    return count2 - count1;
}

// Recursive backtracking function
void backtrack(int pos, mask_t covered, int used, mask_t *coverage_list, int num_castles, int max_k) {
    if (found) return;
    if (covered == target_uncovered) {
        found = 1;
        return;
    }
    if (used == max_k) return;
    if (pos == num_castles) return;

    // Estimate the maximum possible coverage
    // If even selecting all remaining castles cannot cover, prune
    mask_t remaining = target_uncovered & ~covered;
    int bits_left = __builtin_popcountll(remaining);
    if (bits_left ==0){
        found =1;
        return;
    }

    // Select the current castle
    backtrack(pos +1, covered | coverage_list[pos], used +1, coverage_list, num_castles, max_k);
    if (found) return;
    // Skip the current castle
    backtrack(pos +1, covered, used, coverage_list, num_castles, max_k);
}

int main(){
    // Read n, m, k
    scanf("%d %d %d", &n, &m, &k);
    int r[MAXN];
    for(int i=0;i<n;i++) scanf("%d", &r[i]);
    long long d[MAXN];
    for(int i=0;i<n;i++) scanf("%lld", &d[i]);
    // Initialize existing_castles
    memset(existing_castles, 0, sizeof(existing_castles));
    for(int i=0;i<m;i++){
        int c;
        scanf("%d", &c);
        existing_castles[c] =1;
    }
    // Initialize distance_matrix
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(i ==j) distance_matrix[i][j]=0;
            else distance_matrix[i][j]=INF;
        }
    }
    // Set roads
    for(int i=0;i<n;i++){
        int to = r[i];
        if(to !=i){
            if(d[i] < distance_matrix[i][to]){
                distance_matrix[i][to] = d[i];
                distance_matrix[to][i] = d[i];
            }
        }
    }
    // Floyd-Warshall
    for(int k_fw=0; k_fw<n; k_fw++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(distance_matrix[i][k_fw] + distance_matrix[k_fw][j] < distance_matrix[i][j]){
                    distance_matrix[i][j] = distance_matrix[i][k_fw] + distance_matrix[k_fw][j];
                }
            }
        }
    }
    // Binary search
    long long low=0, high=0;
    // Find the maximum distance in distance_matrix
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            if(distance_matrix[i][j] > high && distance_matrix[i][j] < INF){
                high = distance_matrix[i][j];
            }
        }
    }
    long long answer = high;
    while(low <= high){
        long long mid = low + (high - low)/2;
        // Compute covered mask from existing castles
        mask_t covered =0;
        for(int i=0;i<n;i++) if(existing_castles[i]){
            for(int j=0;j<n;j++) if(distance_matrix[i][j] <= mid){
                covered |= (1ULL << j);
            }
        }
        // Compute uncovered
        mask_t uncovered = ~covered & ((n >=64)? ~0: ((1ULL << n) -1));
        if(uncovered ==0){
            answer = mid;
            high = mid -1;
            continue;
        }
        // Prepare possible castles
        num_possible_castles =0;
        for(int i=0;i<n;i++) if(!existing_castles[i]){
            mask_t mask =0;
            for(int j=0;j<n;j++) if(distance_matrix[i][j] <= mid){
                mask |= (1ULL << j);
            }
            possible_castles[num_possible_castles++] =i;
        }
        // Prepare coverage list
        mask_t coverage_list[MAXN];
        for(int i=0;i<num_possible_castles;i++) coverage_list[i] =0;
        for(int i=0;i<num_possible_castles;i++) {
            int c = possible_castles[i];
            for(int j=0;j<n;j++) if(distance_matrix[c][j] <= mid){
                coverage_list[i] |= (1ULL << j);
            }
        }
        // Sort castles by coverage descending
        for(int i=0;i<num_possible_castles;i++) sorted_indices[i] =i;
        qsort_r(sorted_indices, num_possible_castles, sizeof(int), compare, coverage_list);
        mask_t sorted_coverage[MAXN];
        for(int i=0;i<num_possible_castles;i++) sorted_coverage[i] = coverage_list[sorted_indices[i]];
        // Set target_uncovered
        target_uncovered = uncovered;
        // Initialize found
        found =0;
        // Backtrack
        backtrack(0, 0, 0, sorted_coverage, num_possible_castles, k);
        if(found){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    printf("%lld\n", answer);
    return 0;
}