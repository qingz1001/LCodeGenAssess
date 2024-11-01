#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STATIONS 50

typedef struct {
    double distance;
    double price;
} Station;

int compareStations(const void *a, const void *b) {
    Station *stationA = (Station *)a;
    Station *stationB = (Station *)b;
    return (stationA->distance > stationB->distance) - (stationA->distance < stationB->distance);
}

double calculateMinCost(double totalDistance, double tankCapacity, double mileage, double initialCost, int numStations, Station stations[]) {
    double currentFuel = tankCapacity; // Start with a full tank
    double totalCost = initialCost; // Initial cost to fill the tank
    double currentDistance = 0.0;
    double maxDistance = tankCapacity * mileage;

    for (int i = 0; i < numStations; i++) {
        double distanceToNextStation = (i < numStations - 1) ? stations[i + 1].distance : totalDistance;
        double distanceToCurrentStation = stations[i].distance - currentDistance;

        if (distanceToCurrentStation > maxDistance) {
            return -1; // Cannot reach the next station
        }

        currentFuel -= distanceToCurrentStation / mileage;
        currentDistance = stations[i].distance;

        if (currentFuel < tankCapacity / 2 || distanceToNextStation > currentFuel * mileage) {
            double fuelNeeded = tankCapacity - currentFuel;
            double costAtStation = fuelNeeded * stations[i].price + 20.0; // Include the cost of food
            totalCost += costAtStation;
            currentFuel = tankCapacity; // Refill the tank
        }
    }

    return round(totalCost * 10) / 10;
}

int main() {
    double totalDistance;
    double tankCapacity, mileage, initialCost;
    int numStations;
    Station stations[MAX_STATIONS];

    scanf("%lf", &totalDistance);
    scanf("%lf %lf %lf %d", &tankCapacity, &mileage, &initialCost, &numStations);

    for (int i = 0; i < numStations; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }

    qsort(stations, numStations, sizeof(Station), compareStations);

    double minCost = calculateMinCost(totalDistance, tankCapacity, mileage, initialCost, numStations, stations);

    if (minCost < 0) {
        printf("Cannot reach destination\n");
    } else {
        printf("%.1f\n", minCost);
    }

    return 0;
}