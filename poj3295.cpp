#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

int K(int, int);  //与
int A(int, int);  //或
int N(int);       //非
int C(int, int);  //非或 (!x)||y
int E(int, int);  //等于
int judge(char *array);

int main()
{
    char array[100] = {0};
    while((cin>>array)&&array[0]!='0')  // 如果不加&&array[0]，那么将会导致judge中栈越界
    {
        if(judge(array))
            cout<<"tautology"<<endl;
        else
            cout<<"not"<<endl;
    }
}

int K(int w,int x)
{
    if(w==1&&x==1)
        return 1;
    return 0;
}

int A(int w,int x)
{
    if(w==0&&x==0)
        return 0;
    return 1;
}

int N(int w)
{
    return !w;
}

int C(int w,int x)
{
    if(w==1&&x==0)
        return 0;
    return 1;
}

int E(int w,int x)
{
    if(w==x)
        return 1;
    return 0;
}

int judge(char *array)
{
    stack<int> _stack;
    int i,len,p,q,r,s,t,temp1,temp2;
    len = (int)strlen(array);
    
    for(p=0;p<2;p++)
        for(q=0;q<2;q++)
            for(r=0;r<2;r++)
                for(s=0;s<2;s++)
                    for(t=0;t<2;t++)//共枚举变量序列<p,q,r,s,t>的32(2^5)种情况
                    {
                        for(i = len-1; i >= 0; i--)//从尾巴开始向前遍历，遇到变量就压栈
                        {
                            if(array[i]=='p')
                                _stack.push(p);
                            else if(array[i]=='q')
                                _stack.push(q);
                            else if(array[i]=='r')
                                _stack.push(r);
                            else if(array[i]=='s')
                                _stack.push(s);
                            else if(array[i]=='t')
                                _stack.push(t);
                            
                            //遇到运算符
                            else if(array[i]=='N')//“非运算”是一元操作
                            {
                                temp1=_stack.top();
                                _stack.pop();//取数并弹栈
                                
                                _stack.push(N(temp1));//运算并压栈
                            }
                            else//其它都是二元运算
                            {
                                temp1=_stack.top();
                                _stack.pop();//取数并弹栈
                                
                                temp2=_stack.top();
                                _stack.pop();//取数并弹栈
                                
                                if(array[i]=='K')
                                    _stack.push(K(temp1,temp2));
                                else if(array[i]=='A')
                                    _stack.push(A(temp1,temp2));
                                else if(array[i]=='C')
                                    _stack.push(C(temp1,temp2));
                                else
                                    _stack.push(E(temp1,temp2));
                            }
                        }
                        temp1 = _stack.top();
                        _stack.pop();//保证栈清空
                        if(!temp1)
                            return 0;//枚举过程中有1种不是永真式就返回0
                    }
    return 1;//所有取值都是永真式才返回1
}