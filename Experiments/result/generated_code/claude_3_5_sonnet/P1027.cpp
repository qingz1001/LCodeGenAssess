#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_CITIES 100
#define MAX_AIRPORTS 4

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point airports[MAX_AIRPORTS];
    double railway_price;
} City;

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double min_cost(City cities[], int S, double t, int A, int B) {
    double min_cost = DBL_MAX;

    for (int a = 0; a < MAX_AIRPORTS; a++) {
        for (int b = 0; b < MAX_AIRPORTS; b++) {
            double cost = 0;
            
            // Cost within city A
            for (int i = 0; i < MAX_AIRPORTS; i++) {
                double d = distance(cities[A-1].airports[a], cities[A-1].airports[i]);
                cost += d * cities[A-1].railway_price;
            }
            
            // Cost within city B
            for (int i = 0; i < MAX_AIRPORTS; i++) {
                double d = distance(cities[B-1].airports[b], cities[B-1].airports[i]);
                cost += d * cities[B-1].railway_price;
            }
            
            // Cost of flight between A and B
            cost += distance(cities[A-1].airports[a], cities[B-1].airports[b]) * t;
            
            if (cost < min_cost) {
                min_cost = cost;
            }
        }
    }

    return min_cost;
}

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        int S, A, B;
        double t;
        scanf("%d %lf %d %d", &S, &t, &A, &B);

        City cities[MAX_CITIES];
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%lf %lf", &cities[i].airports[j].x, &cities[i].airports[j].y);
            }
            scanf("%lf", &cities[i].railway_price);

            // Calculate the fourth airport's coordinates
            cities[i].airports[3].x = cities[i].airports[0].x + cities[i].airports[2].x - cities[i].airports[1].x;
            cities[i].airports[3].y = cities[i].airports[0].y + cities[i].airports[2].y - cities[i].airports[1].y;
        }

        printf("%.1f\n", min_cost(cities, S, t, A, B));
    }

    return 0;
}