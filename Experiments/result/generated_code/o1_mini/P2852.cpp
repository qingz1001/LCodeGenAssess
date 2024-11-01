#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 20000

int A[MAX_N];
int SA_array[MAX_N];
int rank_[MAX_N];
int tmp_rank_[MAX_N];
int LCP_array[MAX_N];
int N, K;

// Function to perform counting sort based on key
void counting_sort(int *SA, int *rank_, int step, int N, int *sorted) {
    int max_rank = 0;
    for(int i=0;i<N;i++) {
        int key = (SA[i] + step < N) ? rank_[SA[i] + step] + 1 : 0;
        if(key > max_rank) max_rank = key;
    }
    int *count = (int*)calloc(max_rank + 2, sizeof(int));
    for(int i=0;i<N;i++) {
        int key = (SA[i] + step < N) ? rank_[SA[i] + step] + 1 : 0;
        count[key]++;
    }
    for(int i=1;i<=max_rank+1;i++) {
        count[i] += count[i-1];
    }
    for(int i=N-1;i>=0;i--){
        int key = (SA[i] + step < N) ? rank_[SA[i] + step] + 1 : 0;
        sorted[--count[key]] = SA[i];
    }
    free(count);
}

int main(){
    scanf("%d %d", &N, &K);
    for(int i=0;i<N;i++) scanf("%d", &A[i]);

    // Initialize SA and rank
    for(int i=0;i<N;i++){
        SA_array[i] = i;
        rank_[i] = A[i];
    }

    int *sorted = (int*)malloc(N * sizeof(int));
    for(int step=1; step< N; step <<=1){
        // Sort by second key
        counting_sort(SA_array, rank_, step, N, sorted);
        // Sort by first key
        counting_sort(sorted, rank_, 0, N, SA_array);
        // Assign tmp_rank
        tmp_rank_[SA_array[0]] = 0;
        for(int i=1;i<N;i++){
            int prev = SA_array[i-1];
            int curr = SA_array[i];
            int rank_prev_second = (prev + step < N) ? rank_[prev + step] : -1;
            int rank_curr_second = (curr + step < N) ? rank_[curr + step] : -1;
            if(rank_[prev] != rank_[curr] || rank_prev_second != rank_curr_second){
                tmp_rank_[curr] = tmp_rank_[prev] +1;
            }
            else{
                tmp_rank_[curr] = tmp_rank_[prev];
            }
        }
        // Update rank
        for(int i=0;i<N;i++) rank_[i] = tmp_rank_[i];
        // Check if all ranks are unique
        int unique = 1;
        for(int i=1;i<N;i++) if(rank_[SA_array[i]] != rank_[SA_array[i-1]]) { unique=0; break;}
        if(unique) break;
    }
    free(sorted);

    // Build LCP array using Kasai
    int *pos = (int*)malloc(N * sizeof(int));
    for(int i=0;i<N;i++) pos[SA_array[i]] = i;
    int k =0;
    for(int i=0;i<N;i++){
        if(pos[i]==0){
            LCP_array[0] =0;
            continue;
        }
        int j = SA_array[pos[i]-1];
        while(i + k < N && j + k < N && A[i +k] == A[j +k]) k++;
        LCP_array[pos[i]] = k;
        if(k>0) k--;
    }
    free(pos);

    // Sliding window minimum for LCP
    // Window size K-1
    if(K ==1){
        printf("%d\n", N);
        return 0;
    }
    int max_L =0;
    int *deque = (int*)malloc(N * sizeof(int));
    int front =0, back=0;
    for(int i=1;i<N;i++){
        while(front < back && LCP_array[i] <= LCP_array[deque[back-1]]) back--;
        deque[back++] = i;
        while(front < back && deque[front] <= i - (K-1)) front++;
        if(i >= K){
            if(front < back){
                int current_min = LCP_array[deque[front]];
                if(current_min > max_L) max_L = current_min;
            }
        }
        if(i >= K-1){
            if(i >= K-1){
                if(i - (K-1) >=1){
                    int window_start = i - (K-1) +1;
                    if(front < back && deque[front] < window_start){
                        front++;
                    }
                }
                if(front < back){
                    int current_min = LCP_array[deque[front]];
                    if(current_min > max_L) max_L = current_min;
                }
            }
        }
    }
    // Alternatively, use sliding window correctly
    front =0; back=0;
    for(int i=1;i<N;i++){
        while(front < back && LCP_array[i] <= LCP_array[deque[back-1]]) back--;
        deque[back++] = i;
        while(front < back && deque[front] < i - (K-1) +1) front++;
        if(i >= K){
            if(front < back){
                int current_min = LCP_array[deque[front]];
                if(current_min > max_L) max_L = current_min;
            }
        }
    }

    // Alternatively, iterate with proper window
    // Reset and do again
    front =0; back=0; max_L=0;
    for(int i=1;i<N;i++){
        while(front < back && LCP_array[i] <= LCP_array[deque[back-1]]) back--;
        deque[back++] = i;
        while(front < back && deque[front] < i - (K-1) +1) front++;
        if(i >= K){
            if(front < back){
                int current_min = LCP_array[deque[front]];
                if(current_min > max_L) max_L = current_min;
            }
        }
    }

    // To ensure correctness, use a simple sliding window minimum
    front =0; back=0; max_L=0;
    for(int i=1;i<N;i++){
        while(front < back && LCP_array[i] <= LCP_array[deque[back-1]]) back--;
        deque[back++] = i;
        while(front < back && deque[front] < i - (K-1) +1) front++;
        if(i >= K){
            if(front < back){
                int current_min = LCP_array[deque[front]];
                if(current_min > max_L) max_L = current_min;
            }
        }
    }

    printf("%d\n", max_L);

    free(deque);
    return 0;
}