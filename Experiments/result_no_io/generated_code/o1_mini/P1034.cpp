#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int x;
    int y;
} Point;

Point points[50];
int n, k;

// Comparator for sorting by x
int cmp_x(const void *a, const void *b) {
    int idx1 = *(int*)a;
    int idx2 = *(int*)b;
    if (points[idx1].x != points[idx2].x)
        return points[idx1].x - points[idx2].x;
    return points[idx1].y - points[idx2].y;
}

// Comparator for sorting by y
int cmp_y(const void *a, const void *b) {
    int idx1 = *(int*)a;
    int idx2 = *(int*)b;
    if (points[idx1].y != points[idx2].y)
        return points[idx1].y - points[idx2].y;
    return points[idx1].x - points[idx2].x;
}

long long dfs(int num_points, int sorted_x[], int sorted_y[], int current_k) {
    // Base case
    if(current_k ==1){
        int min_x = points[sorted_x[0]].x;
        int max_x = points[sorted_x[num_points-1]].x;
        int min_y = points[sorted_y[0]].y;
        int max_y = points[sorted_y[num_points-1]].y;
        for(int i=1;i<num_points;i++) {
            if(points[sorted_x[i]].y < min_y) min_y = points[sorted_x[i]].y;
            if(points[sorted_x[i]].y > max_y) max_y = points[sorted_x[i]].y;
        }
        if(min_x == max_x || min_y == max_y)
            return 0;
        return (long long)(max_x - min_x) * (max_y - min_y);
    }

    long long min_sum = LLONG_MAX;

    // Try vertical splits
    for(int i=1;i<num_points;i++) {
        int left_max_x = points[sorted_x[i-1]].x;
        int right_min_x = points[sorted_x[i]].x;
        if(left_max_x < right_min_x){
            // Split sorted_x into left and right
            int left_num = i;
            int right_num = num_points -i;
            int left_sorted_x[50], right_sorted_x[50];
            for(int a=0;a<left_num;a++) left_sorted_x[a] = sorted_x[a];
            for(int a=0;a<right_num;a++) right_sorted_x[a] = sorted_x[i+a];
            // Split sorted_y into left and right based on x
            int left_sorted_y[50], right_sorted_y_arr[50];
            int left_y =0, right_y =0;
            for(int a=0;a<num_points;a++) {
                if(points[sorted_y[a]].x < right_min_x){
                    left_sorted_y[left_y++] = sorted_y[a];
                }
                else{
                    right_sorted_y_arr[right_y++] = sorted_y[a];
                }
            }
            // Distribute k
            for(int kk=1; kk < current_k; kk++) {
                long long left_cost = dfs(left_num, left_sorted_x, left_sorted_y, kk);
                long long right_cost = dfs(right_num, right_sorted_x, right_sorted_y_arr, current_k - kk);
                if(left_cost + right_cost < min_sum)
                    min_sum = left_cost + right_cost;
            }
        }
    }

    // Try horizontal splits
    for(int i=1;i<num_points;i++) {
        int left_max_y = points[sorted_y[i-1]].y;
        int right_min_y = points[sorted_y[i]].y;
        if(left_max_y < right_min_y){
            // Split sorted_y into bottom and top
            int bottom_num = i;
            int top_num = num_points -i;
            int bottom_sorted_y[50], top_sorted_y[50];
            for(int a=0;a<bottom_num;a++) bottom_sorted_y[a] = sorted_y[a];
            for(int a=0;a<top_num;a++) top_sorted_y[a] = sorted_y[i+a];
            // Split sorted_x into bottom and top based on y
            int bottom_sorted_x[50], top_sorted_x[50];
            int bottom_x =0, top_x =0;
            for(int a=0;a<num_points;a++) {
                if(points[sorted_x[a]].y < right_min_y){
                    bottom_sorted_x[bottom_x++] = sorted_x[a];
                }
                else{
                    top_sorted_x[top_x++] = sorted_x[a];
                }
            }
            // Distribute k
            for(int kk=1; kk < current_k; kk++) {
                long long bottom_cost = dfs(bottom_x, bottom_sorted_x, bottom_sorted_y, kk);
                long long top_cost = dfs(top_x, top_sorted_x, top_sorted_y, current_k - kk);
                if(bottom_cost + top_cost < min_sum)
                    min_sum = bottom_cost + top_cost;
            }
        }
    }

    return min_sum;
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i=0;i<n;i++) scanf("%d %d", &points[i].x, &points[i].y);
    
    // Initialize sorted_x and sorted_y
    int sorted_x[50], sorted_y[50];
    for(int i=0;i<n;i++) { sorted_x[i] = i; sorted_y[i] = i; }
    qsort(sorted_x, n, sizeof(int), cmp_x);
    qsort(sorted_y, n, sizeof(int), cmp_y);
    
    long long result = dfs(n, sorted_x, sorted_y, k);
    printf("%lld\n", result);
    return 0;
}