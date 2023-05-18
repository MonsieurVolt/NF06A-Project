#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct
{
    int id;
    int processing_time;
    date release_date;
    date due_date;
    float prtf_value;
}job;

typedef struct
{
    int year;
    int month;
    int day;
}date;

float convert_date_to_day(date date_of_the_day, date date_to_convert){
float diff_time;
int conversion_month_by_day[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
int day_for_the_month_of_the_day, day_for_the_month_to_convert;
diff_time = (date_to_convert.year-date_of_the_day.year)*365; /* pas de prise en compte des années bissextiles */
day_for_the_month_of_the_day = conversion_month_by_day[(date_of_the_day.month+1)] ;
day_for_the_month_to_convert = conversion_month_by_day[(date_of_the_day.month+1)];
diff_time += day_for_the_month_to_convert - day_for_the_month_of_the_day + date_to_convert.day - date_of_the_day.day; /* ajout mois et jour*/
return diff_time;
}

float prtf_calculation(date date_of_the_day,float processing_time, date release_date, date due_date){
    float prtf_value, diff_time;
    diff_time = convert_date_to_day(date_of_the_day,release_date);
    prtf_value = 2*fmax(0,diff_time)+processing_time; /* 0 is the current day */
    return prtf_value;  
}

void sortAscendingOrder(job *jobs_list, int listSize)
{
    int i, done = 0;
    job stock;
    while(done == 0){
        done = 1;
        for (i = 0; i < listSize-1; i++)
        {
            if(jobs_list[i].prtf_value > jobs_list[i+1].prtf_value)
            {
                stock = jobs_list[i];
                jobs_list[i] = jobs_list[i+1];
                jobs_list[i+1] = stock;
                done = 0;
            }
        }
    }
}

int main(){
    int ind,i;
    job *jobs_list;
    time_t t = time(NULL);
    struct tm tm=*localtime(&t);
    date date_of_the_day;
    date_of_the_day.year=tm.tm_year+1900;
    date_of_the_day.month=tm.tm_mon+1;
    date_of_the_day.day=tm.tm_mday;
    for (ind=0; ind< ; ind++){
        jobs_list[ind].prtf_value=prtf_calculation(date_of_the_day,jobs_list[ind].processing_time,jobs_list[ind].release_date,jobs_list[ind].due_date);
    }
    sortAscendingOrder(jobs_list,number_of_jobs);
    int list_of_id[number_of_jobs];
    for (i=0; i<number_of_jobs;ind++){
        list_of_id[i] = jobs_list[i].id;
    }/* On a la liste d'ID trié dans le bon ordre d'exécution */
    free(jobs_list);
    return 0;
}