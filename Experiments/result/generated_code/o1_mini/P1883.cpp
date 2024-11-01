#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double a, b, c;
} Func;

double get_Fx(Func arr[], int n, double x){
    double max_f = arr[0].a *x*x + arr[0].b*x + arr[0].c;
    for(int i=1;i<n;i++){
        double val = arr[i].a *x*x + arr[i].b*x + arr[i].c;
        if(val > max_f){
            max_f = val;
        }
    }
    return max_f;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int n;
        scanf("%d", &n);
        Func *arr = (Func*)malloc(sizeof(Func)*n);
        for(int i=0;i<n;i++){
            scanf("%lf %lf %lf", &arr[i].a, &arr[i].b, &arr[i].c);
        }
        double low = 0.0, high = 1000.0, eps = 1e-8;
        for(int iter=0; iter < 100; iter++){
            double m1 = low + (high - low)/3.0;
            double m2 = high - (high - low)/3.0;
            double f1 = get_Fx(arr, n, m1);
            double f2 = get_Fx(arr, n, m2);
            if(f1 < f2){
                high = m2;
            }
            else{
                low = m1;
            }
        }
        double candidates[102];
        int cnt = 0;
        candidates[cnt++] = low;
        candidates[cnt++] = high;
        candidates[cnt++] = 0.0;
        candidates[cnt++] = 1000.0;
        double min_F = 1e18;
        for(int i=0;i<cnt;i++){
            double fx = get_Fx(arr, n, candidates[i]);
            if(fx < min_F){
                min_F = fx;
            }
        }
        printf("%.4lf\n", min_F);
        free(arr);
    }
    return 0;
}