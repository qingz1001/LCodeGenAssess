#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001
#define MAXK 151
#define MOD 10007

int head_arr[MAXN];
int to_arr[2 * MAXN];
int next_arr[2 * MAXN];
int edge_count = 0;

int power_table[MAXN][MAXK];
int visited[MAXN];
int queue_arr[MAXN];
int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i=0;i<n-1;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        to_arr[edge_count] = v;
        next_arr[edge_count] = head_arr[u];
        head_arr[u] = edge_count++;
        
        to_arr[edge_count] = u;
        next_arr[edge_count] = head_arr[v];
        head_arr[v] = edge_count++;
    }
    // Precompute power_table
    for(int d=0; d<=n; d++){
        power_table[d][0] = 1;
        for(int m=1; m<=k; m++){
            if(d ==0){
                power_table[d][m] = 0;
            }
            else{
                power_table[d][m] = (power_table[d][m-1] * d) % MOD;
            }
        }
    }
    int step =1;
    for(int i=1;i<=n;i++){
        long long sum =0;
        int head =0, tail =0;
        queue_arr[tail++] = i;
        visited[i] = step;
        int current_distance =0;
        int current_level =1;
        while(head < tail){
            // Add to sum
            if(current_distance <=k){
                sum += (long long)current_level * power_table[current_distance][k];
                if(sum >= 1000000000) sum %= MOD;
            }
            // Process current level
            int next_level =0;
            for(int c=0; c<current_level; c++){
                int u = queue_arr[head++];
                for(int e = head_arr[u]; e != -1; e = next_arr[e]){
                    int v = to_arr[e];
                    if(visited[v] != step){
                        visited[v] = step;
                        queue_arr[tail++] = v;
                        next_level++;
                    }
                }
            }
            current_distance++;
            current_level = next_level;
        }
        // After BFS, sum might exceed MOD
        sum %= MOD;
        printf("%lld\n", sum);
        step++;
    }
    return 0;
}