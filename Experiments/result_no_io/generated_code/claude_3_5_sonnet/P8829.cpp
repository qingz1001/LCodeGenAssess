#include <stdio.h>
#include <string.h>
#include <math.h>

double convert(double value, char* from, char* to) {
    int from_exp, to_exp;
    
    if (strcmp(from, "B") == 0) from_exp = 0;
    else if (strcmp(from, "KB") == 0) from_exp = 10;
    else if (strcmp(from, "MB") == 0) from_exp = 20;
    else if (strcmp(from, "GB") == 0) from_exp = 30;
    
    if (strcmp(to, "B") == 0) to_exp = 0;
    else if (strcmp(to, "KB") == 0) to_exp = 10;
    else if (strcmp(to, "MB") == 0) to_exp = 20;
    else if (strcmp(to, "GB") == 0) to_exp = 30;
    
    return value * pow(2, from_exp - to_exp);
}

int main() {
    int value;
    char from[3], to[3];
    
    scanf("%d%s=%s", &value, from, to);
    
    double result = convert(value, from, to);
    
    printf("%.6f\n", result);
    
    return 0;
}