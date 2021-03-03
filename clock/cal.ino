//Процедура нахождения високосных годов
//
//1 - високосный
//0 - невисокосный

boolean cal_yy (int yyyy)
{
  int _cal_yy = 0;
      _cal_yy=yyyy/4;
      _cal_yy=_cal_yy*4;
      if(yyyy-_cal_yy==0)
      {
        return (1);
      }
      else
      {
        return (0);
      }
}
//
//Процедура возвращает количество дней в месяце
int cal_maxd(int yyyy, int mmmm)
{
int array_vis[13]={0,31,29, 31,30, 31,30,31,31,30,31,30,31};
int array_no_vis[13]={0,31,28, 31,30, 31,30,31,31,30,31,30,31};
boolean vv;
    vv=cal_yy(yyyy);
    if (vv == 1)
    {
      return array_vis[mmmm];
    }
    else
    {
      return array_no_vis[mmmm];
    }
}
//определене дня недели
  char* cal_dn (int yyyy, int mmmm, int dddd)
  {
    int cal_dn;
    int cal_m;
    int month_v[]={0,4,0,1,4,6,2,4,0,3,5,1,3};
    int month[]={0,5,1,1,4,6,2,4,0,3,5,1,3};
    char* dn[]={"DC","Gy","Dn","Ch","Xn","Gn","C<"};          //Пн Вт Ср Чт Пт СБ ВС
    //определяем високосный или невисокосный год
    
    if(cal_yy(yyyy) == 0)
    {
      cal_m=month[mmmm];
    }
    else
    {
      cal_m=month_v[mmmm];
    }
    cal_dn=(yyyy+yyyy/4+cal_m+dddd) % 7;
    return dn[cal_dn];
    
  }
