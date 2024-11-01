#include <stdio.h>

int main(){
    int n;
    scanf("%d", &n);
    long long x[1001], y[1001];
    double w[1001];
    double min_y = 100000.0;
    for(int i=0;i<n;i++){
        scanf("%lld %lld %lf", &x[i], &y[i], &w[i]);
        if(y[i] < min_y){
            min_y = y[i];
        }
    }
    double sum_w = 0.0, sum_wx = 0.0;
    for(int i=0;i<n;i++){
        if(y[i] == min_y){
            sum_w += w[i];
            sum_wx += w[i]*x[i];
        }
    }
    double X = sum_wx / sum_w;
    double Y = min_y;
    printf("%.3lf %.3lf\n", X, Y);
}