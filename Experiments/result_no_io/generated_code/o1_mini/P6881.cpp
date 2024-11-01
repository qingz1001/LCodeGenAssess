#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define a structure for queries
typedef struct {
    int t;
    int l;
    int r;
    int idx;
} Query;

// Comparator for sorting queries by t
int cmp(const void* a, const void* b){
    Query* qa = (Query*)a;
    Query* qb = (Query*)b;
    if(qa->t != qb->t){
        return qa->t - qb->t;
    }
    return qa->idx - qb->idx;
}

int main(){
    int N, Q;
    scanf("%d %d", &N, &Q);
    int* S = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &S[i]);
    
    Query* queries = (Query*)malloc(Q * sizeof(Query));
    for(int i=0;i<Q;i++){
        scanf("%d %d %d", &queries[i].t, &queries[i].l, &queries[i].r);
        queries[i].idx = i;
    }
    
    // Sort queries by t
    qsort(queries, Q, sizeof(Query), cmp);
    
    long long* answers = (long long*)malloc(Q * sizeof(long long));
    
    // Initialize variables
    int current_t = 1;
    // To store prefix sums for the current t
    long long* prefix = (long long*)malloc((N+1) * sizeof(long long));
    
    // Initialize deque
    int* dq = (int*)malloc((N+1) * sizeof(int));
    int front = 0, back = 0;
    
    int q_idx = 0;
    while(q_idx < Q){
        int t = queries[q_idx].t;
        // Reset deque
        front = back = 0;
        // Compute sliding window max for current t
        for(int i=1;i<=N;i++){
            // Remove elements from the back smaller than current
            while(back > front && S[dq[back-1]] <= S[i]) back--;
            dq[back++] = i;
            // Remove elements from the front out of the window
            while(front < back && dq[front] < i - t +1) front++;
            // Set prefix sum
            if(i ==1) prefix[i] = S[dq[front]];
            else prefix[i] = prefix[i-1] + S[dq[front]];
        }
        // Process all queries with this t
        while(q_idx < Q && queries[q_idx].t == t){
            int l = queries[q_idx].l;
            int r = queries[q_idx].r;
            if(l > r){
                answers[queries[q_idx].idx] = 0;
            }
            else{
                if(l-1 >=0){
                    answers[queries[q_idx].idx] = prefix[r] - prefix[l-1];
                }
                else{
                    answers[queries[q_idx].idx] = prefix[r];
                }
            }
            q_idx++;
        }
    }
    
    // Output answers in original order
    for(int i=0;i<Q;i++) printf("%lld\n", answers[i]);
    
    // Free memory
    free(S);
    free(queries);
    free(answers);
    free(prefix);
    free(dq);
    
    return 0;
}