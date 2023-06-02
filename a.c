/**
 * @file a.c
 * @author Florian Ducept
 * @author Nathan Guérin
 * @brief Retrieves tasks and their information to determine the order in which they should be carried out
 * @version 0.1
 * @date 2023-06-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * @brief Structure used to store a date
 * 
 */
typedef struct
{
    int year;
    int month;
    int day;
} date;
/**
 * @brief Structure used to store task information
 * 
 */
typedef struct
{
    int id;
    int processing_time;
    date release_date;
    date due_date;
    float prtf_value;
} job;

/**
 * @fn float convert_date_to_day(date date_of_the_day, date date_to_convert)
 * @brief Calculates the time difference in days between today's date and a given date.
 * @param[in] date_of_the_day Current date in date format (day in numbers, month in numbers and year in numbers)
 * @param[in] date_to_convert Date to be converted in date format (day in numbers, month in numbers and year in numbers)
 * @return diff_time Time difference in days between the date to be converted and today's date.
 */ 
float convert_date_to_day(date date_of_the_day, date date_to_convert)
{
    float diff_time;
    int conversion_month_by_day[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int day_for_the_month_of_the_day, day_for_the_month_to_convert;
    diff_time = (date_to_convert.year - date_of_the_day.year) * 365; /* Days difference taking into account years */
    day_for_the_month_of_the_day = conversion_month_by_day[(date_of_the_day.month - 1)];
    day_for_the_month_to_convert = conversion_month_by_day[(date_to_convert.month - 1)];
    diff_time += day_for_the_month_to_convert - day_for_the_month_of_the_day + date_to_convert.day - date_of_the_day.day; /* Add the days difference taking into account months and days to the days difference taking into account years */
    return diff_time;
}

/**
 * @brief Calculate the prtf_value. The formula is : 2max(today's date, release_date) + processing_time. With today's date = 0 and release_date = diff_time because diff_time is the difference of day between the release_date and today's date.
 * 
 * @param date_of_the_day Current date in date format (day in numbers, month in numbers and year in numbers)
 * @param[in] processing_time The time it takes to complete the task
 * @param[in] release_date The date from which the task can be carried out
 * @return  prtf_value is Priority Rule Total Flow time value which will allow us to sort the list
 */
float prtf_calculation(date date_of_the_day, int processing_time, date release_date)
{
    float prtf_value, diff_time;

    diff_time = convert_date_to_day(date_of_the_day, release_date);
    prtf_value = 2 * fmax(0, diff_time) + processing_time; /* 0 is the current day */
    return prtf_value;
}
/**
 * @brief A function that sorts the list according to prtf values in ascending order
 * 
 * @param jobs_list A list containing the tasks to be carried out. Tasks are in job format. 
 * @param listSize An integer containing the size of the list
 * @return void
 */
void sortAscendingOrder(job *jobs_list, int listSize)
{
    int i, done = 0;
    job stock;
    while (done == 0)
    {
        done = 1;
        for (i = 0; i < listSize - 1; i++)
        {
            if (jobs_list[i].prtf_value > jobs_list[i + 1].prtf_value)
            {
                stock = jobs_list[i];
                jobs_list[i] = jobs_list[i + 1];
                jobs_list[i + 1] = stock;
                done = 0;
            }
        }
    }
}
/**
 * @brief Retrieves tasks and their information to determine the order in which they should be carried out
 * @param[in] jobs_list A list containing the tasks to be carried out. Tasks are in job format. 
 * @param[in] size Size of the list
 * @return A sorted list of task IDs
 */
__declspec(dllexport) int *test(job *jobs_list, int size)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    date date_of_the_day;
    date_of_the_day.year = tm.tm_year + 1900;
    date_of_the_day.month = tm.tm_mon + 1;
    date_of_the_day.day = tm.tm_mday;
    for (int ind = 0; ind < size; ind++)
    {
        jobs_list[ind].prtf_value = prtf_calculation(date_of_the_day, jobs_list[ind].processing_time, jobs_list[ind].release_date);
    }
    sortAscendingOrder(jobs_list, size);
    int *list_of_id = (int *)malloc(100 * sizeof(int));
    for (int i = 0; i < size; i++)
    {

        list_of_id[i] = jobs_list[i].id;
    }
    free (jobs_list);
    return list_of_id;
}
