#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000005
#define MAXM 1000005
#define CAPACITY 36

typedef struct {
    int x, y, z;
} Request;

Request requests[MAXM];
int passengerCount[MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &requests[i].x, &requests[i].y, &requests[i].z);
        if (requests[i].x < requests[i].y) {
            passengerCount[requests[i].x] += requests[i].z;
            passengerCount[requests[i].y] -= requests[i].z;
        } else {
            passengerCount[requests[i].x] += requests[i].z;
            passengerCount[1] += requests[i].z;
            passengerCount[requests[i].y] -= requests[i].z;
        }
    }

    int maxPassengers = 0;
    int currentPassengers = 0;

    for (int i = 1; i <= n; i++) {
        currentPassengers += passengerCount[i];
        if (currentPassengers > maxPassengers) {
            maxPassengers = currentPassengers;
        }
    }

    int requiredCarriages = (maxPassengers + CAPACITY - 1) / CAPACITY;
    printf("%d\n", requiredCarriages);

    return 0;
}