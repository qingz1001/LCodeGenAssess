#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Point;

int N;
Point rect[2];
Point points[6];
double min_remaining = 1e18;

// Function to calculate distance between two points
double distance(Point a, Point b){
    double dx = (double)(a.x - b.x);
    double dy = (double)(a.y - b.y);
    return sqrt(dx*dx + dy*dy);
}

// Function to generate permutations using Heap's algorithm
void generate_permutations(int n, int *perm, int size, Point placed[6], double total_area, double rect_area){
    if(n == 1){
        // Calculate remaining area
        double remaining = rect_area - total_area;
        if(remaining < min_remaining){
            min_remaining = remaining;
        }
        return;
    }
    for(int i=0;i<n;i++){
        generate_permutations(n-1, perm, size, placed, total_area, rect_area);
        if(n %2 ==1){
            // swap first and last
            Point temp = placed[0];
            placed[0] = placed[n-1];
            placed[n-1] = temp;
        }
        else{
            // swap i and last
            Point temp = placed[i];
            placed[i] = placed[n-1];
            placed[n-1] = temp;
        }
    }
}

int main(){
    scanf("%d", &N);
    scanf("%d %d %d %d", &rect[0].x, &rect[0].y, &rect[1].x, &rect[1].y);
    for(int i=0;i<N;i++) scanf("%d %d", &points[i].x, &points[i].y);
    
    // Determine rectangle boundaries
    int x_min = rect[0].x < rect[1].x ? rect[0].x : rect[1].x;
    int x_max = rect[0].x > rect[1].x ? rect[0].x : rect[1].x;
    int y_min = rect[0].y < rect[1].y ? rect[0].y : rect[1].y;
    int y_max = rect[0].y > rect[1].y ? rect[0].y : rect[1].y;
    
    // Calculate rectangle area
    double rect_area = (double)(x_max - x_min) * (double)(y_max - y_min);
    
    // Initialize permutation
    int perm[6];
    for(int i=0;i<N;i++) perm[i] = i;
    
    // Function to recursively generate and evaluate permutations
    double process(int n, int *perm, Point placed[6], double total_area){
        if(n == N){
            if(total_area < min_remaining){
                min_remaining = total_area;
            }
            return 0;
        }
        double local_min = 1e18;
        for(int i=n;i<N;i++){
            // Swap
            int temp = perm[n];
            perm[n] = perm[i];
            perm[i] = temp;
            
            // Place the nth drop
            Point current = points[perm[n]];
            // Maximum radius by borders
            double r = fmin(current.x - x_min, x_max - current.x);
            r = fmin(r, (double)(current.y - y_min));
            r = fmin(r, (double)(y_max - current.y));
            // Check with existing drops
            for(int j=0;j<n;j++){
                double dist = distance(current, placed[j]);
                double temp_r = dist - 0.0; // radii not yet determined
                r = fmin(r, dist);
            }
            // Place the drop with radius r
            placed[n].x = current.x;
            placed[n].y = current.y;
            double new_total = total_area + M_PI * r * r;
            // Recurse
            double res = process(n+1, perm, placed, new_total);
            if(res < local_min){
                local_min = res;
            }
            // Swap back
            temp = perm[n];
            perm[n] = perm[i];
            perm[i] = temp;
        }
        return local_min;
    }
    
    // Since N is small, use permutation generation and evaluate each
    // Implemented via recursion
    // Initialize placed and total_area
    Point placed[6];
    double total_area = 0.0;
    
    // Function to generate all permutations and evaluate
    // Using Heap's algorithm inline
    void heap_permute(int k, int n, int *arr, Point placed_local[6], double total_area_local){
        if(k == 1){
            // Evaluate this permutation
            Point current_placed[6];
            double current_total = 0.0;
            for(int i=0;i<N;i++){
                Point p = points[arr[i]];
                double r = fmin(p.x - x_min, x_max - p.x);
                r = fmin(r, (double)(p.y - y_min));
                r = fmin(r, (double)(y_max - p.y));
                for(int j=0;j<i;j++){
                    double dist = distance(p, current_placed[j]);
                    r = fmin(r, dist);
                }
                current_placed[i] = p;
                current_total += M_PI * r * r;
            }
            double remaining = rect_area - current_total;
            if(remaining < min_remaining){
                min_remaining = remaining;
            }
            return;
        }
        for(int i=0;i<k;i++){
            heap_permute(k-1, n, arr, placed_local, total_area_local);
            if(k%2 ==1){
                int temp = arr[0];
                arr[0] = arr[k-1];
                arr[k-1] = temp;
            }
            else{
                int temp = arr[i];
                arr[i] = arr[k-1];
                arr[k-1] = temp;
            }
        }
    }
    
    heap_permute(N, N, perm, placed, total_area);
    
    // Output the minimal remaining area, rounded
    double result = rect_area - min_remaining;
    double final_remaining = rect_area - (rect_area - min_remaining);
    double remaining_area = min_remaining;
    long long rounded = round(remaining_area);
    printf("%lld\n", rounded);
    
    return 0;
}