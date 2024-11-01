#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 6

typedef struct {
    double distance;
    double price;
} GasStation;

int compare(const void *a, const void *b) {
    return ((GasStation *)a)->distance - ((GasStation *)b)->distance;
}

int main() {
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);

    GasStation stations[MAX_N + 1];
    stations[0].distance = 0;
    stations[0].price = P;

    for (int i = 1; i <= N; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }

    qsort(stations, N + 1, sizeof(GasStation), compare);

    double totalCost = 0.0;
    double currentFuel = 0.0;
    double maxDistance = C * D2;

    for (int i = 0; i <= N; i++) {
        if (i > 0) {
            double distance = stations[i].distance - stations[i - 1].distance;
            if (distance > maxDistance) {
                printf("No Solution\n");
                return 0;
            }
            double requiredFuel = distance / D2;
            if (requiredFuel > currentFuel) {
                double additionalFuel = requiredFuel - currentFuel;
                totalCost += additionalFuel * stations[i - 1].price;
                currentFuel = requiredFuel;
            }
            currentFuel -= requiredFuel;
        }

        if (i == N) {
            double remainingDistance = D1 - stations[i].distance;
            if (remainingDistance > maxDistance) {
                printf("No Solution\n");
                return 0;
            }
            double requiredFuel = remainingDistance / D2;
            if (requiredFuel > currentFuel) {
                double additionalFuel = requiredFuel - currentFuel;
                totalCost += additionalFuel * stations[i].price;
            }
            break;
        }

        double minPrice = stations[i].price;
        int nextStation = -1;
        for (int j = i + 1; j <= N && stations[j].distance - stations[i].distance <= maxDistance; j++) {
            if (stations[j].price < minPrice) {
                minPrice = stations[j].price;
                nextStation = j;
                break;
            }
        }

        if (nextStation == -1) {
            totalCost += (C - currentFuel) * stations[i].price;
            currentFuel = C;
        } else {
            double distanceToNext = stations[nextStation].distance - stations[i].distance;
            double requiredFuel = distanceToNext / D2;
            if (requiredFuel > currentFuel) {
                double additionalFuel = requiredFuel - currentFuel;
                totalCost += additionalFuel * stations[i].price;
                currentFuel = requiredFuel;
            }
        }
    }

    printf("%.2lf\n", totalCost);
    return 0;
}