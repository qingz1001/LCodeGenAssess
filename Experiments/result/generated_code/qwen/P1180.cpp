#include <stdio.h>
#include <math.h>

int main() {
    double distance, max_capacity, fuel_efficiency, start_cost;
    int n, i;
    scanf("%lf %lf %lf %d", &distance, &max_capacity, &fuel_efficiency, &n);
    
    double prev_distance = 0;
    double total_cost = start_cost;
    double current_fuel = max_capacity;
    
    for (i = 0; i < n; i++) {
        double current_distance, price_per_liter;
        scanf("%lf %lf", &current_distance, &price_per_liter);
        
        double required_fuel = (current_distance - prev_distance) / fuel_efficiency;
        if (required_fuel > current_fuel || current_fuel <= max_capacity / 2) {
            total_cost += round((current_fuel * price_per_liter + 20) * 10) / 10;
            current_fuel = max_capacity;
        }
        current_fuel -= required_fuel;
        prev_distance = current_distance;
    }
    
    double final_required_fuel = (distance - prev_distance) / fuel_efficiency;
    if (final_required_fuel > current_fuel || current_fuel <= max_capacity / 2) {
        total_cost += round((current_fuel * price_per_liter + 20) * 10) / 10;
    }
    
    printf("%.1f\n", total_cost);
    return 0;
}