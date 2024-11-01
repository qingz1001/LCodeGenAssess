#include <stdio.h>

int main(){
    double s, x;
    scanf("%lf %lf", &s, &x);
    double detection_min = s - x;
    double detection_max = s + x;
    double position = 0.0;
    double distance = 7.0;
    while(position <= detection_max){
        position += distance;
        if(position >= detection_min && position <= detection_max){
            double next_distance = distance * 0.98;
            double next_position = position + next_distance;
            if(next_position >= detection_min && next_position <= detection_max){
                printf("y");
                return 0;
            }
        }
        distance *= 0.98;
    }
    printf("n");
    return 0;
}