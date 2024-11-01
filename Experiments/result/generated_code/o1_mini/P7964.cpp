#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char command[20];
    char title[21];
    int sec1=0, sec2=0, sec3=0;
    for(int i=0;i<n;i++){
        scanf("%s %s", command, title);
        if(strcmp(command, "section")==0){
            sec1++;
            sec2=0;
            sec3=0;
            printf("%d %s\n", sec1, title);
        }
        else if(strcmp(command, "subsection")==0){
            sec2++;
            sec3=0;
            printf("%d.%d %s\n", sec1, sec2, title);
        }
        else if(strcmp(command, "subsubsection")==0){
            sec3++;
            printf("%d.%d.%d %s\n", sec1, sec2, sec3, title);
        }
    }
    return 0;
}