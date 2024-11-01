#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 2000
#define MAX_COMPONENTS 2000
#define MAX_QUEUE (MAX_N)
#define BITSET_SIZE ((MAX_N + 63)/64)

unsigned char F[MAX_N][MAX_N];
unsigned char mutual_friends[MAX_N][MAX_N];
int color_arr[MAX_N];
int queue_arr[MAX_QUEUE];
int front, rear;
int components_c0[MAX_COMPONENTS];
int components_c1[MAX_COMPONENTS];
int component_count = 0;

typedef unsigned long long ull;

int main(){
    int N;
    scanf("%d", &N);
    for(int i=0;i<N;i++){
        int j;
        while(scanf("%d", &j) && j != 0){
            if(j >=1 && j <=N){
                F[i][j-1] = 1;
            }
        }
    }
    // Build mutual_friends
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i != j && F[i][j] && F[j][i]){
                mutual_friends[i][j] = 1;
            }
        }
    }
    memset(color_arr, -1, sizeof(color_arr));
    int impossible = 0;
    for(int i=0;i<N && !impossible;i++){
        if(color_arr[i]==-1){
            front = rear =0;
            queue_arr[rear++] = i;
            color_arr[i] = 0;
            int c0 =1, c1=0;
            while(front < rear && !impossible){
                int u = queue_arr[front++];
                for(int v=0;v<N && !impossible;v++){
                    if(u == v) continue;
                    if(mutual_friends[u][v]==0){
                        if(color_arr[v]==-1){
                            color_arr[v] = 1 - color_arr[u];
                            if(color_arr[v]==0) c0++;
                            else c1++;
                            queue_arr[rear++] = v;
                        }
                        else{
                            if(color_arr[v] != 1 - color_arr[u]){
                                impossible =1;
                            }
                        }
                    }
                }
            }
            if(!impossible){
                components_c0[component_count] = c0;
                components_c1[component_count] = c1;
                component_count++;
            }
        }
    }
    if(impossible){
        printf("No solution\n");
        return 0;
    }
    // DP for subset sum
    int dp_size = N +1;
    unsigned char dp[2001];
    memset(dp, 0, sizeof(dp));
    dp[0] =1;
    for(int i=0;i<component_count;i++){
        int c0 = components_c0[i];
        int c1 = components_c1[i];
        unsigned char tmp[2001];
        memset(tmp, 0, sizeof(tmp));
        for(int s=0;s<=N;s++){
            if(dp[s]){
                if(s + c0 <=N){
                    tmp[s + c0] =1;
                }
                if(s + c1 <=N){
                    tmp[s + c1] =1;
                }
            }
        }
        memcpy(dp, tmp, sizeof(dp));
    }
    // Find the closest sum to N/2
    int target = N/2;
    int best = -1;
    for(int s=target;s>=0;s--){
        if(dp[s]){
            best = s;
            break;
        }
    }
    if(best == -1){
        printf("No solution\n");
        return 0;
    }
    int other = N - best;
    if(best > other){
        int temp = best;
        best = other;
        other = temp;
    }
    printf("%d %d\n", best, other);
    return 0;
}