#include<iostream>
#define PI 3.141592653589
using namespace std;

int main()
{
    int N, i, year;
    float x, y;
    cin >> N;
    
    for(i = 1; i <= N; ++i)
    {
        cin >> x >> y;
        year = (int)(PI*(x*x + y*y)/100)+1;
        cout<<"Property "<<i<<": This property will begin eroding in year " <<year<<"."<<endl;
    }
    cout<<"END OF OUTPUT."<<endl;
    return 0;
}