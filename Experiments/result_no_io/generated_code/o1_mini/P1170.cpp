#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll gcd_func(ll a, ll b){
    while(b){
        ll temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(){
    int n;
    if(scanf("%d", &n)!=1) return 0;
    while(n--){
        ll ax, ay, bx, by;
        if(scanf("%lld %lld", &ax, &ay)!=2) return 0;
        if(scanf("%lld %lld", &bx, &by)!=2) return 0;
        ll dx = ax > bx ? ax - bx : bx - ax;
        ll dy = ay > by ? ay - by : by - ay;
        if(dx ==0 && dy ==0){
            printf("yes\n");
            continue;
        }
        ll g = gcd_func(dx, dy);
        if(g ==1){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }
    }
    return 0;
}