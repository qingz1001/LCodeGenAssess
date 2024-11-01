#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double D;
    double P;
} Station;

int compare(const void* a, const void* b){
    Station *sa = (Station*)a;
    Station *sb = (Station*)b;
    if(sa->D < sb->D) return -1;
    else if(sa->D > sb->D) return 1;
    else return 0;
}

int main(){
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);
    Station stations[8];
    stations[0].D = 0.0;
    stations[0].P = P;
    for(int i=1;i<=N;i++){
        scanf("%lf %lf", &stations[i].D, &stations[i].P);
    }
    stations[N+1].D = D1;
    stations[N+1].P = 0.0;
    int total = N + 2;
    qsort(stations, total, sizeof(Station), compare);
    // Check if first station is at 0
    if(stations[0].D != 0.0){
        printf("No Solution");
        return 0;
    }
    // Check if any distance between consecutive stations is > C * D2
    double max_distance = C * D2;
    for(int i=0;i<total-1;i++){
        if(stations[i+1].D - stations[i].D > max_distance +1e-8){
            printf("No Solution");
            return 0;
        }
    }
    double total_cost = 0.0;
    double current_fuel = 0.0;
    for(int i=0;i<total-1;i++){
        double distance = stations[i+1].D - stations[i].D;
        double required_fuel = distance / D2;
        // Find the next station with lower price
        int j = -1;
        for(int k=i+1;k<total;k++){
            if(stations[k].P < stations[i].P){
                if(stations[k].D - stations[i].D <= max_distance +1e-8){
                    j = k;
                    break;
                }
            }
        }
        double price_to_buy;
        if(j != -1){
            double distance_to_j = stations[j].D - stations[i].D;
            double required = distance_to_j / D2;
            if(required < required_fuel){
                required_fuel = required;
            }
            if(current_fuel < required_fuel){
                price_to_buy = required_fuel - current_fuel;
                total_cost += price_to_buy * stations[i].P;
                current_fuel = required_fuel;
            }
        }
        else{
            // Buy as much as possible
            double needed = C;
            if(current_fuel < needed){
                price_to_buy = needed - current_fuel;
                total_cost += price_to_buy * stations[i].P;
                current_fuel = needed;
            }
        }
        current_fuel -= required_fuel;
    }
    printf("%.2lf", total_cost);
}