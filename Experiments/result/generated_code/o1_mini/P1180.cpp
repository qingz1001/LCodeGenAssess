#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STATIONS 52
#define MAX_FUEL 400
#define INF 1e18

typedef struct {
    double distance;
    double price;
} Station;

int main(){
    double D;
    scanf("%lf", &D);
    
    double C, M, init_cost;
    int n;
    scanf("%lf %lf %lf %d", &C, &M, &init_cost, &n);
    
    Station stations[MAX_STATIONS];
    stations[0].distance = 0.0;
    stations[0].price = 0.0;
    
    for(int i=1;i<=n;i++){
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }
    stations[n+1].distance = D;
    stations[n+1].price = 0.0;
    int total = n+2;
    
    // Initialize DP
    double DP[total][MAX_FUEL+1][2];
    for(int i=0;i<total;i++)
        for(int f=0; f<=MAX_FUEL; f++)
            for(int s=0;s<2;s++)
                DP[i][f][s] = INF;
    
    int initial_fuel = (int)(C *10 +1e-6);
    DP[0][initial_fuel][0] = init_cost;
    
    for(int i=0;i<total-1;i++){
        for(int f=0; f<=MAX_FUEL; f++){
            for(int s=0; s<2; s++){
                if(DP[i][f][s] >= INF) continue;
                
                double distance = stations[i+1].distance - stations[i].distance;
                double fuel_needed = distance / M;
                int fuel_needed_scaled = ceil(fuel_needed *10 -1e-6);
                
                if(f >= fuel_needed_scaled){
                    int f_after = f - fuel_needed_scaled;
                    
                    if(i+1 == total-1){
                        // Destination, no need to stop
                        if(DP[i+1][f_after][s] > DP[i][f][s]){
                            DP[i+1][f_after][s] = DP[i][f][s];
                        }
                    }
                    else{
                        double distance_next = stations[i+2].distance - stations[i+1].distance;
                        double fuel_needed_next = distance_next / M;
                        double f_after_fuel = f_after /10.0;
                        int required_stop = 0;
                        if(f_after_fuel < (C /2.0 -1e-6) || f_after_fuel < (fuel_needed_next -1e-6)){
                            required_stop =1;
                        }
                        if(required_stop){
                            if(s ==0){
                                // First stop, must fill to max
                                int fill = (int)(ceil((C - f_after_fuel)*10 -1e-6));
                                if(fill <0) fill=0;
                                if(fill > (int)(C*10 - f_after)) fill = (int)(C*10 - f_after);
                                
                                double cost_fill = (fill /10.0) * stations[i+1].price;
                                // Round to 0.1
                                cost_fill = floor(cost_fill *10 +0.5)/10.0;
                                double total_cost = DP[i][f][s] + cost_fill +20.0;
                                
                                int new_fuel = (int)(C *10 +1e-6);
                                int new_s =1;
                                
                                if(DP[i+1][new_fuel][new_s] > total_cost){
                                    DP[i+1][new_fuel][new_s] = total_cost;
                                }
                            }
                            else{
                                // Not first stop, choose how much to fill
                                double fuel_needed_req = f_after_fuel;
                                double max_required = (C /2.0 > fuel_needed_next) ? (C /2.0) : fuel_needed_next;
                                int min_fuel_scaled = ceil(max_required *10 -1e-6);
                                int fill_min = min_fuel_scaled - f_after;
                                if(fill_min <0) fill_min=0;
                                if(fill_min > (int)(C*10 - f_after)) fill_min = (int)(C*10 - f_after);
                                
                                for(int fill = fill_min; fill <= (int)(C*10 - f_after); fill++){
                                    double cost_fill = (fill /10.0) * stations[i+1].price;
                                    cost_fill = floor(cost_fill *10 +0.5)/10.0;
                                    double total_cost = DP[i][f][s] + cost_fill +20.0;
                                    
                                    int new_fuel = f_after + fill;
                                    int new_s = s;
                                    
                                    if(DP[i+1][new_fuel][new_s] > total_cost){
                                        DP[i+1][new_fuel][new_s] = total_cost;
                                    }
                                }
                            }
                        }
                        else{
                            // Do not stop
                            if(DP[i+1][f_after][s] > DP[i][f][s]){
                                DP[i+1][f_after][s] = DP[i][f][s];
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Find the minimum cost at destination
    double result = INF;
    for(int f=0; f<=MAX_FUEL; f++){
        for(int s=0; s<2; s++){
            if(DP[total-1][f][s] < result){
                result = DP[total-1][f][s];
            }
        }
    }
    
    // Print with one decimal
    printf("%.1lf\n", result);
    
    return 0;
}