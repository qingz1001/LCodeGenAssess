#include <stdio.h>
#include <math.h>

int main(){
    double H, S1, V, L, K;
    int n;
    scanf("%lf %lf %lf %lf %lf %d", &H, &S1, &V, &L, &K, &n);
    
    double g = 10.0;
    double t_hit = sqrt(2.0 * H / g);
    double t_catch;
    if(H > K + 1e-4){
        t_catch = sqrt(2.0 * (H - K - 1e-4) / g);
    }
    else{
        t_catch = 0.0;
    }
    
    int count =0;
    for(int x=0; x<n; x++){
        double t_start = (S1 - x) / V;
        double t_end = (S1 - x - L) / V;
        
        if(t_start < 0 && t_end < 0){
            continue;
        }
        
        if(t_end <0){
            t_end =0.0;
        }
        
        if(t_start <0){
            t_start =0.0;
        }
        
        double t_accept = t_catch > t_end ? t_catch : t_end;
        
        if(t_accept <= t_start && t_accept <= t_hit){
            double y = H - 0.5 * g * t_accept * t_accept;
            if(y <= K + 1e-4){
                count++;
            }
        }
    }
    
    printf("%d\n", count);
    return 0;
}