#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef long long ll;

// Comparator for qsort
int cmp(const void *a, const void *b) {
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int N;
    scanf("%d", &N);
    ll *a = (ll*)malloc(N * sizeof(ll));
    ll *sorted = (ll*)malloc(N * sizeof(ll));
    for(int i=0;i<N;i++){
        scanf("%lld", &a[i]);
        sorted[i] = a[i];
    }
    qsort(sorted, N, sizeof(ll), cmp);
    ll global_min = sorted[0];
    // Function to find index using binary search
    // Returns the sorted index of key
    auto find_index = [&](ll key) -> int {
        int left = 0, right = N-1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(sorted[mid] == key) return mid;
            else if(sorted[mid] < key) left = mid +1;
            else right = mid -1;
        }
        return -1;
    };
    // Create mapping
    ll *pos = (ll*)malloc(N * sizeof(ll));
    for(int i=0;i<N;i++){
        pos[i] = find_index(a[i]);
    }
    bool *visited = (bool*)calloc(N, sizeof(bool));
    ll total_cost = 0;
    for(int i=0;i<N;i++){
        if(!visited[i]){
            int cycle_size =0;
            ll cycle_sum=0, cycle_min=1000000001;
            int j = i;
            while(!visited[j]){
                visited[j]=true;
                ll val = a[j];
                cycle_sum += val;
                if(val < cycle_min) cycle_min = val;
                j = pos[j];
                cycle_size++;
            }
            if(cycle_size >1){
                ll cost1 = cycle_sum + (cycle_size -2)*cycle_min;
                ll cost2 = cycle_sum + cycle_min + (cycle_size +1)*global_min;
                if(cost1 < cost2){
                    total_cost += cost1;
                }
                else{
                    total_cost += cost2;
                }
            }
        }
    }
    printf("%lld\n", total_cost);
    free(a);
    free(sorted);
    free(pos);
    free(visited);
    return 0;
}