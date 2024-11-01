#include <stdio.h>
#include <math.h>

int main(){
    int counts[32769] = {0};
    // Precompute counts
    for(int a=0; a<=181; a++){
        int a_sq = a*a;
        if(a_sq >32768) break;
        for(int b=a; b<=181; b++){
            int b_sq = b*b;
            if(a_sq + b_sq >32768) break;
            for(int c=b; c<=181; c++){
                int c_sq = c*c;
                if(a_sq + b_sq +c_sq >32768) break;
                // Compute d_max
                int rem = 32768 - a_sq - b_sq -c_sq;
                int d_max = (int)sqrt(rem);
                if(d_max <c) continue;
                if(d_max >181) d_max=181;
                for(int d=c; d<=d_max; d++){
                    int sum =a_sq + b_sq +c_sq + d*d;
                    if(sum >32768) break;
                    counts[sum]++;
                }
            }
        }
    }
    // Read test cases
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        if(n >=0 && n <=32768)
            printf("%d\n", counts[n]);
        else
            printf("0\n");
    }
}