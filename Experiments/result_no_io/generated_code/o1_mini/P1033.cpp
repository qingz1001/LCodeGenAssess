#include <stdio.h>
#include <math.h>

int main(){
    double H, S1, V, L, K;
    long long n;
    scanf("%lf %lf %lf %lf %lf %lld", &H, &S1, &V, &L, &K, &n);
    double t_hit = sqrt(2.0 * H / 10.0);
    long long count = 0;
    for(long long i=0;i<n;i++){
        double t_min = (i - S1 - 0.0001) / V;
        double t_max = (i - S1 + L + 0.0001) / V;
        if(t_min < 0) t_min = 0.0;
        if(t_max > t_hit) t_max = t_hit;
        if(t_min <= t_max){
            count++;
        }
    }
    printf("%lld", count);
    return 0;
}