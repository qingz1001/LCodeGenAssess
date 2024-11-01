#include <stdio.h>
#include <math.h>

typedef struct {
    double a;
    double b;
    double c;
} Quadratic;

double F(double x, Quadratic* funcs, int n) {
    double max_val = -1e18;
    for(int i = 0; i < n; i++) {
        double val = funcs[i].a * x * x + funcs[i].b * x + funcs[i].c;
        if(val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        Quadratic funcs[n];
        for(int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &funcs[i].a, &funcs[i].b, &funcs[i].c);
        }
        double left = 0.0, right = 1000.0;
        for(int iter = 0; iter < 100; iter++) {
            double m1 = left + (right - left) / 3.0;
            double m2 = right - (right - left) / 3.0;
            double f1 = F(m1, funcs, n);
            double f2 = F(m2, funcs, n);
            if(f1 < f2){
                right = m2;
            }
            else{
                left = m1;
            }
        }
        double res = F((left + right) / 2.0, funcs, n);
        printf("%.4lf\n", res);
    }
    return 0;
}