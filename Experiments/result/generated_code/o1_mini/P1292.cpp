#include <stdio.h>
#include <stdlib.h>

// Function to compute extended GCD of a and b
long long extended_gcd_func(long long a, long long b, long long* x, long long* y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd_func(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to solve a*x - b*y = d
int solve_pour(long long a, long long b, long long d, long long gcd, long long x0, long long y0, long long* x, long long* y) {
    if (d % gcd != 0) return 0;
    long long factor = d / gcd;
    long long xp = x0 * factor;
    long long yp = y0 * factor;

    long long b_div_gcd = b / gcd;
    long long a_div_gcd = a / gcd;

    // Calculate k for x >=0
    long long k1;
    if (b_div_gcd != 0) {
        if (-xp % b_div_gcd > 0)
            k1 = (-xp) / b_div_gcd + 1;
        else
            k1 = (-xp) / b_div_gcd;
    }
    else {
        if (xp >=0 )
            k1 = 0;
        else
            return 0;
    }

    // Calculate k for y >=0
    long long k2;
    if (a_div_gcd != 0) {
        if (yp % a_div_gcd > 0)
            k2 = yp / a_div_gcd + 1;
        else
            k2 = yp / a_div_gcd;
    }
    else {
        if (-yp >=0 )
            k2 = 0;
        else
            return 0;
    }

    long long k = (k1 > k2) ? k1 : k2;

    *x = xp + k * b_div_gcd;
    *y = -yp + k * a_div_gcd;

    if (*x >=0 && *y >=0)
        return 1;
    return 0;
}

int main(){
    long long a, b;
    scanf("%lld %lld", &a, &b);
    if(b ==0){
        printf("0\n0 0\n");
        return 0;
    }
    long long gcd, x0, y0;
    gcd = extended_gcd_func(a, b, &x0, &y0);
    
    // Case 1: a*x - b*y = gcd
    long long x1, y1;
    int valid1 = solve_pour(a, b, gcd, gcd, x0, y0, &x1, &y1);
    
    // Case 2: a*x - b*y = -gcd
    long long x2, y2;
    int valid2 = solve_pour(a, b, -gcd, gcd, x0, y0, &x2, &y2);
    
    // Find the best solution
    int has_solution = 0;
    long long final_x=0, final_y=0;
    
    if(valid1){
        has_solution =1;
        final_x =x1;
        final_y =y1;
    }
    if(valid2){
        if(!has_solution){
            has_solution =1;
            final_x =x2;
            final_y =y2;
        }
        else{
            if(x2 < final_x || (x2 == final_x && y2 < final_y)){
                final_x =x2;
                final_y =y2;
            }
        }
    }
    
    if(has_solution){
        printf("%lld\n%lld %lld\n", gcd, final_x, final_y);
    }
    else{
        // If no solution found, which should not happen as gcd is achievable
        printf("%lld\n0 0\n", gcd);
    }
    return 0;
}