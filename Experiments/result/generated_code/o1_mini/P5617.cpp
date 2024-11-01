#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592653589793238462643383279502884197

typedef long long ll;

int main(){
    int n, k;
    double r;
    scanf("%d %d %lf", &n, &k, &r);
    double *x = (double*)malloc(n * sizeof(double));
    for(int i=0;i<n;i++) scanf("%lf", &x[i]);
    if(k ==0){
        printf("0.0\n");
        return 0;
    }
    if(k ==1){
        printf("%.10lf\n", PI * r * r);
        free(x);
        return 0;
    }
    double step = (x[n-1] - x[0]) / (k -1);
    double *selected = (double*)malloc(k * sizeof(double));
    selected[0] = x[0];
    int current =0;
    for(int i=1;i<k-1;i++){
        double target = x[0] + step * i;
        while(current < n && x[current] < target){
            current++;
        }
        if(current >= n){
            selected[i] = x[n-1];
        }
        else{
            selected[i] = x[current];
            current++;
        }
    }
    selected[k-1] = x[n-1];
    // Now, ensure selected are sorted and unique
    // Compute overlaps
    double sum_overlap =0.0;
    for(int i=1;i<k;i++){
        double d = selected[i] - selected[i-1];
        if(d >= 2.0 * r){
            continue;
        }
        double overlap;
        if(d <=0){
            overlap = PI * r * r;
        }
        else{
            double acos_val = d / (2.0 * r);
            if(acos_val >1.0) acos_val =1.0;
            if(acos_val < -1.0) acos_val = -1.0;
            double term1 = 2.0 * r * r * acos(acos_val);
            double term2 = (d / 2.0) * sqrt(4.0 * r * r - d * d);
            overlap = term1 - term2;
        }
        sum_overlap += overlap;
    }
    double A_union = k * PI * r * r - sum_overlap;
    printf("%.10lf\n", A_union);
    free(x);
    free(selected);
    return 0;
}