#include <stdio.h>
#include <math.h>

int main(){
    long long w0, w;
    int m;
    scanf("%lld %lld %d", &w0, &w, &m);
    double left = 0.0, right = 3.0;
    double target = (double)w0;
    double r = 0.0;
    for(int i=0;i<100;i++){
        double mid = (left + right)/2.0;
        double pow_val = pow(1.0 + mid, m);
        double pv;
        if(mid < 1e-10){
            pv = w * m;
        }
        else{
            pv = w * (1.0 - 1.0 / pow_val) / mid;
        }
        if(pv > target){
            left = mid;
        }
        else{
            right = mid;
        }
    }
    r = right;
    double r_percent = r * 100.0;
    r_percent = floor(r_percent * 10.0 + 0.5) / 10.0;
    printf("%.1lf\n", r_percent);
}