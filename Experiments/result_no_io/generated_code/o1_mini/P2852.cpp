#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAXN 20005

int N, K;
int S[MAXN];
int SA[MAXN], rank_arr[MAXN], tmp_rank[MAXN];
int LCP[MAXN];
int rank_inv[MAXN];

// Comparator for the doubling algorithm
int cmp(int a, int b, int k) {
    if (rank_arr[a] != rank_arr[b])
        return rank_arr[a] - rank_arr[b];
    int rank_a = (a + k < N) ? rank_arr[a + k] : -1;
    int rank_b = (b + k < N) ? rank_arr[b + k] : -1;
    return rank_a - rank_b;
}

int main(){
    // Read N and K
    scanf("%d %d", &N, &K);
    for(int i=0;i<N;i++) scanf("%d", &S[i]);
    
    // Initialize SA and rank_arr
    for(int i=0;i<N;i++){
        SA[i] = i;
        rank_arr[i] = S[i];
    }
    
    // Prefix-doubling algorithm
    for(int k=1; k< N; k <<=1){
        // Sort SA based on rank and rank at k distance
        // Simple comparator with qsort
        qsort(SA, N, sizeof(int), (int (*)(const void*, const void*))cmp);
        
        // Temporary ranks
        tmp_rank[SA[0]] = 0;
        for(int i=1;i<N;i++){
            tmp_rank[SA[i]] = tmp_rank[SA[i-1]];
            if(cmp(SA[i-1], SA[i], k) < 0){
                tmp_rank[SA[i]]++;
            }
        }
        for(int i=0;i<N;i++) rank_arr[i] = tmp_rank[i];
        // Check if all ranks are unique
        int unique = 1;
        for(int i=1;i<N;i++) if(rank_arr[SA[i]] != rank_arr[SA[i-1]]) {unique=0; break;}
        if(unique) break;
    }
    
    // Build rank_inv
    for(int i=0;i<N;i++) rank_inv[SA[i]] = i;
    
    // Kasai's algorithm for LCP
    int k_lcp =0;
    for(int i=0;i<N;i++){
        if(rank_inv[i]==0){k_lcp=0; continue;}
        int j = SA[rank_inv[i]-1];
        while(i + k_lcp < N && j + k_lcp < N && S[i + k_lcp] == S[j + k_lcp]) k_lcp++;
        LCP[rank_inv[i]] = k_lcp;
        if(k_lcp >0) k_lcp--;
    }
    
    // Sliding window minimum with deque
    int deque[MAXN];
    int front=0, back=0;
    int max_len=0;
    for(int i=1;i<N;i++){
        // Remove from back while current LCP is <= last in deque
        while(back > front && LCP[i] <= LCP[deque[back-1]]) back--;
        deque[back++] = i;
        
        // Remove from front if out of window
        while(front < back && deque[front] <= i - (K-1)) front++;
        
        // If we have at least K-1 in the window
        if(i >= K-1){
            if(front < back){
                if(LCP[deque[front]] > max_len) max_len = LCP[deque[front]];
            }
        }
    }
    
    printf("%d\n", max_len);
    return 0;
}