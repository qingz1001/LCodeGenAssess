#include <stdio.h>
#include <stdlib.h>

// Function to swap two integers
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to reverse a segment of the array from start to end indices
void reverse_segment(int arr[], int start, int end){
    while(start < end){
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// Function to perform one next permutation step
int next_permutation_step(int arr[], int N){
    int i = N - 2;
    // Step 1: Find the largest index i such that arr[i] < arr[i+1]
    while(i >= 0 && arr[i] >= arr[i+1]){
        i--;
    }
    if(i < 0){
        return 0; // No next permutation
    }
    // Step 2: Find the largest index j > i such that arr[j] > arr[i]
    int j = N - 1;
    while(arr[j] <= arr[i]){
        j--;
    }
    // Step 3: Swap arr[i] and arr[j]
    swap(&arr[i], &arr[j]);
    // Step 4: Reverse the suffix starting at i+1
    reverse_segment(arr, i+1, N-1);
    return 1;
}

int main(){
    int N, M;
    // Read N
    if(scanf("%d", &N)!=1){
        return 1;
    }
    // Read M
    if(scanf("%d", &M)!=1){
        return 1;
    }
    // Allocate array
    int *p = (int*)malloc(sizeof(int)*N);
    if(p == NULL){
        return 1;
    }
    // Read permutation
    for(int i=0;i<N;i++){
        if(scanf("%d", &p[i])!=1){
            free(p);
            return 1;
        }
    }
    // Perform M next permutations
    for(int m=0; m<M; m++){
        if(!next_permutation_step(p, N)){
            // As per problem statement, this should not happen
            break;
        }
    }
    // Output the resulting permutation
    if(N > 0){
        printf("%d", p[0]);
        for(int i=1;i<N;i++){
            printf(" %d", p[i]);
        }
    }
    printf("\n");
    // Free memory
    free(p);
    return 0;
}