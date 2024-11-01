#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char s[9];
    scanf("%s", s);
    // Check if first three are 'M','D','A'
    int isLocal = (s[0]=='M' && s[1]=='D' && s[2]=='A') ? 1 : 0;
    if(!isLocal){
        printf("1 1 1 1 1");
        return 0;
    }
    // Find tail digit
    char tail = '0';
    for(int i=7;i>=3;i--){
        if(isdigit(s[i])){
            tail = s[i];
            break;
        }
    }
    int digit = tail - '0';
    // Define restrictions
    int restrictions[5][2] = {
        {1,9}, // Monday
        {2,8}, // Tuesday
        {3,7}, // Wednesday
        {4,6}, // Thursday
        {5,0}  // Friday
    };
    int output[5];
    for(int i=0;i<5;i++){
        if(digit == restrictions[i][0] || digit == restrictions[i][1]){
            output[i]=1;
        }
        else{
            output[i]=0;
        }
    }
    printf("%d %d %d %d %d", output[0], output[1], output[2], output[3], output[4]);
}