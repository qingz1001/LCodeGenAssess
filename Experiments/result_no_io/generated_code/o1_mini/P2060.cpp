#include <stdio.h>
#include <stdlib.h>

int main(){
    int x_p, y_p, x_s, y_s;
    scanf("%d %d %d %d", &x_p, &y_p, &x_s, &y_s);
    int dx = abs(x_p - x_s);
    int dy = abs(y_p - y_s);
    if (dx < dy){
        int tmp = dx;
        dx = dy;
        dy = tmp;
    }
    int steps;
    if (dy ==0 && dx ==1){
        steps =3;
    }
    else if (dy ==1 && dx ==1){
        steps =2;
    }
    else if (dy ==2 && dx ==2){
        steps =4;
    }
    else{
        int k1 = (dx +1)/2;
        int k2 = (dx + dy + 2)/3;
        int k = (k1 > k2) ? k1 : k2;
        if ( (k %2) != ( (dx + dy) %2 ) ){
            k +=1;
        }
        steps =k;
    }
    printf("%d\n", steps);
    return 0;
}