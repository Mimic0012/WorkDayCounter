#ifndef __PROGTEST__
#define __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>


bool leapyear(int y)
{
  if(y%400==0)return true;
  if(y%100==0)return false;
  if(y%4==0)return true;
  return false;  //default case if nothing is true
}

int days_in_month (int m,int y )
{
  if(m==2)
  {
    return leapyear(y) ? 29 : 28; //ternary operator leapyear is called as a conditttion to check if the year is leapyear or not
  }
  int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//first one is set to zero becuse indexing in array starts at 0
  return days[m];
}

bool is_valid_date(int y, int m,int d)
{
  if(y<2000 || (m>12 || m<1) || d<1 || (d>days_in_month(m,y)))
  {
    return false;
  }
  return true;
  
}

bool national_holiday(int m,int d)
{
  int holiday [11][2] = { {1, 1}, {5, 1}, {5, 8}, {7, 5}, {7, 6}, {9, 28}, {10, 28}, {11, 17}, {12, 24}, {12, 25}, {12, 26} };
  for(int i=0;i<11;i++)
  {
    if(holiday[i][0]==m && holiday[i][1]==d)
    {
      return true;
    }
  }
  return false;
}


bool isWorkDay ( int y, int m, int d )
{
  if(!is_valid_date(y,m,d)) return false;
  if(national_holiday(m,d)) return false;
  struct tm date = {0}; //initializes the date structure with all members set to zero. This is a shorthand way to ensure no uninitialized values.
  date.tm_year = y-1900;// For year 2023, this sets tm_year to 123(kuki ye 1900 se calculate karne ke liye set kiya gaya he)
  date.tm_mon = m-1;//The tm_mon field represents the month of the year as a zero-indexed value: January = 0, February = 1, ..., December = 11.
  date.tm_mday = d;

  mktime(&date);//mktime will set date.tm_wday based on the provided date

  if(date.tm_wday==0 ||date.tm_wday==6)//tm_wday means day of the week 0 = Sunday and so on..
  {
    return false;
  }
  return true;
  
}

typedef struct
{
  int m_TotalDays;
  int m_WorkDays;
} TResult;

TResult countDays ( int y1, int m1, int d1, int y2, int m2, int d2 )
{
  TResult result = {0,0};
  if(!is_valid_date(y1,m1,d1) || !is_valid_date(y2,m2,d2)|| y1>y2)
  {
    result.m_TotalDays = -1;
    result.m_WorkDays = -1;
    return result;//default case
  }
  struct tm start_date = {0};
  struct tm end_date = {0};

  start_date.tm_year = y1-1900;
  start_date.tm_mon = m1-1;
  start_date.tm_mday = d1;

  end_date.tm_year =y2-1900;
  end_date.tm_mon= m2-1;
  end_date.tm_mday =d2;

  time_t start = mktime(&start_date); //mktime initializes everything for start date also time_t is used to calculate the number of sectonds from the epoch
  time_t end = mktime(&end_date);

  if(start== -1 || end == -1 || start>end)//When using mktime(), it can return -1 to indicate that the conversion failed or the date is invalid. thats why we also check that condition
  {
    result.m_TotalDays = -1;
    result.m_WorkDays = -1;
    return result;
  }

  double seconds = difftime(end,start);//diiftime claculate the time diff in sec btw start and end from epoch
  int days = seconds / (24*60*60) ;  
  result.m_TotalDays = days+1; //beacuse lets say the date is from jan1 to jan1 then the diff would be 0 so we have to add 1

  

  for(time_t t = start; t<=end;t+=24*60*60)//hamne time_t isliye liya he kuki we have to take account for leap year and no of days in a  month etc 
  {
    struct tm *current_date = localtime(&t);//this stores the value of &t in current_date which is a ptr to strct tm whic divides everything like motnth years leap year etc
    if(isWorkDay(current_date->tm_year+1900,current_date->tm_mon+1,current_date->tm_mday))
    {
      result.m_WorkDays++;
    }
  }
  return result;

}

int main ( int argc, char *argv [] )
{
  TResult r;

  assert ( isWorkDay ( 2023, 10, 10 ) );

  assert ( ! isWorkDay ( 2023, 11, 11 ) );

  assert ( ! isWorkDay ( 2023, 11, 17 ) );

  assert ( ! isWorkDay ( 2023, 11, 31 ) );

  assert ( ! isWorkDay ( 2023,  2, 29 ) );

  assert ( ! isWorkDay ( 2004,  2, 29 ) );

  assert ( isWorkDay ( 2008,  2, 29 ) );

  assert ( ! isWorkDay ( 2001,  2, 29 ) );

  assert ( ! isWorkDay ( 1996,  1,  2 ) );

  r = countDays ( 2023, 11,  1,
                  2023, 11, 30 );
  assert ( r . m_TotalDays == 30 );
  assert ( r . m_WorkDays == 21 );

  r = countDays ( 2023, 11,  1,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 17 );
  assert ( r . m_WorkDays == 12 );

  r = countDays ( 2023, 11,  1,
                  2023, 11,  1 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 1 );

  r = countDays ( 2023, 11, 17,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 0 );

  r = countDays ( 2023,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 365 );
  assert ( r . m_WorkDays == 252 );

  r = countDays ( 2024,  1,  1,
                  2024, 12, 31 );
  assert ( r . m_TotalDays == 366 );
  assert ( r . m_WorkDays == 254 );

  r = countDays ( 2000,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 8766 );
  assert ( r . m_WorkDays == 6072 );

  r = countDays ( 2001,  2,  3,
                  2023,  7, 18 );
  assert ( r . m_TotalDays == 8201 );
  assert ( r . m_WorkDays == 5682 );

  r = countDays ( 2021,  3, 31,
                  2023, 11, 12 );
  assert ( r . m_TotalDays == 957 );
  assert ( r . m_WorkDays == 666 );

  r = countDays ( 2001,  1,  1,
                  2000,  1,  1 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );

  r = countDays ( 2001,  1,  1,
                  2023,  2, 29 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );

  //2 line left
  return 0;
}
#endif //this tell the _PROGETEST_ that this program has ended
