#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

typedef struct {
    int data;
    int weight;
    int freq;
} Node;

int compare(const void* a, const void* b) {
    Node* na = (Node*)a;
    Node* nb = (Node*)b;
    if (na->data != nb->data)
        return na->data - nb->data;
    return 0;
}

int main(){
    int N;
    ll K;
    scanf("%d %lld", &N, &K);
    Node nodes[N];
    for(int i=0;i<N;i++) scanf("%d", &nodes[i].data);
    for(int i=0;i<N;i++) scanf("%d", &nodes[i].weight);
    for(int i=0;i<N;i++) scanf("%d", &nodes[i].freq);
    qsort(nodes, N, sizeof(Node), compare);
    ll sum_f[N+1][N+1];
    for(int i=1;i<=N;i++){
        sum_f[i][i] = nodes[i-1].freq;
        for(int j=i+1;j<=N;j++) sum_f[i][j] = sum_f[i][j-1] + nodes[j-1].freq;
    }
    int min_r[N+1][N+1];
    for(int i=1;i<=N;i++){
        min_r[i][i] = i;
        for(int j=i+1;j<=N;j++){
            if(nodes[j-1].weight < nodes[min_r[i][j-1]-1].weight){
                min_r[i][j] = j;
            }
            else{
                min_r[i][j] = min_r[i][j-1];
            }
        }
    }
    ll DP[N+1][N+1];
    for(int i=1;i<=N;i++) {
        DP[i][i] = nodes[i-1].freq;
    }
    for(int len=2; len<=N; len++){
        for(int i=1; i+len-1<=N; i++){
            int j = i + len -1;
            DP[i][j] = LLONG_MAX;
            for(int r=i;r<=j;r++){
                ll cost = 0;
                if(r != min_r[i][j]) cost += K;
                ll total = cost + DP[i][r-1] + DP[r+1][j] + sum_f[i][j];
                if(total < DP[i][j]) DP[i][j] = total;
            }
        }
    }
    printf("%lld", DP[1][N]);
}