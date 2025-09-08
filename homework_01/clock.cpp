#include<iostream>
#include<cmath>
using namespace std;
 int secofMonth1[13]={0,31*24*60*60,28*24*60*60,31*24*60*60,30*24*60*60,31*24*60*60,
    30*24*60*60,31*24*60*60,31*24*60*60,30*24*60*60,31*24*60*60,30*24*60*60,31*24*60*60,};
 int secofMonth2[13]={0,31*24*60*60,29*24*60*60,31*24*60*60,30*24*60*60,31*24*60*60,
    30*24*60*60,31*24*60*60,31*24*60*60,30*24*60*60,31*24*60*60,30*24*60*60,31*24*60*60,};

bool checkyear(int year) {
    if(year%4==0) {
         if(year%400==0)return true;
        if(year%100==0)return false;
        return true;
    }
    return false;
}

long long countbyyear(int year) {
    long long plus=0;
    for(int i=2025;i<year;i++) {
        if(checkyear(i))plus+=366*24*60*60;
        else plus+=365*24*60*60;
    }
    return plus;
}

long long countrest(int year,int month,int day,int hour,int min, int sec) {
  long long plus=0;
    if(checkyear(year)) {
        for(int i=1;i<month;i++) {
            plus+=secofMonth2[i];
        }
    }else {
        for(int i=1;i<month;i++) {
            plus+=secofMonth1[i];
        }
    }
    //day begin with 1!!!
    plus+=(day-1)*24*60*60+hour*60*60+min*60+sec;
    return plus;
}

long long secplus(int year,int month,int day,int hour,int min, int sec) {
    //sec to 2024-09-01T22:20:00
    long long res=0;
    if(year!=2024) {
        res+=366*24*60*60-countrest(2024,9,1,22,20,0);
        res+=countbyyear(year);
        res+=countrest( year, month, day, hour,min, sec);
    }else {
        res+=countrest(year,month,day,hour,min,sec)-countrest(year,9,1,22,20,0);
    }
    return res;
}

long long floor_div(long long a, long long b) {
    // b > 0
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);  // 等价于 floor(a/b)
}

int* realDate(long long secplus) {
    int* ans=new int[6];
   //set 2024 1 1 0 0 0 a new bound
   //secplus<0  ok
    long long newsec=floor(secplus)+countrest(2024,9,16,0,0,0);
    int year=2024,month=1,day=1,hour=0,min=0,sec=0;
    long long  secRest=newsec;
    int* ptr;
    while(true) {
        if(checkyear(year)) ptr=secofMonth2;
        else ptr=secofMonth1;
            //run
            if(secRest>=ptr[month]) {
                //first 先减去当月的，否则月份变了！
                secRest-=ptr[month];
                if(month==12) {
                    year++;
                    month=1;
                }else {
                    month++;
                }
            }else {
                //less than a month
                day+=secRest/(24*60*60);
                secRest%=(24*60*60);
                hour+=secRest/(60*60);
                secRest%=(60*60);
                min+=secRest/60;
                secRest%=60;
                sec=secRest;
                break;
            }
    }
    ans[0]=year;
    ans[1]=month;
    ans[2]=day;
    ans[3]=hour;
    ans[4]=min;
    ans[5]=sec;
    return ans;
}




int main() {
    //input
    int year,month,day,hour,min,sec=0;
    char mon[15]="\0";
    cin>>year>>mon>>day>>hour>>min>>sec;
    //cout<<year<<mon<<day<<hour<<min<<sec;
    //Jan,Feb,Mar,Apr,May,June,July,Aug,Sept,Oct,Nov,Dec
    switch(mon[0]) {
        case 'J': {
            if(mon[1]=='a')month=1;
            else if(mon[2]=='n')month=6;
            else month=7;
            break;
        }
        case 'F':
            month=2;
            break;
        case 'M': {
            if(mon[2]=='r')month=3;
            else month=5;
            break;
        }
        case 'A': {
            if(mon[1]=='p')month=4;
            else month=8;
            break;
        }
        case 'S':
            month=9;
        break;
        case 'O':
            month=10;
        break;
        case 'N':
            month=11;
        break;
        case 'D':
            month=12;
        break;
    }
   // cout<<year<<month<<day<<hour<<min<<sec;
    //sec to 2024 9 16 0000
    long long realsec=floor_div(secplus(year,month,day,hour,min,sec)*60.0,59.0);
    // cout<<realsec;
    // //2024-09-01T22:20:00
    int* date= realDate(realsec);
    char* ans=new char[20];
    //
    int x1=date[0]/1000;
    date[0]%=1000;
    int x2=date[0]/100;
    date[0]%=100;
    int x3=date[0]/10;
    date[0]%=10;
    int x4=date[0];
    ans[0]=x1+'0';
    ans[1]=x2+'0';
    ans[2]=x3+'0';
    ans[3]=x4+'0';
    //
    ans[4]='-';
    //
     x3=date[1]/10;
    date[1]%=10;
     x4=date[1];
    ans[5]=x3+'0';
    ans[6]=x4+'0';
    //
    ans[7]='-';
    //
    x3=date[2]/10;
    date[2]%=10;
    x4=date[2];
    ans[8]=x3+'0';
    ans[9]=x4+'0';
    //
    ans[10]='T';
    //
    x3=date[3]/10;
    date[3]%=10;
    x4=date[3];
    ans[11]=x3+'0';
    ans[12]=x4+'0';
    //
    ans[13]=':';//2024-09-16T00:01:00
   //
    x3=date[4]/10;
    date[4]%=10;
    x4=date[4];
    ans[14]=x3+'0';
    ans[15]=x4+'0';
    //
    ans[16]=':';//2024-09-16T00:01:00
    //
    x3=date[5]/10;
    date[5]%=10;
    x4=date[5];
    ans[17]=x3+'0';
    ans[18]=x4+'0';
    ans[19]='\0';
    cout<<ans;
    delete[] date;
    delete[] ans;

    return 0;

}