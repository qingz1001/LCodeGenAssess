#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double distance;
    double price;
} Station;

int compare(const void *a, const void *b) {
    Station *stationA = (Station *)a;
    Station *stationB = (Station *)b;
    return (stationA->distance - stationB->distance) < 0 ? -1 : 1;
}

int main() {
    double D1, C, D2, P;
    int N;
    scanf("%lf%lf%lf%lf%d", &D1, &C, &D2, &P, &N);

    Station stations[N + 1];
    stations[0].distance = 0;
    stations[0].price = P;

    for (int i = 1; i <= N; i++) {
        scanf("%lf%lf", &stations[i].distance, &stations[i].price);
    }

    // Add destination station
    stations[N + 1].distance = D1;

    // Sort stations by distance
    qsort(stations, N + 2, sizeof(Station), compare);

    // If the first station is not at distance 0 or the last station is not at distance D1, no solution
    if (stations[0].distance != 0 || stations[N + 1].distance != D1) {
        printf("No Solution\n");
        return 0;
    }

    double currentFuel = 0.0;
    double totalCost = 0.0;
    int currentStation = 0;

    while (currentStation < N + 1) {
        int nextStation = currentStation + 1;
        while (nextStation <= N + 1 && stations[nextStation].distance - stations[currentStation].distance <= C * D2) {
            nextStation++;
        }

        if (nextStation > N + 1) {
            break;
        }

        if (stations[nextStation].price > stations[currentStation].price) {
            double maxDistance = stations[nextStation].distance - stations[currentStation].distance;
            double fuelNeeded = maxDistance / D2;
            if (currentFuel < fuelNeeded) {
                double cost = (fuelNeeded - currentFuel) * stations[currentStation].price;
                totalCost += cost;
                currentFuel = 0;
            } else {
                currentFuel -= fuelNeeded;
            }
        } else {
            double maxDistance = stations[nextStation].distance - stations[currentStation].distance;
            double fuelNeeded = maxDistance / D2;
            if (currentFuel < fuelNeeded) {
                double cost = (C - currentFuel) * stations[currentStation].price;
                totalCost += cost;
                currentFuel = C - fuelNeeded;
            } else {
                currentFuel -= fuelNeeded;
            }
            totalCost += fuelNeeded * stations[nextStation].price;
        }

        currentStation = nextStation;
    }

    if (currentStation < N + 1) {
        printf("No Solution\n");
    } else {
        printf("%.2lf\n", totalCost);
    }

    return 0;
}