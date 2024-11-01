#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} cow;

// Comparator for sorting cows by x
int cmp_x(const void* a, const void* b) {
    cow *cow_a = (cow*)a;
    cow *cow_b = (cow*)b;
    if (cow_a->x != cow_b->x)
        return cow_a->x - cow_b->x;
    return cow_a->y - cow_b->y;
}

// Comparator for sorting cows by y
int cmp_y(const void* a, const void* b) {
    cow *cow_a = (cow*)a;
    cow *cow_b = (cow*)b;
    return cow_a->y - cow_b->y;
}

// Comparator for integers
int cmp_int(const void* a, const void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia != ib)
        return ia - ib;
    return 0;
}

// Function to count number of elements less than b using binary search
int count_less(int* arr, int size, int b) {
    int left = 0, right = size;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(arr[mid] < b)
            left = mid +1;
        else
            right = mid;
    }
    return left;
}

int main(){
    int N;
    scanf("%d", &N);
    cow cows[N];
    int i;
    for(i = 0; i < N; ++i){
        scanf("%d %d", &cows[i].x, &cows[i].y);
    }

    // Sort cows by x
    qsort(cows, N, sizeof(cow), cmp_x);

    // Collect b_candidates as y_i +1
    int b_all[N];
    for(i = 0; i < N; ++i){
        b_all[i] = cows[i].y +1;
    }
    qsort(b_all, N, sizeof(int), cmp_int);
    // Remove duplicates
    int b_unique[N];
    int b_size = 0;
    if(N >0){
        b_unique[b_size++] = b_all[0];
        for(i =1; i < N; ++i){
            if(b_all[i] != b_all[i-1]){
                b_unique[b_size++] = b_all[i];
            }
        }
    }

    int min_M = N;
    // Iterate through all possible a_candidates
    for(int a_idx = 0; a_idx <= N; a_idx++){
        int a;
        if(a_idx < N){
            a = cows[a_idx].x +1;
        }
        else{
            a = cows[N-1].x +2;
        }
        // Left cows: 0 to a_idx-1
        int left_count = a_idx;
        int right_count = N - left_count;

        // Prepare left and right cows sorted by y
        int left_y[left_count];
        int right_y[right_count];
        for(int j =0; j < left_count; ++j){
            left_y[j] = cows[j].y;
        }
        for(int j =0; j < right_count; ++j){
            right_y[j] = cows[left_count + j].y;
        }
        qsort(left_y, left_count, sizeof(int), cmp_int);
        qsort(right_y, right_count, sizeof(int), cmp_int);

        // Iterate through all b_unique
        for(int b_idx =0; b_idx < b_size; ++b_idx){
            int b = b_unique[b_idx];
            int lb = count_less(left_y, left_count, b);
            int rb = count_less(right_y, right_count, b);
            int la = left_count - lb;
            int ra = right_count - rb;
            // Find max of lb, la, rb, ra
            int current_max = lb;
            if(la > current_max) current_max = la;
            if(rb > current_max) current_max = rb;
            if(ra > current_max) current_max = ra;
            if(current_max < min_M){
                min_M = current_max;
                if(min_M == 0){
                    break;
                }
            }
        }
    }

    printf("%d\n", min_M);
    return 0;
}