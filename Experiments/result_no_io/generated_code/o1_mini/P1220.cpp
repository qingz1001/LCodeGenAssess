#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 51
#define MAX_STATES 1000

typedef long long ll;

typedef struct {
    ll t;
    ll sum;
} State;

typedef struct {
    State states[MAX_STATES];
    int count;
} StateList;

// Initialize a StateList
void initStateList(StateList *list) {
    list->count = 0;
}

// Add a state with t_new and sum_new to the StateList with pruning
int addState(StateList *list, ll t_new, ll sum_new) {
    // Check if dominated
    for(int i = 0; i < list->count; i++) {
        if(list->states[i].t <= t_new && list->states[i].sum <= sum_new){
            return 0; // Dominated, do not add
        }
    }
    // Remove dominated states
    int j = 0;
    while(j < list->count) {
        if(list->states[j].t >= t_new && list->states[j].sum >= sum_new){
            // Remove this state by shifting
            for(int k = j; k < list->count -1; k++) {
                list->states[k] = list->states[k+1];
            }
            list->count--;
        }
        else{
            j++;
        }
    }
    // Add the new state
    if(list->count < MAX_STATES){
        list->states[list->count].t = t_new;
        list->states[list->count].sum = sum_new;
        list->count++;
        return 1; // Added
    }
    return 0; // Not added
}

int main(){
    int n, c;
    scanf("%d %d", &n, &c);
    int p[MAXN];
    int W[MAXN];
    for(int i =1;i<=n;i++) scanf("%d %d", &p[i], &W[i]);
    
    ll prefix_sum[MAXN];
    prefix_sum[0] =0;
    for(int i=1;i<=n;i++) prefix_sum[i] = prefix_sum[i-1] + W[i];
    
    ll total_W = prefix_sum[n];
    
    // Initialize DP
    StateList dp[MAXN][MAXN][2];
    for(int i=1;i<=n;i++) {
        for(int j=i;j<=n;j++) {
            for(int d=0;d<2;d++) {
                initStateList(&dp[i][j][d]);
            }
        }
    }
    
    // Initialize starting state
    addState(&dp[c][c][0], 0, 0);
    addState(&dp[c][c][1], 0, 0);
    
    // Queue for BFS
    int queue_size = 0;
    int queue_capacity = MAXN * MAXN * 2;
    int queue_front = 0;
    int queue_back = 0;
    int queue_l[MAXN * MAXN *2];
    int queue_r[MAXN * MAXN *2];
    int queue_d[MAXN * MAXN *2];
    
    // Enqueue initial states
    queue_l[queue_back] = c;
    queue_r[queue_back] = c;
    queue_d[queue_back] = 0;
    queue_back++;
    
    queue_l[queue_back] = c;
    queue_r[queue_back] = c;
    queue_d[queue_back] = 1;
    queue_back++;
    
    while(queue_front < queue_back){
        int l = queue_l[queue_front];
        int r = queue_r[queue_front];
        int d = queue_d[queue_front];
        queue_front++;
        
        StateList current = dp[l][r][d];
        for(int si=0; si < current.count; si++){
            ll current_t = current.states[si].t;
            ll current_sum = current.states[si].sum;
            
            // Move Left
            if(l >1){
                int new_l = l -1;
                int new_r = r;
                int new_d = 0;
                ll delta_t;
                if(d ==0){
                    delta_t = p[l] - p[new_l];
                }
                else{
                    delta_t = p[r] - p[new_l];
                }
                ll t_new = current_t + delta_t;
                ll S = total_W - (prefix_sum[r] - prefix_sum[l-1]);
                ll sum_new = current_sum + S * delta_t + (ll)W[new_l] * t_new;
                if(addState(&dp[new_l][new_r][new_d], t_new, sum_new)){
                    queue_l[queue_back] = new_l;
                    queue_r[queue_back] = new_r;
                    queue_d[queue_back] = new_d;
                    queue_back++;
                }
            }
            // Move Right
            if(r <n){
                int new_r = r +1;
                int new_l = l;
                int new_d =1;
                ll delta_t;
                if(d ==1){
                    delta_t = p[new_r] - p[r];
                }
                else{
                    delta_t = p[new_r] - p[l];
                }
                ll t_new = current_t + delta_t;
                ll S = total_W - (prefix_sum[r] - prefix_sum[l-1]);
                ll sum_new = current_sum + S * delta_t + (ll)W[new_r] * t_new;
                if(addState(&dp[new_l][new_r][new_d], t_new, sum_new)){
                    queue_l[queue_back] = new_l;
                    queue_r[queue_back] = new_r;
                    queue_d[queue_back] = new_d;
                    queue_back++;
                }
            }
        }
    }
    
    // Get the minimal sum from dp[1][n][0] and dp[1][n][1]
    ll min_sum = -1;
    for(int d=0; d<2; d++){
        StateList final = dp[1][n][d];
        for(int i=0;i<final.count;i++) {
            if(min_sum == -1 || final.states[i].sum < min_sum){
                min_sum = final.states[i].sum;
            }
        }
    }
    printf("%lld\n", min_sum);
    return 0;
}