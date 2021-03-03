//Вывод на дисплей часиков
void disp_clock()
{
  myGLCD.setFont(BigNumbers);
  myGLCD.print(String(hou_dec)+String(hou_ed)+ "-" + String(min_dec) + String(min_ed),CENTER,0);
  myGLCD.setFont(SmallFont);
  myGLCD.print(String(sec_dec)+String(sec_ed),CENTER,16);
//  вывод даты
  myGLCD.setFont(RusFont);
  myGLCD.print(dn,LEFT,32);
    myGLCD.setFont(SmallFont);
//  myGLCD.invertText(vv);
  myGLCD.print(" "+String(dd_d)+String(dd_e)+"."+String(mm_d)+String(mm_e)+"."+String(yy_t)+String(yy_s)+String(yy_d)+String(yy_e),RIGHT,32);
//    myGLCD.invertText(false);
//        myGLCD.print(String(data[0]),RIGHT,40);

    myGLCD.print(String(teme)+"C",LEFT,40);
    if(bud_en[1]==1)
    {
      myGLCD.print("1",78,40);
    }
    else
    {
      myGLCD.print("_",78,40);
    }
    if(bud_en[2]==1)
    {
      myGLCD.print("2",68,40);
    }
    else
    {
      myGLCD.print("_",68,40);
    }
    if(bud_en[3]==1)
    {
      myGLCD.print("3",58,40);
    }
    else
    {
      myGLCD.print("_",58,40);
    }
    if(bud_en[4]==1)
    {
      myGLCD.print("4",48,40);
    }
    else
    {
      myGLCD.print("_",48,40);
    }

  return;
}


//Вывод меню
void disp_menu(int u)
{
  boolean v=0;
  boolean k=0;
  boolean b=0;
  boolean t=0;
  boolean s=0;
  switch(u)
  {
    case 1:
      v=1;
      k=0;
      b=0;
      t=0;
      s=0;
      break;
    case 2:
      v=0;
      k=1;
      b=0;
      t=0;
      s=0;
      break;
    case 3:
      v=0;
      k=0;
      b=1;
      t=0;
      s=0;
      break;
    case 4:
      v=0;
      k=0;
      b=0;
      t=1;
      s=0;
      break;
    case 5:
      v=0;
      k=0;
      b=0;
      t=0;
      s=1;
      break;
    default:
      v=0;
      k=0;
      b=0;
      t=0;
      s=0;
      break;
    
  }
       myGLCD.clrScr();        //очистка экрана
      myGLCD.setFont(RusFont);
      myGLCD.print("VTY> Ecnfyjdjr",CENTER,0);    //МЕНЮ УСТАНОВОК
      myGLCD.invertText(v);
      myGLCD.print("dhtvz",LEFT,8);                //время
      myGLCD.invertText(k);
      myGLCD.print("lfnf",LEFT,16);            //календарь дата
            myGLCD.invertText(b);
      myGLCD.print(",elbkmybrb",LEFT,24);           //будильники
            myGLCD.invertText(t);
      myGLCD.print("nfqvth",LEFT,32);               //таймер
            myGLCD.invertText(s);
      myGLCD.print("ctreyljvth",LEFT,40);           //секундомер
            myGLCD.invertText(false);
            return;

}

