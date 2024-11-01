#include <stdio.h>

int main(){
    double s, a, b, t;
    scanf("%lf %lf %lf", &s, &a, &b);
    
    if(s == 0){
        t = 0.0;
    }
    else{
        if(b >= a && b > 0){
            t = s / b;
        }
        else if(a > 0){
            t = s / a;
        }
        else{
            t = 0.0; // Undefined scenario, defaulting to 0
        }
    }
    
    printf("%.6lf\n", t);
    return 0;
}