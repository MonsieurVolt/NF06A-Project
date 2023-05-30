/**
 * @file a Doxygen Version.c
 * @author your name (you@domain.com)
 * @brief efhfudfo
 * @version 0.1
 * @date 2023-05-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct
{
    int year;
    int month;
    int day;
} date;

typedef struct
{
    int id;
    int processing_time;
    date release_date;
    date due_date;
    float prtf_value;
} job;

/**
 * @brief Calculates the time difference in days between today's date and a given date.
 * @param[in] date_of_the_day Current date in date format (day in numbers, month in numbers and year in numbers)
 * @param[in] date_to_convert Date to be converted in date format (day in numbers, month in numbers and year in numbers)
 * @param[out] diff_time Time difference in days between the date to be converted and today's date. 
 * @return Time difference in days between the date to be converted and today's date.
 */ 
float convert_date_to_day(date date_of_the_day, date date_to_convert)
{
    float diff_time;
    int conversion_month_by_day[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int day_for_the_month_of_the_day, day_for_the_month_to_convert;
    diff_time = (date_to_convert.year - date_of_the_day.year) * 365; /* pas de prise en compte des années bissextiles */
    day_for_the_month_of_the_day = conversion_month_by_day[(date_of_the_day.month - 1)];
    day_for_the_month_to_convert = conversion_month_by_day[(date_to_convert.month - 1)];
    diff_time += day_for_the_month_to_convert - day_for_the_month_of_the_day + date_to_convert.day - date_of_the_day.day; /* ajout mois et jour*/
    return diff_time;
}

/**
 * @brief On teste
 * 
 * @param date_of_the_day 
 * @param processing_time 
 * @param release_date 
 * @param due_date 
 * @return float 
 */
float prtf_calculation(date date_of_the_day, int processing_time, date release_date, date due_date)
{
    float prtf_value, diff_time;

    diff_time = convert_date_to_day(date_of_the_day, release_date);
    prtf_value = 2 * fmax(0, diff_time) + processing_time; /* 0 is the current day */
    return prtf_value;
}
/**
 * @brief Test 3
 * 
 * @param jobs_list 
 * @param listSize 
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
 * @brief Main
 * 
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
        jobs_list[ind].prtf_value = prtf_calculation(date_of_the_day, jobs_list[ind].processing_time, jobs_list[ind].release_date, jobs_list[ind].due_date);
    }
    sortAscendingOrder(jobs_list, size);
    int *list_of_id = (int *)malloc(100 * sizeof(int));
    for (int i = 0; i < size; i++)
    {

        list_of_id[i] = jobs_list[i].id;
    } /* On a la liste d'ID trié dans le bon ordre d'exécution */

    return list_of_id;
}
