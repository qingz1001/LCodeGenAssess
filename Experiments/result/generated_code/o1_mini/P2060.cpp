#include <stdio.h>
#include <stdlib.h>

int max_int(int a, int b) {
    return a > b ? a : b;
}

int min_knight_moves(int x_p, int y_p, int x_s, int y_s) {
    int dx = abs(x_s - x_p);
    int dy = abs(y_s - y_p);
    
    if (dx < dy) {
        int temp = dx;
        dx = dy;
        dy = temp;
    }
    
    if (dx ==1 && dy ==0) return 3;
    if (dx ==2 && dy ==2) return 4;
    
    int d = max_int( (dx +1)/2, (dx + dy +1)/3 );
    
    if ( (d %2) == ((dx + dy) %2) ) return d;
    else return d +1;
}

int main(){
    int x_p, y_p, x_s, y_s;
    scanf("%d %d %d %d", &x_p, &y_p, &x_s, &y_s);
    printf("%d\n", min_knight_moves(x_p, y_p, x_s, y_s));
    return 0;
}