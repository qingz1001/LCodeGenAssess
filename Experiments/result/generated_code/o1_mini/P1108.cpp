#include <stdio.h>
#include <stdlib.h>

// Structure for BIT node
typedef struct {
    int max_len;
    unsigned int count;
} BITNode;

// Comparator for descending sort
int cmp_desc(const void *a, const void *b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ib > ia) return 1;
    else if (ib < ia) return -1;
    return 0;
}

// Binary search to find rank
int binary_search(int *sorted, int size, int key) {
    int left = 0, right = size -1, mid;
    while(left <= right){
        mid = left + (right - left)/2;
        if(sorted[mid] == key) return mid +1;
        else if(sorted[mid] < key) right = mid -1;
        else left = mid +1;
    }
    return -1;
}

int main(){
    int N;
    scanf("%d", &N);
    int A[5000];
    for(int i=0;i<N;i++) scanf("%d", &A[i]);
    
    // Create unique sorted list in descending order
    int temp[5000];
    for(int i=0;i<N;i++) temp[i] = A[i];
    qsort(temp, N, sizeof(int), cmp_desc);
    int unique[5000];
    int unique_size =0;
    if(N >0){
        unique[unique_size++] = temp[0];
        for(int i=1;i<N;i++) {
            if(temp[i] != temp[i-1]) unique[unique_size++] = temp[i];
        }
    }
    
    // Initialize BIT
    BITNode BIT_tree[5001];
    for(int i=0;i<=unique_size;i++){
        BIT_tree[i].max_len =0;
        BIT_tree[i].count =0;
    }
    
    // Function to update BIT
    void update(int index, int len, unsigned int cnt){
        while(index <= unique_size){
            if(len > BIT_tree[index].max_len){
                BIT_tree[index].max_len = len;
                BIT_tree[index].count = cnt;
            }
            else if(len == BIT_tree[index].max_len){
                BIT_tree[index].count += cnt;
            }
            index += index & (-index);
        }
    }
    
    // Function to query BIT
    void query(int index, int *res_len, unsigned int *res_cnt){
        *res_len =0;
        *res_cnt =0;
        while(index >0){
            if(BIT_tree[index].max_len > *res_len){
                *res_len = BIT_tree[index].max_len;
                *res_cnt = BIT_tree[index].count;
            }
            else if(BIT_tree[index].max_len == *res_len){
                *res_cnt += BIT_tree[index].count;
            }
            index -= index & (-index);
        }
    }
    
    int overall_max =0;
    unsigned int total_cnt =0;
    
    for(int i=0;i<N;i++){
        int rank = binary_search(unique, unique_size, A[i]);
        int q_len;
        unsigned int q_cnt;
        query(rank -1, &q_len, &q_cnt);
        int current_len = q_len +1;
        unsigned int current_cnt = (q_len ==0) ? 1 : q_cnt;
        // Update BIT
        update(rank, current_len, current_cnt);
        // Update overall_max and total_cnt
        if(current_len > overall_max){
            overall_max = current_len;
            total_cnt = current_cnt;
        }
        else if(current_len == overall_max){
            total_cnt += current_cnt;
        }
    }
    
    printf("%d %u\n", overall_max, total_cnt);
    
    return 0;
}