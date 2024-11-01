#include <stdio.h>
#include <string.h>

int main(){
    int k;
    scanf("%d", &k);
    char s[256];
    scanf("%s", s);
    int len = strlen(s);
    // Digit segments: 0 to 6
    unsigned char digit_segments[10] = {
        0x3F, //0
        0x06, //1
        0x5B, //2
        0x4F, //3
        0x66, //4
        0x6D, //5
        0x7D, //6
        0x07, //7
        0x7F, //8
        0x6F  //9
    };
    int total_lines = 2*k + 3;
    for(int line=0; line < total_lines; line++){
        for(int d=0; d < len; d++){
            int digit = s[d]-'0';
            unsigned char segments = digit_segments[digit];
            if(line ==0){
                // Top horizontal
                printf(" ");
                for(int i=0;i<k;i++) printf("%c", (segments & 0x01)? '-' : ' ');
                printf(" ");
            }
            else if(line >0 && line <k+1){
                // Upper vertical
                printf("%c", (segments & 0x20)? '|' : ' ');
                for(int i=0;i<k;i++) printf(" ");
                printf("%c", (segments & 0x02)? '|' : ' ');
            }
            else if(line ==k+1){
                // Middle horizontal
                printf(" ");
                for(int i=0;i<k;i++) printf("%c", (segments & 0x40)? '-' : ' ');
                printf(" ");
            }
            else if(line >k+1 && line <2*k+2){
                // Lower vertical
                printf("%c", (segments & 0x10)? '|' : ' ');
                for(int i=0;i<k;i++) printf(" ");
                printf("%c", (segments & 0x04)? '|' : ' ');
            }
            else{
                // Bottom horizontal
                printf(" ");
                for(int i=0;i<k;i++) printf("%c", (segments & 0x08)? '-' : ' ');
                printf(" ");
            }
            if(d != len-1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}