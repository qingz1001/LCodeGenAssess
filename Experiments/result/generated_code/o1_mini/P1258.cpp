#include <stdio.h>

int main(){
    double s, a, b, t;
    scanf("%lf %lf %lf", &s, &a, &b);
    if(b > a && b > 0){
        t = 2.0 * s / b;
    }
    else{
        if(a > 0){
            t = s / a;
        }
        else{
            t = 0.0;
        }
    }
    printf("%.6lf\n", t);
    return 0;
}