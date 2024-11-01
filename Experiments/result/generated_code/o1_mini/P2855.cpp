#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    int diff = (*(int*)a) - (*(int*)b);
    if(diff < 0) return -1;
    if(diff > 0) return 1;
    return 0;
}

// Function to check if a minimum distance D is possible
int is_possible(int D, int N, int M, int sorted_positions[], int L) {
    int last_pos = 0;
    int remove_count = 0;
    for(int i = 0; i <= N; i++) { // Include end position
        int current_pos = (i < N) ? sorted_positions[i] : L;
        if(current_pos - last_pos < D) {
            remove_count++;
        }
        else {
            last_pos = current_pos;
        }
    }
    return remove_count <= M;
}

int main(){
    int L, N, M;
    if(scanf("%d %d %d", &L, &N, &M)!=3){
        return 1;
    }
    int *positions = (int*)malloc(N * sizeof(int));
    for(int i=0; i<N; i++){
        if(scanf("%d", &positions[i])!=1){
            free(positions);
            return 1;
        }
    }
    qsort(positions, N, sizeof(int), compare);
    int low = 1, high = L, answer = 1;
    while(low <= high){
        int mid = low + (high - low)/2;
        if(is_possible(mid, N, M, positions, L)){
            answer = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%d\n", answer);
    free(positions);
    return 0;
}