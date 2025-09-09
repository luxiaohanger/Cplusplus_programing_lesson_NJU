#include<iostream>
#include<cmath>
#include <string>
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
    int year=0,month=0,day=0,hour=0,min=0,sec=0;
    string mon;
    cin>>year>>mon>>day>>hour>>min>>sec;

    if(mon=="January")month=1;
    else if(mon=="February")month=2;
    else if(mon=="March")month=3;
    else if(mon=="April")month=4;
    else if(mon=="May")month=5;
    else if(mon=="June")month=6;
    else if(mon=="July")month=7;
    else if(mon=="August")month=8;
    else if(mon=="September")month=9;
    else if(mon=="October")month=10;
    else if(mon=="November")month=11;
    else month=12;

    long long realsec=floor_div(secplus(year,month,day,hour,min,sec)*60.0,59.0);

    int* date= realDate(realsec);
    string ans;
    //
    ans+=to_string(date[0]);
    //
    ans+='-';
    //
    if(date[1]>=10)ans+=to_string(date[1]);
    else ans.append("0").append(to_string(date[1]));
    //
    ans+='-';
    //
    if(date[2]>=10)ans+=to_string(date[2]);
    else ans.append("0").append(to_string(date[2]));
    //
    ans+='T';
    //
    if(date[3]>=10)ans+=to_string(date[3]);
    else ans.append("0").append(to_string(date[3]));
    //
    ans+=':';//2024-09-16T00:01:00
   //
    if(date[4]>=10)ans+=to_string(date[4]);
    else ans.append("0").append(to_string(date[4]));
    //
    ans+=':';//2024-09-16T00:01:00
    //
    if(date[5]>=10)ans+=to_string(date[5]);
    else ans.append("0").append(to_string(date[5]));
    cout<<ans;
    delete[] date;
    return 0;

}