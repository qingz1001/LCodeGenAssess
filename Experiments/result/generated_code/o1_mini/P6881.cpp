#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Structure to hold queries
typedef struct {
    int T;
    int L;
    int R;
    int idx;
} Query;

// Comparator for sorting queries by T
int cmp_query(const void* a, const void* b){
    Query* qa = (Query*)a;
    Query* qb = (Query*)b;
    if(qa->T != qb->T) return qa->T - qb->T;
    return qa->idx - qb->idx;
}

int main(){
    ios:
    int N, Q;
    scanf("%d %d", &N, &Q);
    long long *S = (long long*)malloc((N+1)*sizeof(long long));
    for(int i=1;i<=N;i++) scanf("%lld", &S[i]);
    
    Query *queries = (Query*)malloc(Q * sizeof(Query));
    for(int i=0;i<Q;i++){
        scanf("%d %d %d", &queries[i].T, &queries[i].L, &queries[i].R);
        queries[i].idx = i;
    }
    
    // Sort queries by T
    qsort(queries, Q, sizeof(Query), cmp_query);
    
    // Prepare to store answers
    long long *ans = (long long*)malloc(Q * sizeof(long long));
    
    // Initialize deque
    int *deque = (int*)malloc((N+1)*sizeof(int));
    int head = 0, tail = -1;
    
    // Initialize prefix sum array
    long long *prefix = (long long*)malloc((N+1)*sizeof(long long));
    
    int current_T = 0;
    int q_ptr = 0;
    
    for(int t=1;t<=N;t++){
        // Update deque for sliding window
        // Remove elements out of window
        while(head <= tail && deque[head] < t -1){
            head++;
        }
        // Remove smaller elements from tail
        while(head <= tail && S[deque[tail]] <= S[t]){
            tail--;
        }
        // Add current element
        tail++;
        deque[tail] = t;
        
        // Update prefix sum
        prefix[t] = prefix[t-1] + S[deque[head]];
        
        // Answer all queries with T = t
        while(q_ptr < Q && queries[q_ptr].T == t){
            int L = queries[q_ptr].L;
            int R = queries[q_ptr].R;
            if(R > N) R = N;
            if(L > N) { ans[queries[q_ptr].idx] = 0; }
            else{
                if(L < 1) L = 1;
                ans[queries[q_ptr].idx] = prefix[R] - prefix[L-1];
            }
            q_ptr++;
        }
    }
    
    // For queries with T > N
    while(q_ptr < Q){
        int L = queries[q_ptr].L;
        int R = queries[q_ptr].R;
        if(R > N) R = N;
        if(L > N) { ans[queries[q_ptr].idx] = 0; }
        else{
            if(L < 1) L = 1;
            // Max in [1, k] is prefix_max[k]
            // Compute prefix_max
            long long *prefix_max = (long long*)malloc((N+1)*sizeof(long long));
            prefix_max[0] = 0;
            for(int i=1;i<=N;i++) prefix_max[i] = (prefix_max[i-1] > S[i]) ? prefix_max[i-1] : S[i];
            long long sum = 0;
            for(int i=L;i<=R;i++) sum += prefix_max[i];
            ans[queries[q_ptr].idx] = sum;
            free(prefix_max);
        }
        q_ptr++;
    }
    
    // Print answers in original order
    long long *final_ans = (long long*)malloc(Q * sizeof(long long));
    for(int i=0;i<Q;i++) final_ans[queries[i].idx] = ans[i];
    for(int i=0;i<Q;i++) printf("%lld\n", final_ans[i]);
    
    // Free memory
    free(S);
    free(queries);
    free(ans);
    free(deque);
    free(prefix);
    free(final_ans);
    return 0;
}