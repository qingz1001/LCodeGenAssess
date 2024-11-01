#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int q;
    int l;
    int r;
} Operation;

// Comparator for qsort
int cmp_int(const void* a, const void* b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(ia < ib) return -1;
    if(ia > ib) return 1;
    return 0;
}

// Binary search to find the index
int binary_search_unique(int* arr, int size, int target){
    int left = 0, right = size -1, mid;
    while(left <= right){
        mid = left + (right - left)/2;
        if(arr[mid] == target) return mid +1;
        else if(arr[mid] < target) left = mid +1;
        else right = mid -1;
    }
    return -1;
}

long long BIT_left[300005];
long long BIT_right[300005];
int size_unique;

// Update BIT
void update(long long* BIT, int index){
    while(index <= size_unique){
        BIT[index] +=1;
        index += index & (-index);
    }
}

// Query BIT
long long query(long long* BIT, int index){
    long long res =0;
    while(index >0){
        res += BIT[index];
        index -= index & (-index);
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    Operation* operations = (Operation*)malloc(sizeof(Operation)*m);
    int* all_pos = (int*)malloc(sizeof(int)*3*m);
    int pos_cnt =0;
    for(int i=0;i<m;i++){
        scanf("%d %d %d", &operations[i].q, &operations[i].l, &operations[i].r);
        all_pos[pos_cnt++] = operations[i].l;
        all_pos[pos_cnt++] = operations[i].r;
    }
    // Sort and remove duplicates
    qsort(all_pos, pos_cnt, sizeof(int), cmp_int);
    // Remove duplicates
    int unique_cnt =0;
    for(int i=0;i<pos_cnt;i++){
        if(i ==0 || all_pos[i] != all_pos[i-1]){
            all_pos[unique_cnt++] = all_pos[i];
        }
    }
    size_unique = unique_cnt;
    // Process operations
    for(int i=0;i<m;i++){
        if(operations[i].q ==1){
            // Plant mine
            int l = operations[i].l;
            int r = operations[i].r;
            int l_mapped = binary_search_unique(all_pos, unique_cnt, l);
            int r_mapped = binary_search_unique(all_pos, unique_cnt, r);
            update(BIT_left, l_mapped);
            update(BIT_right, r_mapped);
        }
        else{
            // Query
            int L = operations[i].l;
            int R = operations[i].r;
            int L_mapped = binary_search_unique(all_pos, unique_cnt, L);
            if(L_mapped == -1){
                // Find the first greater
                int left =0, right = unique_cnt -1, mid, res = unique_cnt+1;
                while(left <= right){
                    mid = left + (right - left)/2;
                    if(all_pos[mid] >= L){
                        res = mid +1;
                        right = mid -1;
                    }
                    else{
                        left = mid +1;
                    }
                }
                L_mapped = res;
            }
            int R_mapped = binary_search_unique(all_pos, unique_cnt, R);
            if(R_mapped == -1){
                // Find the last less
                int left =0, right = unique_cnt -1, mid, res =0;
                while(left <= right){
                    mid = left + (right - left)/2;
                    if(all_pos[mid] <= R){
                        res = mid +1;
                        left = mid +1;
                    }
                    else{
                        right = mid -1;
                    }
                }
                R_mapped = res;
            }
            long long res = query(BIT_left, R_mapped) - query(BIT_right, L_mapped -1);
            printf("%lld\n", res);
        }
    }
    free(operations);
    free(all_pos);
    return 0;
}