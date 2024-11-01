#include <stdio.h>
#include <math.h>

int main() {
    double distance, max_capacity, km_per_liter, initial_cost;
    int num_gas_stations;
    scanf("%lf %lf %lf %d", &distance, &max_capacity, &km_per_liter, &num_gas_stations);

    double stations_distance[num_gas_stations];
    double stations_price[num_gas_stations];
    for (int i = 0; i < num_gas_stations; i++) {
        scanf("%lf %lf", &stations_distance[i], &stations_price[i]);
    }

    double current_fuel = max_capacity;
    double total_cost = initial_cost;
    int current_station = 0;

    while (current_station < num_gas_stations) {
        // Calculate the distance to the next station or destination
        double next_station_distance = (current_station < num_gas_stations - 1) ? stations_distance[current_station + 1] : distance;
        double distance_to_next_station = next_station_distance - stations_distance[current_station];

        // Check if we can reach the next station or destination with the current fuel
        if (current_fuel * km_per_liter < distance_to_next_station) {
            // Calculate how much more fuel is needed to reach the next station or destination
            double fuel_needed = ceil(distance_to_next_station / km_per_liter) - current_fuel;
            current_fuel += fuel_needed;

            // Calculate the cost of adding fuel
            double cost_of_fuel = fuel_needed * stations_price[current_station];
            total_cost += cost_of_fuel;

            // Add the cost of food
            total_cost += 20;
        }

        // Move to the next station
        current_station++;
    }

    // Check if we can reach the destination with the current fuel
    if (current_fuel * km_per_liter < distance - stations_distance[num_gas_stations - 1]) {
        // Calculate how much more fuel is needed to reach the destination
        double fuel_needed = ceil((distance - stations_distance[num_gas_stations - 1]) / km_per_liter) - current_fuel;
        current_fuel += fuel_needed;

        // Calculate the cost of adding fuel
        double cost_of_fuel = fuel_needed * stations_price[num_gas_stations - 1];
        total_cost += cost_of_fuel;

        // Add the cost of food
        total_cost += 20;
    }

    // Round the total cost to the nearest 0.1
    total_cost = round(total_cost * 10) / 10;

    printf("%.1lf\n", total_cost);
    return 0;
}