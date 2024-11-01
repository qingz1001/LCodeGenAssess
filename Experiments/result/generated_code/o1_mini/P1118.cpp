#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 12

long long C[MAX_N+1][MAX_N+1];
int n;
long long target_sum;
long long coeff[MAX_N];
int result[MAX_N];
bool used[13];
bool found = false;

// Function to compute binomial coefficients
void compute_binomial() {
    for(int i=0;i<=MAX_N;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}

// Function to compute coefficients
void compute_coefficients(int size){
    for(int i=0;i<size;i++){
        coeff[i] = C[size-1][i];
    }
}

// Function to compute min possible sum from remaining positions
long long min_possible(int pos, int available_numbers[]) {
    long long min_sum = 0;
    for(int i=pos;i<n;i++){
        min_sum += coeff[i] * available_numbers[i-pos];
    }
    return min_sum;
}

// Function to compute max possible sum from remaining positions
long long max_possible(int pos, int available_numbers[]) {
    long long max_sum = 0;
    for(int i=pos;i<n;i++){
        max_sum += coeff[i] * available_numbers[n-pos-1 - (i-pos)];
    }
    return max_sum;
}

// Backtracking function
void backtrack(int pos, long long current_sum, int perm[], int available[], int avail_size) {
    if(found) return;
    if(pos == n){
        if(current_sum == target_sum){
            for(int i=0;i<n;i++) {
                printf("%d%c", perm[i], i<n-1?' ':'\n');
            }
            found = true;
        }
        return;
    }
    // Iterate through available numbers in increasing order
    for(int i=0;i<avail_size;i++){
        int num = available[i];
        long long new_sum = current_sum + coeff[pos] * num;
        // Prepare new available list
        int new_available[MAX_N];
        int new_size = 0;
        for(int j=0;j<avail_size;j++) {
            if(j != i) new_available[new_size++] = available[j];
        }
        // Compute min and max possible
        // Min: assign smallest remaining numbers to smallest coefficients
        // Max: assign largest remaining numbers to largest coefficients
        long long rem_min = 0, rem_max = 0;
        if(pos+1 < n){
            // Prepare sorted remaining numbers
            int sorted_min[MAX_N], sorted_max[MAX_N];
            for(int j=0;j<new_size;j++) sorted_min[j] = sorted_max[j] = new_available[j];
            // Sort for min
            for(int j=0;j<new_size-1;j++) {
                for(int k=j+1;k<new_size;k++) {
                    if(sorted_min[j] > sorted_min[k]){
                        int tmp = sorted_min[j];
                        sorted_min[j] = sorted_min[k];
                        sorted_min[k] = tmp;
                    }
                }
            }
            // Sort for max
            for(int j=0;j<new_size-1;j++) {
                for(int k=j+1;k<new_size;k++) {
                    if(sorted_max[j] < sorted_max[k]){
                        int tmp = sorted_max[j];
                        sorted_max[j] = sorted_max[k];
                        sorted_max[k] = tmp;
                    }
                }
            }
            // Compute rem_min and rem_max
            for(int j=pos+1;j<n;j++){
                rem_min += coeff[j] * sorted_min[j-pos-1];
                rem_max += coeff[j] * sorted_max[j-pos-1];
            }
        }
        if(new_sum + rem_min > target_sum) continue;
        if(new_sum + rem_max < target_sum) continue;
        // Assign num to perm[pos]
        perm[pos] = num;
        backtrack(pos+1, new_sum, perm, new_available, new_size);
        if(found) return;
    }
}

int main(){
    compute_binomial();
    if(scanf("%d %lld", &n, &target_sum)!=2){
        return 0;
    }
    compute_coefficients(n);
    // Initialize available numbers
    int available[MAX_N];
    for(int i=0;i<n;i++) available[i] = i+1;
    backtrack(0, 0, result, available, n);
    return 0;
}