#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXSIZE 2000000

typedef long long ll;

typedef struct Node {
    int B;
    int C;
    int L;
    int *children;
    int child_count;
    int child_capacity;
} Node;

Node nodes[MAXN];
int children_storage[MAXSIZE];
int children_ptr = 0;

int sorted_start[MAXN];
int sorted_size_arr[MAXN];
int sorted_storage[MAXSIZE];
ll prefix_sum_storage_arr[MAXSIZE];
int sorted_ptr = 0;

ll M;
ll max_satisfaction = 0;

// Comparator for qsort
int cmp_int(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

// Merge two sorted arrays a and size_a into b and size_b
int merge(int *a, int size_a, int *b, int size_b, int *merged){
    int i=0, j=0, k=0;
    while(i < size_a && j < size_b){
        if(a[i] < b[j]){
            merged[k++] = a[i++];
        }
        else{
            merged[k++] = b[j++];
        }
    }
    while(i < size_a){
        merged[k++] = a[i++];
    }
    while(j < size_b){
        merged[k++] = b[j++];
    }
    return k;
}

void dfs(int u){
    // Initialize with own C
    sorted_start[u] = sorted_ptr;
    sorted_storage[sorted_ptr] = nodes[u].C;
    prefix_sum_storage_arr[sorted_ptr] = nodes[u].C;
    sorted_size_arr[u] = 1;
    sorted_ptr++;

    // Process children
    for(int i=0;i<nodes[u].child_count;i++){
        int v = nodes[u].children[i];
        dfs(v);
        // If current list is smaller, swap
        if(sorted_size_arr[v] > sorted_size_arr[u]){
            // Swap sorted_start and sorted_size
            int temp_start = sorted_start[u];
            int temp_size = sorted_size_arr[u];
            sorted_start[u] = sorted_start[v];
            sorted_size_arr[u] = sorted_size_arr[v];
            sorted_start[v] = temp_start;
            sorted_size_arr[v] = temp_size;
        }
        // Merge sorted_start[v] into sorted_start[u]
        int total_size = sorted_size_arr[u] + sorted_size_arr[v];
        if(sorted_ptr + sorted_size_arr[v] > MAXSIZE){
            // Prevent overflow
            exit(0);
        }
        int *temp = (int*)malloc((sorted_size_arr[u] + sorted_size_arr[v]) * sizeof(int));
        int size = merge(&sorted_storage[sorted_start[u]], sorted_size_arr[u],
                         &sorted_storage[sorted_start[v]], sorted_size_arr[v],
                         temp);
        for(int j=0;j<size;j++) sorted_storage[sorted_ptr + j] = temp[j];
        free(temp);
        // Update prefix sums
        prefix_sum_storage_arr[sorted_ptr] = nodes[u].C; // Placeholder
        for(int j=0; j<size; j++){
            if(j == 0){
                prefix_sum_storage_arr[sorted_ptr + j] = sorted_storage[sorted_ptr + j];
            }
            else{
                prefix_sum_storage_arr[sorted_ptr + j] = prefix_sum_storage_arr[sorted_ptr + j - 1] + sorted_storage[sorted_ptr + j];
            }
        }
        sorted_start[u] = sorted_ptr;
        sorted_size_arr[u] = size;
        sorted_ptr += size;
    }

    // Now, compute satisfaction for this node as manager
    // Option 1: Not include manager
    // Find max k where prefix_sum[k-1] <= M
    // Binary search
    int size = sorted_size_arr[u];
    int left = 0, right = size;
    int k1 = 0;
    while(left < right){
        int mid = (left + right) / 2;
        if(prefix_sum_storage_arr[sorted_start[u] + mid] <= M){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }
    k1 = left;
    ll satisfaction1 = (ll)k1 * nodes[u].L;
    if(satisfaction1 > max_satisfaction) max_satisfaction = satisfaction1;

    // Option 2: Include manager
    // Find max k where C_u + prefix_sum[k-1] <= M
    if(nodes[u].C <= M){
        ll remaining = M - nodes[u].C;
        left = 0;
        right = size;
        int k2 = 0;
        while(left < right){
            int mid = (left + right) / 2;
            if(prefix_sum_storage_arr[sorted_start[u] + mid] <= remaining){
                left = mid + 1;
            }
            else{
                right = mid;
            }
        }
        k2 = left + 1; // Including manager
        if(k2 > size +1) k2 = size +1;
        if(k2 > 0 && k2-1 <= size){
            ll sum = nodes[u].C;
            if(k2-1 >0){
                sum += prefix_sum_storage_arr[sorted_start[u] + k2 -2];
            }
            if(sum <= M){
                ll satisfaction2 = (ll)k2 * nodes[u].L;
                if(satisfaction2 > max_satisfaction) max_satisfaction = satisfaction2;
            }
        }
    }
}

int main(){
    int N;
    scanf("%d %lld", &N, &M);
    for(int i=1;i<=N;i++){
        int B, C, L;
        scanf("%d %d %d", &B, &C, &L);
        nodes[i].B = B;
        nodes[i].C = C;
        nodes[i].L = L;
        nodes[i].children = &children_storage[children_ptr];
        nodes[i].child_count = 0;
        nodes[i].child_capacity = MAXSIZE - children_ptr;
        if(B != 0){
            nodes[B].children[nodes[B].child_count++] = i;
        }
    }
    // Find root
    int root = 1;
    for(int i=1;i<=N;i++) if(nodes[i].B == 0){ root = i; break;}
    dfs(root);
    printf("%lld\n", max_satisfaction);
    return 0;
}