#include <stdio.h>
#include <stdlib.h>
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
__declspec(dllexport) int *test(struct Task *task, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", task[i].rdate.year);
    }
    int *array = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i <= 10; i++)
    {
        array[i] = i;
    }
    return array;
}
__declspec(dllexport) int *getArray()
{
    int *array = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i <= 10; i++)
    {
        array[i] = i;
    }
    return array;
}