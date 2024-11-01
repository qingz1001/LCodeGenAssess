#include <stdio.h>
#include <math.h>

int main(){
    long long a, b;
    scanf("%lld %lld", &a, &b);
    if(a > b){
        long long temp = a;
        a = b;
        b = temp;
    }
    if(a == 0 && b == 0){
        printf("0");
        return 0;
    }
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    double kphi_d = a * phi;
    long long kphi = (long long)(floor(kphi_d + 1e-9));
    if(b == a + kphi){
        printf("0");
    }
    else{
        printf("1");
    }
}