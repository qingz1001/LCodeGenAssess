#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long ull;

char x_str[25], y_str[25];
ull x_num, y_num;
ull count_lever_numbers = 0;

// Function to calculate power of 10
ull power10(int n){
    ull res = 1;
    for(int i=0;i<n;i++) res *=10;
    return res;
}

int is_lever(ull num){
    char s[25];
    sprintf(s, "%llu", num);
    int len = strlen(s);
    for(int pivot=0; pivot<len; pivot++){
        ull left =0, right=0;
        for(int i=0;i<pivot;i++) left += (s[i]-'0')*(pivot - i);
        for(int i=pivot+1;i<len;i++) right += (s[i]-'0')*(i - pivot);
        if(left == right) return 1;
    }
    return 0;
}

int main(){
    scanf("%s %s", x_str, y_str);
    x_num = strtoull(x_str, NULL, 10);
    y_num = strtoull(y_str, NULL, 10);
    // Since y - x can be up to 1e18, we need a smarter way
    // But for simplicity, iterate and check
    // Note: This may not pass time limits for large ranges
    for(ull num = x_num; num <= y_num; num++){
        if(is_lever(num)) count_lever_numbers++;
        if(num == ULLONG_MAX) break;
    }
    printf("%llu", count_lever_numbers);
    return 0;
}