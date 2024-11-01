#include <stdio.h>
#include <math.h>

int main() {
    double distance;
    double max_capacity, fuel_efficiency, initial_fuel_cost;
    int num_gas_stations;
    scanf("%lf %lf %lf %d", &distance, &max_capacity, &initial_fuel_cost, &num_gas_stations);

    double total_cost = initial_fuel_cost;
    double current_fuel = max_capacity;
    double last_station_distance = 0;

    for (int i = 0; i < num_gas_stations; i++) {
        double station_distance, station_price;
        scanf("%lf %lf", &station_distance, &station_price);

        if (current_fuel * fuel_efficiency < station_distance - last_station_distance && current_fuel < max_capacity / 2) {
            total_cost += round(current_fuel * station_price * 10) / 10 + 20;
            current_fuel = max_capacity;
        }

        last_station_distance = station_distance;
    }

    if (current_fuel * fuel_efficiency < distance - last_station_distance && current_fuel < max_capacity / 2) {
        total_cost += round(current_fuel * last_station_distance / fuel_efficiency * station_price * 10) / 10 + 20;
    }

    printf("%.1f\n", total_cost);
    return 0;
}