#include<iostream>
#include <cmath>

using namespace std;
bool checkpostive(double x) {
    return x>0;
}
double func(double a,double b,double x) {
    return exp(x)-a*x-b;
}
int main() {
   double a,b;
    cin>>a>>b;
    double left=0;
    double right = 10;
    double mid=left/2+right/2;
    int n=27;
    while(n--) {
    if(checkpostive(func(a,b,left))==checkpostive(func(a,b,mid))) {
        //key-->(mid,right)
        left=mid;
    }else {
        right=mid;
    }
        mid=left/2+right/2;
    }
    printf("%.6f",mid);
    return 0;
}