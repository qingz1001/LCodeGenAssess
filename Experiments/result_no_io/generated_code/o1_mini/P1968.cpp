#include <stdio.h>
#include <stdlib.h>

int main(){
    int N;
    scanf("%d", &N);
    double A[N];
    for(int i=0;i<N;i++) scanf("%lf", &A[i]);
    double usd = 100.0, dem = 0.0;
    for(int i=0;i<N;i++){
        // Option 1: Do nothing
        double usd1 = usd;
        double dem1 = dem;
        // Option 2: If in USD, buy DEM
        double dem2 = usd / 100.0 * A[i];
        double usd2 = usd;
        // Option 3: If in DEM, buy USD
        double usd3 = dem / A[i] * 100.0;
        double dem3 = dem;
        // Option 4: Do nothing
        double usd4 = usd;
        double dem4 = dem;
        // Take the maximum
        double new_usd = usd1;
        double new_dem = dem1;
        // Compare USD options
        if(usd2 > new_usd) new_usd = usd2;
        if(usd3 > new_usd) new_usd = usd3;
        if(usd4 > new_usd) new_usd = usd4;
        // Compare DEM options
        if(dem2 > new_dem) new_dem = dem2;
        if(dem3 > new_dem) new_dem = dem3;
        if(dem4 > new_dem) new_dem = dem4;
        usd = new_usd;
        dem = new_dem;
    }
    // Convert to USD if in DEM
    if(dem > 0){
        usd = des >=0 ? (dem / A[N-1] * 100.0) : usd;
    }
    printf("%.2lf\n", usd);
    return 0;
}