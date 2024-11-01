#include <stdio.h>
#include <string.h>
#include <math.h>

double convert(double value, const char* from, const char* to) {
    int fromPower, toPower;
    
    if (strcmp(from, "B") == 0) fromPower = 0;
    else if (strcmp(from, "KB") == 0) fromPower = 10;
    else if (strcmp(from, "MB") == 0) fromPower = 20;
    else if (strcmp(from, "GB") == 0) fromPower = 30;
    
    if (strcmp(to, "B") == 0) toPower = 0;
    else if (strcmp(to, "KB") == 0) toPower = 10;
    else if (strcmp(to, "MB") == 0) toPower = 20;
    else if (strcmp(to, "GB") == 0) toPower = 30;
    
    return value * pow(2, fromPower - toPower);
}

int main() {
    int value;
    char from[3], to[3];
    
    scanf("%d%2s=?%2s", &value, from, to);
    
    double result = convert(value, from, to);
    
    printf("%.6f\n", result);
    
    return 0;
}