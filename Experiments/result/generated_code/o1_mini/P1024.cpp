#include <stdio.h>
#include <math.h>

double f(double a, double b, double c, double d, double x){
    return a*x*x*x + b*x*x + c*x + d;
}

double find_root(double a, double b, double c, double d, double left, double right){
    double mid, f_mid;
    while (right - left > 1e-7){
        mid = (left + right) / 2.0;
        f_mid = f(a, b, c, d, mid);
        if (f(a, b, c, d, left) * f_mid <= 0){
            right = mid;
        }
        else{
            left = mid;
        }
    }
    return (left + right) / 2.0;
}

int main(){
    double a, b, c, d;
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    double roots[3];
    int count = 0;
    double step = 0.001;
    double prev = -100.0;
    double f_prev = f(a, b, c, d, prev);
    for(double x = -100.0 + step; x <= 100.0 && count < 3; x += step){
        double f_curr = f(a, b, c, d, x);
        if(f_prev * f_curr <= 0){
            double root = find_root(a, b, c, d, prev, x);
            int duplicate = 0;
            for(int i=0;i<count;i++) {
                if(fabs(root - roots[i]) < 1e-4){
                    duplicate = 1;
                    break;
                }
            }
            if(!duplicate){
                roots[count++] = root;
            }
        }
        prev = x;
        f_prev = f_curr;
    }
    // Simple bubble sort
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(roots[j] > roots[j+1]){
                double temp = roots[j];
                roots[j] = roots[j+1];
                roots[j+1] = temp;
            }
        }
    }
    printf("%.2lf %.2lf %.2lf\n", roots[0], roots[1], roots[2]);
    return 0;
}