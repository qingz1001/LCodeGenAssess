#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 10
#define MAX_DENOM 10000000

typedef struct {
    int denominators[MAX_DEPTH];
    int size;
    int max_denominator;
} Solution;

int a_input, b_input;
Solution best_solution;
int best_found = 0;

// Function to compute GCD
int gcd(int a, int b){
    while(b !=0){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Function to compare and update the best solution
void update_best(int list[], int size, int current_max){
    if(!best_found || size < best_solution.size || (size == best_solution.size && current_max < best_solution.max_denominator)){
        best_solution.size = size;
        best_solution.max_denominator = current_max;
        for(int i=0;i<size;i++) best_solution.denominators[i] = list[i];
        best_found = 1;
    }
}

// Backtracking function
void backtrack(int remaining_a, int remaining_b, int list[], int size, int start){
    if(remaining_a ==0){
        // Found a solution
        int current_max = list[size-1];
        update_best(list, size, current_max);
        return;
    }
    if(size >= best_solution.size && best_found) return;
    if(size >= MAX_DEPTH) return;
    // Starting denominator
    int n_start = (remaining_b + remaining_a -1)/remaining_a;
    for(int n = n_start; n <= MAX_DENOM; n++){
        // Compute new fraction: remaining_a/remaining_b -1/n = (remaining_a*n - remaining_b)/ (remaining_b*n)
        int new_num = remaining_a * n - remaining_b;
        if(new_num <0) continue;
        int new_den = remaining_b * n;
        if(new_den ==0) continue;
        // Reduce the fraction
        int g = gcd(new_num, new_den);
        new_num /= g;
        new_den /= g;
        list[size] = n;
        backtrack(new_num, new_den, list, size+1, n+1);
    }
}

int main(){
    scanf("%d %d", &a_input, &b_input);
    int current_list[MAX_DEPTH];
    backtrack(a_input, b_input, current_list, 0, 1);
    for(int i=0;i<best_solution.size;i++){
        printf("%d%c", best_solution.denominators[i], i < best_solution.size-1 ? ' ' : '\n');
    }
    return 0;
}