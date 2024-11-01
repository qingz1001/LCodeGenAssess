#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 255
#define MAX_SIZE 30
#define MAX_LINE 20000

int main(){
    int k;
    char s[MAX_DIGITS+1];
    scanf("%d", &k);
    scanf("%s", s);
    int n = strlen(s);
    
    // Define segments for each digit
    // segments[digit][segment]: 0=a,1=b,2=c,3=d,4=e,5=f,6=g
    int segments[10][7] = {
        {1,1,1,1,1,1,0}, //0
        {0,1,1,0,0,0,0}, //1
        {1,1,0,1,1,0,1}, //2
        {1,1,1,1,0,0,1}, //3
        {0,1,1,0,0,1,1}, //4
        {1,0,1,1,0,1,1}, //5
        {1,0,1,1,1,1,1}, //6
        {1,1,1,0,0,0,0}, //7
        {1,1,1,1,1,1,1}, //8
        {1,1,1,1,0,1,1}  //9
    };
    
    int total_rows = 2*k + 3;
    for(int row=0; row < total_rows; row++){
        char line[MAX_LINE] = "";
        for(int d=0; d < n; d++){
            int digit = s[d]-'0';
            char part[MAX_SIZE*2 + 5] = "";
            if(row == 0){
                // Top horizontal
                strcat(part, " ");
                if(segments[digit][0]){
                    for(int i=0; i<k; i++) strcat(part, "-");
                }
                else{
                    for(int i=0; i<k; i++) strcat(part, " ");
                }
                strcat(part, " ");
            }
            else if(row >0 && row < k+1){
                // Upper verticals
                if(segments[digit][5]) strcat(part, "|");
                else strcat(part, " ");
                for(int i=0; i<k; i++) strcat(part, " ");
                if(segments[digit][1]) strcat(part, "|");
                else strcat(part, " ");
            }
            else if(row == k+1){
                // Middle horizontal
                strcat(part, " ");
                if(segments[digit][6]){
                    for(int i=0; i<k; i++) strcat(part, "-");
                }
                else{
                    for(int i=0; i<k; i++) strcat(part, " ");
                }
                strcat(part, " ");
            }
            else if(row >k+1 && row < 2*k+2){
                // Lower verticals
                if(segments[digit][4]) strcat(part, "|");
                else strcat(part, " ");
                for(int i=0; i<k; i++) strcat(part, " ");
                if(segments[digit][2]) strcat(part, "|");
                else strcat(part, " ");
            }
            else if(row == 2*k+2){
                // Bottom horizontal
                strcat(part, " ");
                if(segments[digit][3]){
                    for(int i=0; i<k; i++) strcat(part, "-");
                }
                else{
                    for(int i=0; i<k; i++) strcat(part, " ");
                }
                strcat(part, " ");
            }
            strcat(line, part);
            if(d != n-1) strcat(line, " ");
        }
        printf("%s\n", line);
    }
}