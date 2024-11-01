#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned int gcd_func(unsigned int a, unsigned int b){
    while(b){
        unsigned int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    unsigned int M, N;
    double R;
    scanf("%u %u", &M, &N);
    scanf("%lf", &R);
    double min_diff = 1e20;
    unsigned int best_a = 0, best_b = 1;
    int count = 0;
    for(unsigned int b=1; b<=N; b++){
        double a_f = R * b;
        unsigned int a_low = (unsigned int)floor(a_f);
        unsigned int a_high = a_low +1;
        for(unsigned int a = a_low; a <= a_high; a++){
            if(a > M) continue;
            if(gcd_func(a, b) !=1) continue;
            double diff = fabs((double)a / b - R);
            if(diff < min_diff - 1e-12){
                min_diff = diff;
                best_a = a;
                best_b = b;
                count =1;
            }
            else if(fabs(diff - min_diff) <1e-12){
                count++;
                if(count >1){
                    break;
                }
            }
        }
        if(count >1){
            break;
        }
    }
    if(count ==1){
        if(best_b ==1){
            printf("%u/1\n", best_a);
        }
        else{
            printf("%u/%u\n", best_a, best_b);
        }
    }
    else{
        printf("TOO MANY\n");
    }
    return 0;
}