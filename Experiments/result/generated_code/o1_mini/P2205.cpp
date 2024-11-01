#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store segments
typedef struct {
    long long start;
    long long end;
} Segment;

// Comparator for qsort
int cmp(const void* a, const void* b){
    long long x = *((long long*)a);
    long long y = *((long long*)b);
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    
    Segment* segments = (Segment*)malloc(N * sizeof(Segment));
    long long pos = 0;
    // To store all unique points
    long long* points = (long long*)malloc(2 * N * 2 * sizeof(long long));
    int point_cnt = 0;
    
    for(int i=0;i<N;i++){
        long long dist;
        char dir;
        scanf("%lld %c", &dist, &dir);
        long long new_pos;
        if(dir == 'L') new_pos = pos - dist;
        else new_pos = pos + dist;
        if(new_pos < pos){
            segments[i].start = new_pos;
            segments[i].end = pos;
        }
        else{
            segments[i].start = pos;
            segments[i].end = new_pos;
        }
        points[point_cnt++] = segments[i].start;
        points[point_cnt++] = segments[i].end;
        pos = new_pos;
    }
    
    // Sort and remove duplicates
    qsort(points, point_cnt, sizeof(long long), cmp);
    int unique = 0;
    for(int i=1;i<point_cnt;i++){
        if(points[i] != points[unique]){
            unique++;
            points[unique] = points[i];
        }
    }
    unique++;
    
    // Function to find index using binary search
    auto find_idx = [&](long long x) -> int{
        int left = 0, right = unique-1;
        while(left <= right){
            int mid = left + (right - left)/2;
            if(points[mid] < x) left = mid +1;
            else if(points[mid] > x) right = mid -1;
            else return mid;
        }
        return left;
    };
    
    // Initialize difference array
    int size = unique +1;
    int* diff = (int*)calloc(size, sizeof(int));
    
    // Apply difference for each segment
    for(int i=0;i<N;i++){
        int l = find_idx(segments[i].start);
        int r = find_idx(segments[i].end);
        diff[l] +=1;
        diff[r] -=1;
    }
    
    // Compute prefix sums and calculate the result
    long long res =0;
    int current =0;
    for(int i=0;i<unique-1;i++){
        current += diff[i];
        if(current >= K){
            res += points[i+1] - points[i];
        }
    }
    
    printf("%lld\n", res);
    
    // Free allocated memory
    free(segments);
    free(points);
    free(diff);
    
    return 0;
}