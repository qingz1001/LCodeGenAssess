#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Fast GCD using binary GCD
int gcd_fast(int a, int b){
    if(a ==0) return b;
    if(b ==0) return a;
    int shift;
    for(shift =0; ((a | b) &1)==0; shift++){
        a >>=1;
        b >>=1;
    }
    while((a &1)==0) a >>=1;
    while((b &1)==0) b >>=1;
    while(a != b){
        if(a > b){
            a = a - b;
            while((a &1)==0) a >>=1;
        }
        else{
            b = b - a;
            while((b &1)==0) b >>=1;
        }
    }
    return a << shift;
}

int main(){
    int M, N;
    scanf("%d %d", &M, &N);
    double R;
    scanf("%lf", &R);
    double min_diff = 1e20;
    int count =0;
    int best_a=0, best_b=1;
    for(int b=1; b<=N; b++){
        double temp = R * b;
        long a_low = floor(temp);
        long a_high = a_low +1;
        for(long a_candidate = a_low; a_candidate <=a_high; a_candidate++){
            if(a_candidate <0 || a_candidate > M){
                continue;
            }
            if(a_candidate ==0 && b !=1){
                continue;
            }
            if(gcd_fast((int)a_candidate, b) !=1){
                continue;
            }
            double frac = (double)a_candidate / b;
            double diff = fabs(R - frac);
            if(diff < min_diff -1e-14){
                min_diff = diff;
                count =1;
                best_a = (int)a_candidate;
                best_b = b;
            }
            else if(fabs(diff - min_diff) <1e-14){
                count +=1;
            }
        }
    }
    if(count ==1){
        printf("%d/%d\n", best_a, best_b);
    }
    else{
        printf("TOO MANY\n");
    }
}