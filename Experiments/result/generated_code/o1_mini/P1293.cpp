#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int students;
    int distance;
    char name[101];
} City;

int main(){
    City cities[150];
    int n=0;

    while(1){
        int students, distance;
        char name[101];
        if(scanf("%d %d %s", &students, &distance, name)!=3){
            break;
        }
        cities[n].students = students;
        cities[n].distance = distance;
        strcpy(cities[n].name, name);
        n++;
        if(distance ==0){
            break;
        }
    }

    int best_city = -1;
    long min_cost = 0;

    for(int i=0;i<n;i++){
        long cost=0;
        for(int j=0;j<n;j++){
            cost += (long)cities[j].students * abs(cities[i].distance - cities[j].distance);
        }
        if(i==0 || cost < min_cost || (cost == min_cost && cities[i].distance < cities[best_city].distance)){
            min_cost = cost;
            best_city = i;
        }
    }

    printf("%s %ld\n", cities[best_city].name, min_cost);

    return 0;
}