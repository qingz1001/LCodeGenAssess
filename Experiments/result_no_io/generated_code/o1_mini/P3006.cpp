#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct {
    ll T_i;
    ll C_i;
    ll min_M_i;
} Node;

ll min_ll(ll a, ll b) {
    return a < b ? a : b;
}

int cmp_nodes(const void *a, const void *b) {
    Node *na = (Node*)a;
    Node *nb = (Node*)b;
    if (na->T_i < nb->T_i) return -1;
    if (na->T_i > nb->T_i) return 1;
    return 0;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    
    // Allocate memory
    ll *C = (ll*)calloc(N+1, sizeof(ll));
    ll *M = (ll*)calloc(N+1, sizeof(ll));
    ll *parent = (ll*)calloc(N+1, sizeof(ll));
    ll *min_M = (ll*)calloc(N+1, sizeof(ll));
    
    // For building children list
    int *children_cnt = (int*)calloc(N+1, sizeof(int));
    
    // First pass: read P_i, C_i, M_i and count children
    for(int i=2;i<=N;i++){
        ll P_i;
        scanf("%lld %lld %lld", &P_i, &C[i], &M[i]);
        parent[i] = P_i;
        children_cnt[P_i]++;
    }
    
    // Compute children_start
    ll *children = (ll*)malloc((N-1) * sizeof(ll));
    int *children_start = (int*)calloc(N+1, sizeof(int));
    children_start[1] = 0;
    for(int i=2;i<=N;i++){
        children_start[i] = children_start[i-1] + children_cnt[i-1];
    }
    
    // Reset children_cnt for assignment
    for(int i=1;i<=N;i++) children_cnt[i]=0;
    
    // Second pass: assign children
    for(int i=2;i<=N;i++){
        ll P_i = parent[i];
        children[children_start[P_i] + children_cnt[P_i]] = i;
        children_cnt[P_i]++;
    }
    
    // BFS to compute min_M
    // Initialize
    for(int i=1;i<=N;i++) min_M[i] = 0;
    min_M[1] = 1000000000000000000LL; // INF
    // Initialize queue
    ll *queue = (ll*)malloc(N * sizeof(ll));
    int front=0, rear=0;
    queue[rear++] = 1;
    
    while(front < rear){
        ll current = queue[front++];
        for(int j=children_start[current]; j<children_start[current] + children_cnt[current]; j++){
            ll child = children[j];
            if(M[child] ==0){
                min_M[child] =0;
            }
            else{
                min_M[child] = min_ll(min_M[current], M[child]);
            }
            queue[rear++] = child;
        }
    }
    
    // Prepare nodes array
    Node *nodes = (Node*)malloc(N * sizeof(Node));
    for(int i=1;i<=N;i++){
        if(i ==1){
            nodes[i-1].C_i =0;
            nodes[i-1].min_M_i =1000000000000000000LL;
            nodes[i-1].T_i =0;
        }
        else{
            nodes[i-1].C_i = C[i];
            nodes[i-1].min_M_i = min_M[i];
            if(nodes[i-1].min_M_i >0){
                if(nodes[i-1].C_i % nodes[i-1].min_M_i ==0)
                    nodes[i-1].T_i = nodes[i-1].C_i / nodes[i-1].min_M_i;
                else
                    nodes[i-1].T_i = nodes[i-1].C_i / nodes[i-1].min_M_i +1;
            }
            else{
                nodes[i-1].T_i = 2000000000000000000LL;
            }
        }
    }
    
    // Sort nodes by T_i ascending
    qsort(nodes, N, sizeof(Node), cmp_nodes);
    
    // Compute prefix sums
    ll *prefix_C = (ll*)calloc(N+1, sizeof(ll));
    ll *prefix_sum_min_M = (ll*)calloc(N+1, sizeof(ll));
    for(int i=1;i<=N;i++){
        prefix_C[i] = prefix_C[i-1] + nodes[i-1].C_i;
        prefix_sum_min_M[i] = prefix_sum_min_M[i-1] + nodes[i-1].min_M_i;
    }
    ll total_min_M = prefix_sum_min_M[N];
    
    // Process queries
    for(int q=0; q<K; q++){
        ll T;
        scanf("%lld", &T);
        // Binary search for k
        int left=0, right=N;
        while(left < right){
            int mid = left + (right - left)/2;
            if(nodes[mid].T_i <= T){
                left = mid +1;
            }
            else{
                right = mid;
            }
        }
        int k = left;
        ll sum_C = prefix_C[k];
        ll sum_min_M = total_min_M - prefix_sum_min_M[k];
        ll total = sum_C + T * sum_min_M;
        printf("%lld\n", total);
    }
    
    // Free memory
    free(C);
    free(M);
    free(parent);
    free(min_M);
    free(children_cnt);
    free(children_start);
    free(children);
    free(queue);
    free(nodes);
    free(prefix_C);
    free(prefix_sum_min_M);
    
    return 0;
}