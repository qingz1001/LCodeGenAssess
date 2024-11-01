#include <stdio.h>
#include <string.h>

int main(){
    int num;
    char unit1[4], unit2[4];
    scanf("%d %s = ? %s", &num, unit1, unit2);
    
    double factor1, factor2;
    
    if(strcmp(unit1, "GB") == 0){
        factor1 = 1 << 30;
    }
    else if(strcmp(unit1, "MB") == 0){
        factor1 = 1 << 20;
    }
    else if(strcmp(unit1, "KB") == 0){
        factor1 = 1 << 10;
    }
    else{
        factor1 = 1;
    }
    
    if(strcmp(unit2, "GB") == 0){
        factor2 = 1 << 30;
    }
    else if(strcmp(unit2, "MB") == 0){
        factor2 = 1 << 20;
    }
    else if(strcmp(unit2, "KB") == 0){
        factor2 = 1 << 10;
    }
    else{
        factor2 = 1;
    }
    
    double result = (num * factor1) / factor2;
    printf("%.6lf\n", result);
    
    return 0;
}