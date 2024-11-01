#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// Comparator for qsort
int cmp(const void *a, const void *b){
    ll x = *(ll*)a;
    ll y = *(ll*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

ll array[500005];
ll sorted[500005];
ll tree_arr[500005];
int size;

// Update BIT
void update_tree(int index){
    while(index <= size){
        tree_arr[index] += 1;
        index += index & (-index);
    }
}

// Query BIT
ll query_tree(int index){
    ll sum = 0;
    while(index > 0){
        sum += tree_arr[index];
        index -= index & (-index);
    }
    return sum;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        scanf("%lld", &array[i]);
        sorted[i] = array[i];
    }
    qsort(sorted, n, sizeof(ll), cmp);
    // Remove duplicates
    size = 0;
    for(int i=0;i<n;i++){
        if(i ==0 || sorted[i] != sorted[i-1]){
            sorted[size++] = sorted[i];
        }
    }
    ll ans = 0;
    for(int i=n-1;i>=0;i--){
        // Binary search for rank
        int left = 0, right = size-1, mid, rank;
        while(left <= right){
            mid = left + (right - left)/2;
            if(sorted[mid] < array[i]){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        rank = left +1;
        ans += query_tree(rank -1);
        update_tree(left +1);
    }
    printf("%lld\n", ans);
    return 0;
}