#include <stdio.h>

int gcd(int a, int b){
    while(b){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1) return 0;
    while(n--){
        int ax, ay, bx, by;
        if(scanf("%d %d", &ax, &ay)!=2) return 0;
        if(scanf("%d %d", &bx, &by)!=2) return 0;
        int dx = ax > bx ? ax - bx : bx - ax;
        int dy = ay > by ? ay - by : by - ay;
        if(dx ==0 && dy ==0){
            printf("no\n");
            continue;
        }
        int g = gcd(dx, dy);
        if(g >1){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }
    }
    return 0;
}