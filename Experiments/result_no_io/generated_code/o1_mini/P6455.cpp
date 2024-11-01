#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 100005

long long n, k;
double r, L;
double p[MAX_N];
int selected[MAX_N];

// Comparator for qsort
int cmp_double(const void *a, const void *b){
    double diff = (*(double*)a - *(double*)b);
    if(diff < 0) return -1;
    else if(diff >0) return 1;
    else return 0;
}

// Check if it's possible to select at least k points with minimal distance d
int is_possible(double d){
    int count =1;
    int last =0;
    for(long long i=1;i<n;i++){
        double diff = p[i] - p[last];
        if(diff >=d){
            count++;
            last =i;
            if(count >=k) return 1;
        }
    }
    // Check wrap around
    if((p[0] + L - p[last]) >=d){
        count++;
    }
    return count >=k;
}

int main(){
    // Read input
    if(scanf("%lld %lld %lf %lf", &n, &k, &r, &L)!=4){
        return 0;
    }
    for(long long i=0;i<n;i++){
        if(scanf("%lf", &p[i])!=1){
            return 0;
        }
    }
    // Sort p just in case
    qsort(p, n, sizeof(double), cmp_double);
    // Binary search for the maximum minimal distance
    double left=0.0, right=L;
    for(int iter=0; iter < 100; iter++){
        double mid = (left + right)/2.0;
        if(is_possible(mid)){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    // Now, left is the maximum minimal distance
    double d = left;
    // Reconstruct the selection
    int count =1;
    selected[0]=0;
    int last =0;
    for(long long i=1;i<n;i++){
        double diff = p[i] - p[last];
        if(diff >=d){
            selected[count++] =i;
            last =i;
            if(count ==k){
                break;
            }
        }
    }
    // If not enough, wrap around
    if(count <k){
        for(long long i=0;i<n && count <k;i++){
            double diff = p[i] + L - p[last];
            if(diff >=d){
                selected[count++] =i;
                last =i;
            }
        }
    }
    // If still not enough, start from the beginning
    // (This condition should not happen due to the binary search)
    // Output the selected indices in 1-based indexing
    for(int i=0;i<k;i++){
        if(i>0) printf(" ");
        printf("%d", selected[i]+1);
    }
    printf("\n");
    return 0;
}