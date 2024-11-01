#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double h;
    double r1;
    double r2;
} Bowl;

int main(){
    int n;
    scanf("%d", &n);
    Bowl bowls[n];
    for(int i=0;i<n;i++) {
        scanf("%lf %lf %lf", &bowls[i].h, &bowls[i].r1, &bowls[i].r2);
    }
    int perm[n];
    for(int i=0;i<n;i++) perm[i]=i;
    double min_height = 1e18;
    // Heap permutations using Heap's algorithm
    int c[n];
    for(int i=0;i<n;i++) c[i]=0;
    int i = 0;
    while(i < n){
        if(c[i] < i){
            if(i%2==0){
                // swap perm[0] and perm[i]
                int temp = perm[0];
                perm[0] = perm[i];
                perm[i] = temp;
            }
            else{
                // swap perm[c[i]] and perm[i]
                int temp = perm[c[i]];
                perm[c[i]] = perm[i];
                perm[i] = temp;
            }
            // Calculate current permutation
            double total = bowls[perm[0]].h;
            for(int j=1;j<n;j++){
                Bowl upper = bowls[perm[j]];
                Bowl lower = bowls[perm[j-1]];
                if(lower.r2 < upper.r1){
                    // No overlap
                }
                double t = 0.0;
                if(lower.r2 >= upper.r1){
                    double denom = ((lower.r2 - lower.r1)/lower.h) + ((upper.r2 - upper.r1)/upper.h);
                    if(denom != 0){
                        t = (lower.r2 - upper.r1) / denom;
                        if(t > upper.h) t = upper.h;
                        if(t > lower.h) t = lower.h;
                        if(t < 0) t = 0;
                    }
                }
                total += upper.h - t;
            }
            if(total < min_height){
                min_height = total;
            }
            c[i]++;
            i = 0;
        }
        else{
            c[i]=0;
            i++;
        }
    }
    // Handle the last permutation
    double total = bowls[perm[0]].h;
    for(int j=1;j<n;j++){
        Bowl upper = bowls[perm[j]];
        Bowl lower = bowls[perm[j-1]];
        if(lower.r2 < upper.r1){
            // No overlap
        }
        double t = 0.0;
        if(lower.r2 >= upper.r1){
            double denom = ((lower.r2 - lower.r1)/lower.h) + ((upper.r2 - upper.r1)/upper.h);
            if(denom != 0){
                t = (lower.r2 - upper.r1) / denom;
                if(t > upper.h) t = upper.h;
                if(t > lower.h) t = lower.h;
                if(t < 0) t = 0;
            }
        }
        total += upper.h - t;
    }
    if(total < min_height){
        min_height = total;
    }
    // Round to nearest integer
    int answer = (int)(min_height + 0.5);
    printf("%d", answer);
}