//вывод дисплея установки часиков (Уровень 2)
void disp_u2(int u)
{
  boolean v=0;
  boolean k=0;
  switch(u)
  {
  case 1:
    v=1;
    k=0;
    break;
  case 2:
    v=0;
    k=1;
    break;
  default:
    v=1;
    k=0;
  }
  myGLCD.setFont(BigNumbers);
  myGLCD.invertText(v);
  myGLCD.print(String(hou_dec)+String(hou_ed),LEFT,0);
  myGLCD.invertText(k);
  myGLCD.print(String(min_dec) + String(min_ed),RIGHT,0);
  myGLCD.invertText(false);

}
//Вывод дисплея установи календаря (Уровень 3)
void disp_u3(int u)
{
  boolean yyy=0;
  boolean mmm=0;
  boolean ddd=0;
  switch (u)
  {
    case 1:
      yyy=1;
      mmm=0;
      ddd=0;
      break;
    case 2:
      yyy=0;
      mmm=1;
      ddd=0;
      break;
    case 3:
      yyy=0;
      mmm=0;
      ddd=1;
      break;
    default:
      yyy=1;
      mmm=0;
      ddd=0;
      break;
  }
          myGLCD.setFont(RusFont);
          myGLCD.print("Ujl",LEFT,8);
                myGLCD.invertText(yyy);
          myGLCD.print(String(yy_t)+String(yy_s)+String(yy_d)+String(yy_e),RIGHT,8);
                          myGLCD.invertText(false);
          myGLCD.print("Vtczw",LEFT,16);
                          myGLCD.invertText(mmm);
          myGLCD.print(String(mm_d)+String(mm_e),RIGHT,16);
                          myGLCD.invertText(false);
          myGLCD.print("Ltym",LEFT,24);
                          myGLCD.invertText(ddd);
          myGLCD.print(String(dd_d)+String(dd_e),RIGHT,24);
                          myGLCD.invertText(false);
     return;
}
//Вывод дисплея выбора будильников (уровень 4)
void disp_u4(int u)
{
  boolean v=0;
  boolean k=0;
  boolean b=0;
  boolean t=0;
  boolean s=0;
  switch (u)
  {
    case 1:
    v=1;
    k=0;
    b=0;
    t=0;
    break;
    case 2:
    v-0;
    k=1;
    b=0;
    t=0;
    break;
    case 3:
    v-0;
    k=0;
    b=1;
    t=0;
    break;
    case 4:
    v-0;
    k=0;
    b=0;
    t=1;
    break;
    default:
    v-1;
    k=0;
    b=0;
    t=0;
    break;
  }
  
           myGLCD.setFont(RusFont);
         myGLCD.print("Ds,jh",CENTER,0);
         myGLCD.invertText(v);                   //будильник 1
         myGLCD.print("<elbkmybr 1",CENTER,8);
         myGLCD.invertText(k);                   //будильник 2
         myGLCD.print("<elbkmybr 2",CENTER,16);
         myGLCD.invertText(b);                   //будильник 3
         myGLCD.print("<elbkmybr 3",CENTER,24);
         myGLCD.invertText(t);                   //будильник 4
         myGLCD.print("<elbkmybr 4",CENTER,32);
  return;

}
//Вывод дисплея установки будильников (Уровень 5)
void disp_u5(int bud_num, int u)
{
  boolean v=0;
  boolean k=0;
  boolean b=0;
  boolean t=0;
  boolean s=0;
  int bud_hou_d=0;
  int bud_hou_e=0;
  int bud_min_d=0;
  int bud_min_e=0;

    switch (u){
      case 3:
        v=1;
        k=0;
        b=0;
        t=0;
        s=0;
        break;
      case 4:
        v=0;
        k=1;
        b=0;
        t=0;
        s=0;
        break;

      default:
        v=0;
        k=0;
        b=0;
        t=0;
        s=0;
        break;
    }
         myGLCD.setFont(RusFont);
         myGLCD.invertText(bud_en[bud_num]);                   //подуровень 1
         myGLCD.print("<elbkmybr "+String(bud_num),CENTER,0);
         myGLCD.invertText(! bud_en[bud_num]);                 //
//                   myGLCD.invertText(false);
                   myGLCD.invertText(true);
          myGLCD.print("1", LEFT,8);               //подуровень 2
          myGLCD.print("2", 12,8);
          myGLCD.print("3", 24,8);
          myGLCD.print("4", 36,8);
          myGLCD.print("5", 48,8);
          myGLCD.print("6", 60,8);
          myGLCD.print("7", 72,8);                  //
          myGLCD.invertText(false);
              myGLCD.setFont(RusFont);
          myGLCD.print("Dhtvz",LEFT, 16);
              myGLCD.setFont(SmallFont);
        bud_hou_d=bud_hou[bud_num]/10;
        bud_hou_e=bud_hou[bud_num]-bud_hou_d*10;
          myGLCD.invertText(v);
          myGLCD.print(String(bud_hou_d)+String(bud_hou_e), 36,16);                //подуровень 3
          myGLCD.invertText(k);
          bud_min_d=bud_min[bud_num]/10;
          bud_min_e=bud_min[bud_num]-bud_min_d*10;
          myGLCD.print(String(bud_min_d)+String(bud_min_e), 56,16);                //подуровень 4
              myGLCD.setFont(RusFont);
          myGLCD.print("Gjdnjh", LEFT,24);
            myGLCD.print("5",RIGHT,24);
              myGLCD.setFont(RusFont);
          myGLCD.print("Vtkjlbz", LEFT,32);
              myGLCD.setFont(SmallFont);
          myGLCD.print("1", RIGHT,32);
              myGLCD.setFont(RusFont);
          myGLCD.print("Yfuheprf", LEFT,40);
              myGLCD.setFont(SmallFont);
          myGLCD.print("PWM+",RIGHT,40);
          
    return;
  
}
