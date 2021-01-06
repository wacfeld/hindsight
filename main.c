#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define LINELEN 1000
#define MAXACTS 10000
#define putd(x) printf(#x ": %d\n", x)

typedef struct activity
{
    int mins;
    char *name;
} activity;

int curyear, curmonth, curday;
activity acts[MAXACTS];
int numacts = 0;

enum mod{SET, ADD};
void modact(char *name, enum mod how, int amt)
{
    for(int i = 0; i < numacts; i++)
    {
        if(strcmp(acts[i].name, name) == 0)
        {
            if(how == SET)
            {
                acts[i].mins = amt;
            }
            else if(how == ADD)
            {
                acts[i].mins += amt;
            }
            return;
        }
    }
    acts[numacts].name = name;
    acts[numacts].mins = amt;
    numacts++;
}

int trydate(char *line)
{
    int tempyear, tempmonth, tempday;
    if(sscanf(line, "%d-%d-%d", &tempyear, &tempmonth, &tempday) == 3)
    {
        curyear = tempyear, curmonth = tempmonth, curday = tempday;
        return 1;
    }
    return 0;
}

int tryrange(char *line)
{
    int comp1, comp2;
    int h1,m1, h2,m2;
    struct tm time1, time2;
    time_t objtime1, objtime2;

    char *name = malloc(LINELEN);
    if(sscanf(line, "%d-%d %s", &comp1, &comp2, name) == 3)
    {
        h1 = comp1/100, m1 = comp1 % 100;
        h2 = comp2/100, m2 = comp2 % 100;
        time1 = (struct tm) {.tm_min = m1, .tm_hour = h1, .tm_mday = curday, .tm_mon = curmonth-1, .tm_year = curyear-1900};
        time2 = (struct tm) {.tm_min = m2, .tm_hour = h2, .tm_mday = curday, .tm_mon = curmonth-1, .tm_year = curyear-1900};

        if(comp2 < comp1)
        {
            time2.tm_mday +=1;
        }
        objtime1 = mktime(&time1), objtime2 = mktime(&time2);
        int diff = (int) difftime(objtime2, objtime1)/60;

        modact(name, ADD, diff);
        return 1;
    }

    return 0;
}

int tryinst(char *line)
{
    int comp;
    int h, m;
    struct tm time;
    time_t objtime;

    char *name = malloc(LINELEN);
    if(sscanf(line, "%d %s", &comp, name) == 2)
    {
        h = comp/100, m = comp % 100;
        time = (struct tm) {.tm_min = m, .tm_hour = h, .tm_day = curday, .tm_mon = curmonth-1, .tm_year = curyear-1900};

    }
}

int main()
{
    char curline[LINELEN];
    while(scanf("%[^\n]\n", curline) != EOF)
    {
        if(trydate(curline)) ;
        else if(tryrange(curline)) ;
        else if(tryinst(curline)) ;
    }
    for(int i = 0; i < numacts; i++)
    {
        printf("%-20s %02d:%02d\n", acts[i].name, acts[i].mins/60, acts[i].mins%60);
    }
    //struct tm time = {.tm_year = 0, .tm_mon = 0, .tm_mday = 31};
    //time_t thing;
    //thing = mktime(&time);
    //puts(ctime(&thing));
    //time.tm_mday++;
    //thing = mktime(&time);
    //puts(ctime(&thing));
}
