#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

int main(){
    char *s = malloc(1000005);
    fgets(s, 1000005, stdin);
    char *p = s;
    // Parse X
    while(*p && isspace(*p)) p++;
    int x_missing = 0;
    ll X = 0;
    if(*p == '?'){
        x_missing = 1;
        p++;
    }
    else{
        X = 0;
        while(*p && isdigit(*p)){
            X = X*10 + (*p - '0');
            p++;
        }
    }
    // Parse operator
    while(*p && isspace(*p)) p++;
    char op = *p;
    p++;
    // Parse Y
    while(*p && isspace(*p)) p++;
    int y_missing = 0;
    ll Y = 0;
    if(*p == '?'){
        y_missing = 1;
        p++;
    }
    else{
        Y = 0;
        while(*p && isdigit(*p)){
            Y = Y*10 + (*p - '0');
            p++;
        }
    }
    // Parse '='
    while(*p && isspace(*p)) p++;
    if(*p == '=') p++;
    // Parse Z
    while(*p && isspace(*p)) p++;
    int z_missing = 0;
    ll Z = 0;
    if(*p == '?'){
        z_missing = 1;
    }
    else{
        Z = 0;
        while(*p && isdigit(*p)){
            Z = Z*10 + (*p - '0');
            p++;
        }
    }
    ll res;
    if(x_missing){
        if(op == '+') res = Z - Y;
        else res = Z + Y;
    }
    else if(y_missing){
        if(op == '+') res = Z - X;
        else res = X - Z;
    }
    else{
        if(op == '+') res = X + Y;
        else res = X - Y;
    }
    printf("%lld\n", res);
    free(s);
}