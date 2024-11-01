#include <stdio.h>
#include <math.h>

int main(){
    double d_total;
    scanf("%lf", &d_total);
    
    double C, e, F;
    int n;
    scanf("%lf %lf %lf %d", &C, &e, &F, &n);
    
    double d[52];
    double p[52];
    
    for(int i=1;i<=n;i++){
        scanf("%lf %lf", &d[i], &p[i]);
    }
    // Add destination as station n+1
    d[n+1] = d_total;
    p[n+1] = 0.0;
    n = n +1;
    
    double current_fuel = C;
    double total_cost = F;
    int first_stop = 1;
    
    double prev_d = 0.0;
    
    for(int i=1;i<=n;i++){
        double distance = d[i] - prev_d;
        double fuel_consumed = distance / e;
        current_fuel -= fuel_consumed;
        
        prev_d = d[i];
        
        if(i > n) continue;
        
        if(i == n){
            // Destination, no need to decide to stop
            continue;
        }
        
        double next_distance = d[i+1] - d[i];
        double fuel_needed = next_distance / e;
        
        if(current_fuel < fuel_needed || current_fuel < C / 2.0){
            double additional_fuel;
            if(first_stop){
                additional_fuel = C - current_fuel;
                total_cost += additional_fuel * p[i] + 20.0;
                current_fuel = C;
                first_stop = 0;
            }
            else{
                double target_fuel;
                if(fuel_needed > C / 2.0){
                    target_fuel = fuel_needed;
                }
                else{
                    target_fuel = C / 2.0;
                }
                additional_fuel = target_fuel - current_fuel;
                if(additional_fuel < 0){
                    additional_fuel = 0.0;
                }
                total_cost += additional_fuel * p[i] + 20.0;
                current_fuel += additional_fuel;
            }
        }
    }
    
    // Round to nearest 0.1
    total_cost = floor(total_cost * 10.0 + 0.5) / 10.0;
    printf("%.1lf\n", total_cost);
    
    return 0;
}