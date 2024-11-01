#include <stdio.h>
#include <math.h>

int main(){
    double s, x;
    scanf("%lf %lf", &s, &x);
    double left = s - x;
    double right = s + x;
    double pos = 0.0;
    double speed = 7.0;
    for(int t=1; t<=1000; t++){
        pos += speed;
        if(pos >= left - 1e-8 && pos <= right + 1e-8){
            double pos_next = pos + speed * 0.98;
            if(pos_next <= right + 1e-8){
                printf("y");
            }
            else{
                printf("n");
            }
            return 0;
        }
        speed *= 0.98;
    }
    printf("n");
    return 0;
}