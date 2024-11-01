#include <stdio.h>
#include <stdlib.h>

#define MAXN 12

int C_coef[MAXN];
int path[MAXN];
int best_path[MAXN];
int found_flag = 0;
int n_global;
int target_sum;

// Function to compute binomial coefficient C(n, k)
int binomial(int n, int k){
    if(k ==0 || k ==n) return 1;
    int res =1;
    for(int i=1;i<=k;i++){
        res = res * (n - i +1) / i;
    }
    return res;
}

// Function to sort an array in descending order
void sort_desc(int *arr, int size){
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(arr[i] < arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to sort an array in ascending order
void sort_asc(int *arr, int size){
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Recursive backtrack function
void backtrack(int pos, int current_sum, int used[], int remaining_C[], int remaining_size){
    if(found_flag) return;
    if(pos == n_global){
        if(current_sum == target_sum){
            for(int i=0;i<n_global;i++) best_path[i] = path[i];
            found_flag = 1;
        }
        return;
    }
    for(int x=1; x<=n_global; x++){
        if(!used[x]){
            int new_sum = current_sum + C_coef[pos] * x;
            if(new_sum > target_sum) continue;
            used[x] = 1;
            // Prepare remaining coefficients and numbers
            int new_remaining_size = remaining_size -1;
            int temp_C[MAXN];
            int idx =0;
            for(int i=0;i<remaining_size;i++) temp_C[i] = remaining_C[i];
            // Remove C[pos] by not including it
            // Not needed as remaining_C already excludes current pos
            // Collect remaining coefficients
            int sorted_C[MAXN];
            for(int i=0;i<new_remaining_size;i++) sorted_C[i] = remaining_C[i];
            // Sort remaining coefficients descending
            sort_desc(sorted_C, new_remaining_size);
            // Collect remaining available numbers
            int available_nums[MAXN];
            int count =0;
            for(int num=1; num<=n_global; num++) if(!used[num]) available_nums[count++] = num;
            // Sort available numbers ascending
            int sorted_asc[MAXN];
            for(int i=0;i<new_remaining_size;i++) sorted_asc[i] = available_nums[i];
            sort_asc(sorted_asc, new_remaining_size);
            // Compute min_sum_remaining
            int min_sum =0;
            for(int i=0;i<new_remaining_size;i++) min_sum += sorted_C[i] * sorted_asc[i];
            // Sort available numbers descending
            int sorted_desc[MAXN];
            for(int i=0;i<new_remaining_size;i++) sorted_desc[i] = available_nums[i];
            sort_desc(sorted_desc, new_remaining_size);
            // Compute max_sum_remaining
            int max_sum =0;
            for(int i=0;i<new_remaining_size;i++) max_sum += sorted_C[i] * sorted_desc[i];
            int sum_needed = target_sum - new_sum;
            if(sum_needed >= min_sum && sum_needed <= max_sum){
                path[pos] = x;
                backtrack(pos +1, new_sum, used, remaining_C, new_remaining_size);
                if(found_flag) return;
            }
            used[x] = 0;
        }
    }
}

int main(){
    int n;
    long sum;
    if(scanf("%d %ld", &n, &sum)!=2){
        return 0;
    }
    n_global = n;
    target_sum = sum;
    // Compute coefficients
    for(int i=0;i<n;i++) C_coef[i] = binomial(n-1, i);
    // Prepare initial remaining coefficients
    int initial_remaining_C[MAXN];
    for(int i=0;i<n;i++) initial_remaining_C[i] = C_coef[i];
    // Initialize used array
    int used_nums[MAXN+1];
    for(int i=0;i<=n;i++) used_nums[i] = 0;
    // Start backtracking
    backtrack(0, 0, used_nums, initial_remaining_C, n);
    if(found_flag){
        for(int i=0;i<n;i++){
            if(i>0) printf(" ");
            printf("%d", best_path[i]);
        }
        printf("\n");
    }
    return 0;
}