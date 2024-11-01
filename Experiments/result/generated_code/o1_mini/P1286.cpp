#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 9
#define MAX_SUMS 36
#define MAX_LINE 500

int cmp_int(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// Function to remove a sum from the sum list
int remove_sum(int *sums, int *used, int sum_count, int target){
    for(int i=0;i<sum_count;i++){
        if(!used[i] && sums[i] == target){
            used[i] = 1;
            return 1;
        }
    }
    return 0;
}

// Recursive backtracking function
int backtrack(int n, int *sums, int sum_count, int *used, int *numbers, int num_size, int solution[]){
    if(num_size == n){
        for(int i=0;i<sum_count;i++) if(!used[i]) return 0;
        for(int i=0;i<n;i++) solution[i] = numbers[i];
        return 1;
    }
    if(num_size == 0){
        // Try all possible a0
        for(int i=0;i<sum_count;i++){
            if(used[i]) continue;
            used[i] = 1;
            numbers[num_size++] = 0;
            if(backtrack(n, sums, sum_count, used, numbers, num_size, solution)) return 1;
            used[i] = 0;
            num_size--;
        }
        return 0;
    }
    if(num_size ==1){
        // Assign a1 based on first sum
        for(int i=0;i<sum_count;i++){
            if(used[i]) continue;
            used[i] = 1;
            numbers[num_size++] = sums[i];
            if(backtrack(n, sums, sum_count, used, numbers, num_size, solution)) return 1;
            used[i] = 0;
            num_size--;
        }
        return 0;
    }
    // Assign next number based on the smallest unused sum
    int next_sum = -1;
    for(int i=0;i<sum_count;i++) if(!used[i]){
        next_sum = sums[i];
        break;
    }
    if(next_sum == -1) return 0;
    for(int i=0;i<sum_count;i++) if(!used[i] && sums[i] == next_sum){
        // Assume current number is sums[i] - numbers[0]
        int candidate = sums[i] - numbers[0];
        if(candidate < numbers[num_size-1]) continue;
        // Check if all a_j + candidate are in sums
        int valid = 1;
        int temp_used[MAX_SUMS];
        memcpy(temp_used, used, sizeof(int)*MAX_SUMS);
        for(int j=0;j<num_size;j++){
            int required = numbers[j] + candidate;
            if(!remove_sum(sums, temp_used, sum_count, required)){
                valid = 0;
                break;
            }
        }
        if(valid){
            // Assign candidate
            memcpy(used, temp_used, sizeof(int)*MAX_SUMS);
            numbers[num_size++] = candidate;
            if(backtrack(n, sums, sum_count, used, numbers, num_size, solution)) return 1;
            // Backtrack
            num_size--;
            memcpy(used, temp_used, sizeof(int)*MAX_SUMS);
            for(int j=0;j<num_size;j++){}
        }
    }
    return 0;
}

int main(){
    char line[MAX_LINE];
    while(fgets(line, sizeof(line), stdin)){
        int n;
        int sums[MAX_SUMS];
        int count =0;
        char *token = strtok(line, " \n");
        if(token == NULL) continue;
        n = atoi(token);
        while((token = strtok(NULL, " \n")) != NULL && count < MAX_SUMS){
            sums[count++] = atoi(token);
        }
        if(count != (n*(n-1))/2){
            printf("Impossible\n");
            continue;
        }
        qsort(sums, count, sizeof(int), cmp_int);
        int used[MAX_SUMS];
        memset(used, 0, sizeof(used));
        int numbers[MAX_N];
        int solution[MAX_N];
        if(backtrack(n, sums, count, used, numbers, 0, solution)){
            // Sort the solution
            qsort(solution, n, sizeof(int), cmp_int);
            for(int i=0;i<n;i++) printf("%d%c", solution[i], (i<n-1)?' ':'\n');
        }
        else{
            printf("Impossible\n");
        }
    }
    return 0;
}