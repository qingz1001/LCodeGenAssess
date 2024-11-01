#include <stdio.h>
#include <stdlib.h>

#define MAX 200005

long long a_original[MAX];
long long a_sorted[MAX];
long long sorted_unique_a[MAX];
int u_cmd[MAX];
int rank_map[MAX];
int tree_arr[MAX];
int k;

int cmp(const void *a, const void *b){
    if(*(long long*)a < *(long long*)b) return -1;
    if(*(long long*)a > *(long long*)b) return 1;
    return 0;
}

int find_rank(long long val){
    int left=1, right=k, mid, res;
    while(left <= right){
        mid = left + (right - left)/2;
        if(sorted_unique_a[mid] < val){
            left = mid +1;
        }
        else if(sorted_unique_a[mid] > val){
            right = mid -1;
        }
        else{
            return mid;
        }
    }
    return -1;
}

void update_tree(int idx, int val){
    while(idx <= k){
        tree_arr[idx] += val;
        idx += idx & (-idx);
    }
}

int query_tree(int idx){
    int res =0;
    while(idx >0){
        res += tree_arr[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int find_kth(int x){
    int idx=0, bit=1;
    while((bit <<=1) <=k);
    bit >>=1;
    while(bit >0){
        if(idx + bit <=k && tree_arr[idx + bit] < x){
            idx += bit;
            x -= tree_arr[idx];
        }
        bit >>=1;
    }
    return idx +1;
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    for(int i=1;i<=m;i++) scanf("%lld", &a_original[i]);
    for(int i=1;i<=m;i++) a_sorted[i] = a_original[i];
    qsort(a_sorted +1, m, sizeof(long long), cmp);
    sorted_unique_a[1] = a_sorted[1];
    k =1;
    for(int i=2;i<=m;i++){
        if(a_sorted[i] != a_sorted[i-1]){
            sorted_unique_a[++k] = a_sorted[i];
        }
    }
    for(int i=1;i<=m;i++) rank_map[i] = find_rank(a_original[i]);
    for(int i=1;i<=n;i++) scanf("%d", &u_cmd[i]);
    int current_add =0;
    for(int j=1;j<=n;j++){
        int target_add = u_cmd[j];
        for(int l = current_add +1; l <= target_add; l++){
            update_tree(rank_map[l], 1);
        }
        current_add = target_add;
        int ith = j;
        int x = find_kth(ith);
        printf("%lld\n", sorted_unique_a[x]);
    }
    return 0;
}