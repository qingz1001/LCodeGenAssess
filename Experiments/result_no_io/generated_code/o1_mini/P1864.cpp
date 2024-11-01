#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 71
#define INF 100000000000LL

typedef struct {
    int data;
    int weight;
    int freq;
} Node;

long long memo_table[MAX][MAX][MAX];
char computed_table[MAX][MAX][MAX];
Node nodes_sorted[MAX];
int min_weight_node_table[MAX][MAX];
int N;
long long K;

// Comparator for sorting nodes by data value
int cmp(const void *a, const void *b) {
    Node *na = (Node *)a;
    Node *nb = (Node *)b;
    if (na->data != nb->data)
        return na->data - nb->data;
    return na->weight - nb->weight;
}

long long solve(int i, int j, int d) {
    if (i > j)
        return 0;
    if (computed_table[i][j][d])
        return memo_table[i][j][d];
    computed_table[i][j][d] = 1;
    long long res = INF;
    // Option 1: choose the min weight node without modification
    int k_min = min_weight_node_table[i][j];
    long long cost1 = (long long)nodes_sorted[k_min].freq * d;
    cost1 += solve(i, k_min - 1, d + 1);
    cost1 += solve(k_min + 1, j, d + 1);
    if (cost1 < res)
        res = cost1;
    // Option 2: choose any other node and modify its weight
    for(int k = i; k <= j; k++) {
        if(k == k_min)
            continue;
        long long cost2 = (long long)nodes_sorted[k].freq * d + K;
        cost2 += solve(i, k - 1, d + 1);
        cost2 += solve(k + 1, j, d + 1);
        if(cost2 < res)
            res = cost2;
    }
    memo_table[i][j][d] = res;
    return res;
}

int main(){
    scanf("%d %lld", &N, &K);
    int data_input[MAX];
    for(int i=1;i<=N;i++) scanf("%d", &data_input[i]);
    int weight_input[MAX];
    for(int i=1;i<=N;i++) scanf("%d", &weight_input[i]);
    int freq_input[MAX];
    for(int i=1;i<=N;i++) scanf("%d", &freq_input[i]);
    // Initialize nodes_sorted
    for(int i=1;i<=N;i++){
        nodes_sorted[i].data = data_input[i];
        nodes_sorted[i].weight = weight_input[i];
        nodes_sorted[i].freq = freq_input[i];
    }
    // Sort nodes by data
    qsort(&nodes_sorted[1], N, sizeof(Node), cmp);
    // Precompute min_weight_node_table
    for(int i=1;i<=N;i++){
        for(int j=i;j<=N;j++){
            int k_min = i;
            int min_w = nodes_sorted[i].weight;
            for(int k=i+1;k<=j;k++){
                if(nodes_sorted[k].weight < min_w){
                    min_w = nodes_sorted[k].weight;
                    k_min = k;
                }
            }
            min_weight_node_table[i][j] = k_min;
        }
    }
    // Initialize memo and computed tables
    memset(computed_table, 0, sizeof(computed_table));
    // Compute the answer
    long long answer = solve(1, N, 1);
    printf("%lld\n", answer);
    return 0;
}