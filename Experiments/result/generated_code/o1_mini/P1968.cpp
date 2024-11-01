#include<stdio.h>

int main(){
    int N;
    scanf("%d", &N);
    double usd=100.0, dem=0.0, A, temp_usd, temp_dem;
    for(int i=1;i<=N;i++){
        scanf("%lf", &A);
        if(i < N){
            temp_usd = usd > (dem / A) * 100.0 ? usd : (dem / A) * 100.0;
            temp_dem = dem > (usd / 100.0) * A ? dem : (usd / 100.0) * A;
            usd = temp_usd;
            dem = temp_dem;
        }
        else{
            temp_usd = usd > (dem / A) * 100.0 ? usd : (dem / A) * 100.0;
            usd = temp_usd;
        }
    }
    printf("%.2lf\n", usd);
}