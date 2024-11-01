#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 150
#define MAX_NAME_LEN 100

typedef struct {
    int num_students;
    int distance;
    char name[MAX_NAME_LEN];
} City;

int main(){
    City cities[MAX_CITIES];
    int count = 0;
    while(1){
        if(scanf("%d %d %s", &cities[count].num_students, &cities[count].distance, cities[count].name)!=3){
            break;
        }
        if(strcmp(cities[count].name, "Moscow")==0){
            count++;
            break;
        }
        count++;
    }
    int min_cost = -1;
    int best_city = 0;
    for(int i=0;i<count;i++){
        long long cost =0;
        for(int j=0;j<count;j++){
            long long dist = abs(cities[j].distance - cities[i].distance);
            cost += dist * (long long)cities[j].num_students;
        }
        if(min_cost == -1 || cost < min_cost || (cost == min_cost && cities[i].distance < cities[best_city].distance)){
            min_cost = cost;
            best_city = i;
        }
    }
    printf("%s %d\n", cities[best_city].name, min_cost);
    return 0;
}