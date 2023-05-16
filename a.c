#include <stdio.h>

typedef struct
{
    int day;
    int month;
    int year;
} Date;
struct Task
{
    int id;
    Date rdate;
    Date ddate;
    int nbdays;
};
__declspec(dllexport) void test(struct Task *task, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", task[i].rdate.year);
    }
}
