#include <stdio.h>
#include <stdlib.h>

// Binary search for the LIS
int binary_search(int *tail, int size, int key) {
    int left = 0, right = size;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (tail[mid] < key)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int main(){
    int n;
    scanf("%d", &n);
    int *P1 = (int*)malloc(n * sizeof(int));
    int *P2 = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) scanf("%d", &P1[i]);
    for(int i=0;i<n;i++) scanf("%d", &P2[i]);
    // Create position map for P2
    int *pos = (int*)malloc((n+1) * sizeof(int));
    for(int i=0;i<n;i++) pos[P2[i]] = i;
    // Convert P1 to positions
    int *sequence = (int*)malloc(n * sizeof(int));
    for(int i=0;i<n;i++) sequence[i] = pos[P1[i]];
    // Find LIS
    int *tail = (int*)malloc(n * sizeof(int));
    int length = 0;
    for(int i=0;i<n;i++){
        int idx = binary_search(tail, length, sequence[i]);
        tail[idx] = sequence[i];
        if(idx == length) length++;
    }
    printf("%d\n", length);
    free(P1);
    free(P2);
    free(pos);
    free(sequence);
    free(tail);
    return 0;
}