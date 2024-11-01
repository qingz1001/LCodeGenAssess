#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_PEOPLE 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int year;
    int month;
    int day;
} Person;

int compare(const void *a, const void *b) {
    Person *personA = (Person *)a;
    Person *personB = (Person *)b;

    if (personA->year != personB->year) {
        return personB->year - personA->year;
    } else if (personA->month != personB->month) {
        return personB->month - personA->month;
    } else {
        return personB->day - personA->day;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Person people[MAX_PEOPLE];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d", people[i].name, &people[i].year, &people[i].month, &people[i].day);
    }

    qsort(people, n, sizeof(Person), compare);

    for (int i = 0; i < n; i++) {
        printf("%s\n", people[i].name);
    }

    return 0;
}