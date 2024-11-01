#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main(){
    int n, k;
    long long r;
    scanf("%d %d %lld", &n, &k, &r);
    long long x[n];
    for(int i=0;i<n;i++) scanf("%lld", &x[i]);
    int count=0;
    long long last = -1e18;
    for(int i=0;i<n && count <k;i++){
        if(x[i] - last >= 2*r){
            count++;
            last = x[i];
        }
    }
    double area = count * PI * r * r;
    printf("%.10lf\n", area);
    return 0;
}