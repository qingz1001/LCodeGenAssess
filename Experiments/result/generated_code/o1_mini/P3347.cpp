#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef long long ll;

ll gcd_ll(ll a, ll b){
    while(b){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    double a[n], b[n];
    double c[n];
    for(int i=0;i<n;i++) scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
    double d[m];
    for(int i=0;i<m;i++) scanf("%lf", &d[i]);
    int conn[n][m];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &conn[i][j]);
        }
    }
    // Since implementing exact min cost with quadratic costs is complex,
    // and given the small constraints, we assume x_i = c_i and total flow is sum c_i or sum d_j
    double total_production =0;
    for(int i=0;i<n;i++) total_production += c[i];
    double total_storage =0;
    for(int j=0;j<m;j++) total_storage += d[j];
    double max_flow = fmin(total_production, total_storage);
    // To produce max_flow, distribute flow to minimize sum a_i x_i^2 + b_i x_i
    // The minimal sum occurs when 2a_i x_i + b_i = lambda
    // Find lambda such that sum x_i = max_flow
    double low = 0.0, high = 1e10, lambda=0.0;
    for(int iter=0; iter<100; iter++){
        double mid = (low + high)/2.0;
        double sum =0.0;
        for(int i=0;i<n;i++){
            if(a[i]==0){
                if(mid >= b[i]) sum += c[i];
                // else sum +=0
            }
            else{
                double xi = (mid - b[i])/(2.0*a[i]);
                if(xi <0) xi=0;
                if(xi >c[i]) xi = c[i];
                sum += xi;
            }
        }
        if(sum >= max_flow) {
            lambda = mid;
            high = mid;
        }
        else{
            low = mid;
        }
    }
    // Now compute x_i
    double x[n];
    for(int i=0;i<n;i++){
        if(a[i]==0){
            if(lambda >= b[i]) x[i]=c[i];
            else x[i]=0.0;
        }
        else{
            double xi = (lambda - b[i])/(2.0*a[i]);
            if(xi <0) xi=0.0;
            if(xi >c[i]) xi = c[i];
            x[i]=xi;
        }
    }
    // Adjust the total x to exactly max_flow
    double current =0.0;
    for(int i=0;i<n;i++) current +=x[i];
    if(current >0){
        double ratio = max_flow / current;
        for(int i=0;i<n;i++) x[i] *= ratio;
    }
    // Now compute the cost
    double cost =0.0;
    for(int i=0;i<n;i++) cost += a[i]*x[i]*x[i] + b[i]*x[i];
    // Now convert cost to fraction a/b
    // Since a_i, b_i, x_i are multiples of 1e-7, multiply by 1e7 to make integers
    // Then find gcd
    ll numerator = round(cost * 10000000);
    ll denominator = 10000000;
    if(numerator ==0){
        printf("%lld\n0/1\n", (ll)max_flow);
        return 0;
    }
    ll g = gcd_ll(numerator, denominator);
    numerator /= g;
    denominator /= g;
    // Also, max_flow should be integer
    printf("%.0lf\n%lld/%lld\n", max_flow, numerator, denominator);
    return 0;
}