//chcp 65001
//Shift + Alt + t
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int uru(int year);//うるう年判定
void printycal(int year);//年だけ入力された時の表示
int changeday(int year);//その年の1/1の曜日
void printmcal(int month, int year);//年と月が入力された時の表示
int changedate(int month, int year);//指定された年月の1日の曜日
void yuriusu();//ユリウス暦とグレゴリオ暦のずれたとき10月の表示
void printdate();//曜日の表示
void printkoyomi(int month);//暦の表示
void ab(int month, int year);//-jが入力された時の表示
void anprintdate();//-jが入力された時の表示

 int main(int argc, char *argv[])
{
	int year,month;
  time_t timer;
  struct tm *local;
  /* 現在時刻を取得 */
  timer = time(NULL);
  local = localtime(&timer); /* 地方時に変換 */

  char com1[] = "-3";//指定した三か月
  char com2[] = "-y";//現在の年のすべてのカレンダ－
  char com3[] = "-j";//ユリウス暦

  if(argc == 1)
  {
    year = local->tm_year + 1900;
    month = local->tm_mon + 1;
    printmcal(month, year);
  }

  if(argc==2 && atoi(argv[1]) <= 0)
  {
	   if(argc == 2 && strcmp(argv[1],com1) == 0)
    {
     year = local->tm_year + 1900;
     month = local->tm_mon + 1;
     if(month == 1)
     {
       printmcal(12, (year - 1));
       printf("\n");
       printmcal(month, year);
       printf("\n");
       printmcal((month + 1), year);
     }
     else if(month == 12)
     {
       printmcal((month - 1), year);
       printf("\n");
       printmcal(month, year);
       printf("\n");
       printmcal(1, (year + 1));
     }
     else
    {
     printmcal((month - 1), year);
     printf("\n");
     printmcal(month, year);
     printf("\n");
     printmcal((month + 1), year);
    }
   }

  if(argc == 2 && strcmp(argv[1],com2) == 0)
   {
     year = local->tm_year + 1900;
     printycal(year);
   }

  if(argc == 2 && strcmp(argv[1],com3) == 0)
   {
     year = local->tm_year + 1900;
     month = local->tm_mon + 1;
     ab(month, year);
   }
  }

  else if(argc == 2)
	{//年だけ
		year = atoi(argv[1]);
		printycal(year);
	}

	if(argc == 3)
	{
		month = atoi(argv[1]);
		year = atoi(argv[2]);
		printmcal(month, year);
	}

  if(argc == 4 && strcmp(argv[1],com1) == 0)
 {
   month = atoi(argv[2]);
   year = atoi(argv[3]);
  if(month == 1)
  {
    printmcal(12, (year - 1));
    printf("\n");
    printmcal(month, year);
    printf("\n");
    printmcal((month + 1), year);
  }
  else if(month == 12)
  {
    printmcal((month - 1), year);
    printf("\n");
    printmcal(month, year);
    printf("\n");
    printmcal(1, (year + 1));
  }
  else
 {
  printmcal((month - 1), year);
  printf("\n");
  printmcal(month, year);
  printf("\n");
  printmcal((month + 1), year);
 }
}

	return 0;
}

int uru(int year)//うるう年の判定
{
	int flag;
	flag = 0;
	if(year == 4)
	{//西暦4年は平年
		flag = 0;
	}
	else if((year % 400 == 0)
	||
	(year % 4 ==0 && year % 100 != 0)
	)
	{
	flag = 1;
	}
	return flag;
}

void printycal(int year)
{
	int i, j, l, count;
	int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	mday[2] = mday[2] + uru(year);
	count = changeday(year);//何曜日スタートか

	printf("      %d\n", year);
  if(year == 1582)
  {
    count = 1;
    for(i = 1; i < 10; ++i)
   {
     printkoyomi(i);

     printdate();

     for(l = 0; l < count; ++l)
     {
       printf("    ");
     }
     for(j = 1; j <= mday[i]; ++j)
     {

       if(count % 7 == 0 && count > 6)
       {
         printf("\n");
       }
       printf("%2d  ", j);

       ++count;
     }
     count = count % 7;
   }

   printkoyomi(10);

   printdate();

   yuriusu();

   count = 1;
   for(i = 11; i < 13; ++i)
  {
    printkoyomi(i);

    printdate();

    for(l = 0; l < count; ++l)
    {
      printf("    ");
    }
    for(j = 1; j <= mday[i]; ++j)
    {

      if(count % 7 == 0 && count > 6)
      {
        printf("\n");
      }
      printf("%2d  ", j);

      ++count;
    }
    count = count % 7;
  }
  }

	else for(i = 1; i < 13; ++i)
	{
		printkoyomi(i);

    printdate();

		for(l = 0; l < count; ++l)
		{
			printf("    ");
		}
		for(j = 1; j <= mday[i]; ++j)
		{

			if(count % 7 == 0 && count > 6)
			{
				printf("\n");
			}
			printf("%2d  ", j);

			++count;
		}
		count = count % 7;
	}
}

