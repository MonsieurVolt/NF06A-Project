#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int year;
    int month;
    int day;
} date;
struct job
{

    int id;
    int processing_time;
    date release_date;
    date due_date;
    float prtf_value;
};
__declspec(dllexport) int *test(struct job *task, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", task[i].due_date.day);
    }
    int *array = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i <= 10; i++)
    {
        array[i] = i;
    }
    return array;
}
