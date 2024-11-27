#include <iostream>

const int number_of_days_normal_year[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int compute_days_pass(int start_day, int start_month, int start_year, int end_day, int end_month,int end_year);
bool compute_is_leap_year(int year);

int main(void){
    int start_day = 1;
    int start_month = 1;
    int start_year = 1900;
    
    int end_day = 31;
    int end_month = 12;
    int end_year = 2000;

    long int days = compute_days_pass(start_day, start_month, start_year, end_day, end_month,end_year);

    std::cout << days;

    return 1;
}

int compute_days_pass(int start_day, int start_month, int start_year, int end_day, int end_month,int end_year){

    long int days = 0;
    //compute days of firts year
    
    for (int month = start_month;month <= 12; month++){
        days += number_of_days_normal_year[month-1]; //becuase the index starts at 0
    }
    bool first_year_is_leap = compute_is_leap_year(start_year);
    if (first_year_is_leap){
        if (start_month <= 2){
            days += 1; //add the 29 of february
        }
    }
    //substrarc the days that have pass
    days = days - (start_day-1); //include the start day for explae is it start at 1 the day 1 is counted 

    //counpute whole years
    for (int year = start_year + 1; year <= end_year -1 ; year++){
        //is leap year
        bool is_leap_year = compute_is_leap_year(year);
        if (is_leap_year){
                days += 366;
        } else {
                days += 365;
            }
        }

    for (int month = 1;month <= end_month; month++){
        days += number_of_days_normal_year[month-1]; //becuase the index starts at 0
    }

    bool end_year_is_leap = compute_is_leap_year(end_year);
    if (first_year_is_leap){
        if (2<=end_month){
            days += 1; //add the 29 of february
        }
    }
    //substrarc the days that i am extra counting from the 
    days = days - (number_of_days_normal_year[end_month-1]-end_day); 
    return days;
    }

bool compute_is_leap_year(int year){

    bool is_leap_year = false;
    if (year%4 == 0){
        if (year % 100 == 0){ //if they are century
            if(year % 400 == 0){
                is_leap_year = true; //only if the century is divisible by 400
            }
            else {
                is_leap_year = false;
            }
        } else {
            is_leap_year = true;
        }
    }
    return is_leap_year;
}