#include <stdio.h>
#include <math.h>

#define MAX_STATIONS 50

typedef struct {
    double distance;
    double price;
} Station;

double min_cost(double distance, double tank_capacity, double km_per_liter, 
                double start_price, int num_stations, Station stations[]) {
    double current_fuel = tank_capacity;
    double total_cost = tank_capacity * start_price;
    double current_position = 0;
    int current_station = 0;

    while (current_position < distance) {
        double max_distance = current_position + current_fuel * km_per_liter;
        
        if (max_distance >= distance) {
            return total_cost;
        }

        int next_station = -1;
        double min_price = 1e9;
        
        for (int i = current_station; i < num_stations; i++) {
            if (stations[i].distance > max_distance) break;
            
            if (stations[i].price < min_price) {
                min_price = stations[i].price;
                next_station = i;
            }
        }

        if (next_station == -1) {
            return -1; // Impossible to reach destination
        }

        double fuel_needed = (stations[next_station].distance - current_position) / km_per_liter;
        
        if (current_fuel >= fuel_needed + tank_capacity / 2) {
            current_fuel -= fuel_needed;
        } else {
            total_cost += (tank_capacity - current_fuel) * stations[next_station].price;
            current_fuel = tank_capacity - fuel_needed;
            total_cost += 20; // Cost for food
        }

        current_position = stations[next_station].distance;
        current_station = next_station + 1;
    }

    return total_cost;
}

int main() {
    double distance, tank_capacity, km_per_liter, start_price;
    int num_stations;
    Station stations[MAX_STATIONS];

    scanf("%lf", &distance);
    scanf("%lf %lf %lf %d", &tank_capacity, &km_per_liter, &start_price, &num_stations);

    for (int i = 0; i < num_stations; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }

    double result = min_cost(distance, tank_capacity, km_per_liter, start_price, num_stations, stations);
    
    if (result == -1) {
        printf("Impossible to reach destination\n");
    } else {
        printf("%.1f\n", round(result * 10) / 10);
    }

    return 0;
}