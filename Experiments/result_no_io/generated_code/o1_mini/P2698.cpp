#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int t;
} Drop;

int cmp(const void* a, const void* b) {
    Drop* da = (Drop*)a;
    Drop* db = (Drop*)b;
    if (da->x != db->x)
        return da->x - db->x;
    return da->t - db->t;
}

int check(int W, Drop* drops, int N, int D) {
    int left = 0;
    // Deques for min and max
    int* min_deque = (int*)malloc(N * sizeof(int));
    int min_head = 0, min_tail = 0;
    int* max_deque = (int*)malloc(N * sizeof(int));
    int max_head = 0, max_tail = 0;
    
    for(int right = 0; right < N; right++) {
        // Update min_deque
        while(min_tail > min_head && drops[right].t <= drops[min_tail-1].t) {
            min_tail--;
        }
        min_deque[min_tail++] = right;
        
        // Update max_deque
        while(max_tail > max_head && drops[right].t >= drops[max_tail-1].t) {
            max_tail--;
        }
        max_deque[max_tail++] = right;
        
        // Move left pointer
        while(drops[right].x - drops[left].x > W) {
            if(min_deque[min_head] == left) min_head++;
            if(max_deque[max_head] == left) max_head++;
            left++;
        }
        
        // Check condition
        if(max_tail > max_head && min_tail > min_head) {
            int current_min = drops[min_deque[min_head]].t;
            int current_max = drops[max_deque[max_head]].t;
            if(current_max - current_min >= D){
                free(min_deque);
                free(max_deque);
                return 1;
            }
        }
    }
    free(min_deque);
    free(max_deque);
    return 0;
}

int main(){
    int N, D;
    scanf("%d %d", &N, &D);
    Drop* drops = (Drop*)malloc(N * sizeof(Drop));
    int min_x = 1000001, max_x = 0;
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &drops[i].x, &drops[i].t);
        if(drops[i].x < min_x) min_x = drops[i].x;
        if(drops[i].x > max_x) max_x = drops[i].x;
    }
    qsort(drops, N, sizeof(Drop), cmp);
    
    int low = 0, high = max_x - min_x;
    int answer = -1;
    while(low <= high){
        int mid = low + (high - low)/2;
        if(check(mid, drops, N, D)){
            answer = mid;
            high = mid -1;
        }
        else{
            low = mid +1;
        }
    }
    // Check if answer was found
    if(answer == -1){
        // It's possible that W = max_x - min_x satisfies
        // So perform a final check
        // Alternatively, if no window satisfied in binary search, answer remains -1
    }
    printf("%d\n", answer);
    free(drops);
    return 0;
}