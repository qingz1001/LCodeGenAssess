#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_STATIONS 50

typedef struct {
    double distance;
    double price;
} GasStation;

double min(double a, double b) {
    return a < b ? a : b;
}

double calculateMinCost(double totalDistance, double tankCapacity, double mileage, double initialCost, int numStations, GasStation stations[]) {
    double currentFuel = tankCapacity; // Start with a full tank
    double totalCost = initialCost; // Initial cost to fill the tank
    double currentPosition = 0.0; // Start from the origin

    for (int i = 0; i < numStations; i++) {
        double distanceToNext = (i < numStations - 1) ? stations[i + 1].distance : totalDistance;
        double distanceToCurrent = stations[i].distance - currentPosition;
        double fuelNeeded = distanceToCurrent / mileage;

        if (currentFuel < fuelNeeded) {
            // Not enough fuel to reach the next station
            return -1; // This should not happen as per problem statement
        }

        currentFuel -= fuelNeeded;
        currentPosition = stations[i].distance;

        if (currentFuel <= tankCapacity / 2) {
            // Refill the tank
            double fuelToFill = tankCapacity - currentFuel;
            double costAtThisStation = fuelToFill * stations[i].price;
            totalCost += costAtThisStation + 20.0; // Add food cost
            currentFuel = tankCapacity; // Tank is full again
        }
    }

    // Check if we can reach the destination from the last station
    double remainingDistance = totalDistance - currentPosition;
    double fuelNeededForRemaining = remainingDistance / mileage;

    if (currentFuel < fuelNeededForRemaining) {
        // Not enough fuel to reach the destination
        return -1; // This should not happen as per problem statement
    }

    return round(totalCost * 10) / 10; // Round to the nearest 0.1
}

int main() {
    double totalDistance;
    double tankCapacity, mileage, initialCost;
    int numStations;
    GasStation stations[MAX_STATIONS];

    scanf("%lf", &totalDistance);
    scanf("%lf %lf %lf %d", &tankCapacity, &mileage, &initialCost, &numStations);

    for (int i = 0; i < numStations; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }

    double result = calculateMinCost(totalDistance, tankCapacity, mileage, initialCost, numStations, stations);
    printf("%.1f\n", result);

    return 0;
}