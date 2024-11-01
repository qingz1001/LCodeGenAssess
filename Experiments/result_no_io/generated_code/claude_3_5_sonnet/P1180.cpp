#include <stdio.h>
#include <math.h>

#define MAX_STATIONS 50

int main() {
    double distance, tank_capacity, km_per_liter, start_price;
    int num_stations;
    double station_distances[MAX_STATIONS], station_prices[MAX_STATIONS];
    
    scanf("%lf", &distance);
    scanf("%lf %lf %lf %d", &tank_capacity, &km_per_liter, &start_price, &num_stations);
    
    for (int i = 0; i < num_stations; i++) {
        scanf("%lf %lf", &station_distances[i], &station_prices[i]);
    }
    
    double current_fuel = tank_capacity;
    double total_cost = start_price;
    double current_position = 0;
    
    for (int i = 0; i <= num_stations; i++) {
        double next_distance = (i == num_stations) ? distance : station_distances[i];
        double fuel_needed = (next_distance - current_position) / km_per_liter;
        
        if (fuel_needed > current_fuel) {
            double fuel_to_add = tank_capacity - current_fuel;
            current_fuel = tank_capacity;
            total_cost += fuel_to_add * station_prices[i-1] + 20;
            total_cost = round(total_cost * 10) / 10;
        }
        
        current_fuel -= fuel_needed;
        current_position = next_distance;
        
        if (i < num_stations && current_fuel < tank_capacity / 2 && 
            current_fuel < (station_distances[i+1] - current_position) / km_per_liter) {
            double fuel_to_add = tank_capacity - current_fuel;
            current_fuel = tank_capacity;
            total_cost += fuel_to_add * station_prices[i] + 20;
            total_cost = round(total_cost * 10) / 10;
        }
        
        if (current_position == distance) break;
    }
    
    printf("%.1f\n", total_cost);
    
    return 0;
}