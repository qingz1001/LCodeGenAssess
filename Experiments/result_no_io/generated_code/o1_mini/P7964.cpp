#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char cmd[15], title[21];
    int section=0, subsection=0, subsubsection=0;
    for(int i=0;i<n;i++){
        scanf("%s %s", cmd, title);
        if(strcmp(cmd, "section")==0){
            section++;
            subsection=0;
            subsubsection=0;
            printf("%d %s\n", section, title);
        }
        else if(strcmp(cmd, "subsection")==0){
            subsection++;
            subsubsection=0;
            printf("%d.%d %s\n", section, subsection, title);
        }
        else if(strcmp(cmd, "subsubsection")==0){
            subsubsection++;
            printf("%d.%d.%d %s\n", section, subsection, subsubsection, title);
        }
    }
    return 0;
}