int changeday(int year)//その年の1月1日の曜日
{
	//西暦1583年1月1日は土曜日
	int i,sum,date;
	sum = 6;
	for(i = 1583; i < year; ++i)
	{
		sum = sum + 365 + uru(i);
	}
	date = sum % 7;//日曜なら0月曜1火曜2

	return date;
}

void printmcal(int month, int year)
{
	int i, count;
	int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	mday[2] = mday[2] + uru(year);

  if(year == 1582 &&
     (month == 1 || month == 11))
  {
    count = 1;
  }

  else if(year == 1582 &&
     (month == 2 || month == 3))
  {
    count = 4;
  }

  else if(year == 1582 &&
     (month == 4 || month == 7))
  {
    count = 0;
  }

  else if(year == 1582 &&
     (month == 8 || month == 12))
  {
    count = 3;
  }

  else if(year == 1582 && month == 5)
  {
    count = 2;
  }

  else if(year == 1582 && month == 9)
  {
    count = 6;
  }

  else count = changedate(month, year);

	printf("      %d\n", year);
	printkoyomi(month);

  printdate();

  if(year != 1582 || month != 10)
  {
    for(i = 0; i < count; ++i)
	   {
		   printf("    ");
	   }
	  for(i = 1; i <= mday[month]; ++i)
    {
		      if(count % 7 == 0 && count > 6)
		        {
			        printf("\n");
		        }
		 printf("%2d  ", i);
		++count;
	   }
   }
   else yuriusu();
}

int changedate(int month, int year)
{
	int i, sum, date;
	int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	sum = 6;

	for(i = 1583; i < year; ++i)
	{
		sum = sum + 365 + uru(i);
  }

	for(i = 1; i < month; ++i)
	{
		sum = sum + mday[i];
		if(i == 2 && uru(year) == 1)
		{
			sum = sum + uru(year);
		}
	}
	date = sum % 7;
	return date;
}

void yuriusu()
{
  printf("     1   2   3           \n");
  printf("                15  15  16\n");
  printf("17  18  19  20  21  22  23\n");
  printf("24  25  26  27  28  29  30\n");
  printf("31\n");
}

void printdate()
{
  printf("S 　M 　Th 　W 　Th 　F　S\n");
  printf("--------------------------\n");
}

void printkoyomi(int month)
{
  printf("\n");
  switch (month)
  {
    case 1:
    printf("      January\n");
    break;
    case 2:
    printf("      February\n");
    break;
    case 3:
    printf("      March\n");
    break;
    case 4:
    printf("      April\n");
    break;
    case 5:
    printf("      May\n");
    break;
    case 6:
    printf("      June\n");
    break;
    case 7:
    printf("      July\n");
    break;
    case 8:
    printf("      August\n");
    break;
    case 9:
    printf("      September\n");
    break;
    case 10:
    printf("      October\n");
    break;
    case 11:
    printf("      November\n");
    break;
    case 12:
    printf("      December\n");
    break;
  }
}
void ab(int month, int year)
 {
    int i, sum, count;
    count = changedate(month, year);
    sum = 1;
    int mday[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    mday[2] = mday[2] + uru(year);
    for(i = 1; i < month; ++i)
    {
      sum = sum + mday[i];
    }

    printf("%d\n",year);
    printkoyomi(i);
    anprintdate();
    for(i = 0; i < count; ++i)
	   {
		   printf("     ");
	   }
    for(i = 1; i <= mday[month]; ++i)
    {
      if(count % 7 == 0 && count > 6)
        {
          printf("\n");
        }
      printf("%2d  ", sum);
      ++count;
      ++sum;
    }
 }

 void anprintdate()
 {
   printf("S  　  M  　Th   W   Th    F 　 S\n");
   printf("---------------------------------\n");
 }
