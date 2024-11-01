#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double h;
    double r1;
    double r2;
    double slope;
} Bowl;

int n;
Bowl bowls[10];
int used[10];
int perm[10];
double min_height = 1e18;

double compute_overlap(Bowl a, Bowl b){
    // Slope of bowl a and b
    double slopeA = a.slope;
    double slopeB = b.slope;
    
    double numerator = a.r2 - b.r1 - (slopeA + slopeB) * b.h;
    if(numerator < 0){
        return 0.0;
    }
    double x_max = numerator / slopeA;
    if(x_max > b.h){
        x_max = b.h;
    }
    if(x_max < 0){
        return 0.0;
    }
    return x_max;
}

void backtrack(int depth, double current_sum, double overlap_sum){
    if(depth == n){
        double total = current_sum - overlap_sum;
        if(total < min_height){
            min_height = total;
        }
        return;
    }
    for(int i=0;i<n;i++){
        if(!used[i]){
            used[i] = 1;
            perm[depth] = i;
            double new_sum = current_sum + bowls[i].h;
            double new_overlap = overlap_sum;
            if(depth > 0){
                Bowl below = bowls[perm[depth-1]];
                Bowl above = bowls[i];
                double overlap = compute_overlap(below, above);
                new_overlap += overlap;
            }
            backtrack(depth+1, new_sum, new_overlap);
            used[i] = 0;
        }
    }
}

int main(){
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        int h, r1, r2;
        scanf("%d %d %d", &h, &r1, &r2);
        bowls[i].h = (double)h;
        bowls[i].r1 = (double)r1;
        bowls[i].r2 = (double)r2;
        bowls[i].slope = (bowls[i].r2 - bowls[i].r1) / bowls[i].h;
    }
    backtrack(0, 0.0, 0.0);
    double result = min_height;
    result = floor(result + 0.5);
    printf("%.0lf", result);
    return 0;
}