#include <stdio.h>
#include <string.h>

#define MAX_N 100

int main() {
    int n;
    scanf("%d", &n);

    int section = 0, subsection = 0, subsubsection = 0;
    char command[15], title[21];

    for (int i = 0; i < n; i++) {
        scanf("%s %s", command, title);

        if (strcmp(command, "section") == 0) {
            section++;
            subsection = 0;
            subsubsection = 0;
            printf("%d %s\n", section, title);
        } else if (strcmp(command, "subsection") == 0) {
            subsection++;
            subsubsection = 0;
            printf("%d.%d %s\n", section, subsection, title);
        } else if (strcmp(command, "subsubsection") == 0) {
            subsubsection++;
            printf("%d.%d.%d %s\n", section, subsection, subsubsection, title);
        }
    }

    return 0;
}