/*
Flip Game

Description

Flip game is played on a rectangular 4x4 field with two-sided pieces placed on each of its 16 squares. One side of each piece is white and the other one is black and each piece is lying either it's black or white side up. Each round you flip 3 to 5 pieces, thus changing the color of their upper side from black to white and vice versa. The pieces to be flipped are chosen every round according to the following rules:
Choose any one of the 16 pieces.
Flip the chosen piece and also all adjacent pieces to the left, to the right, to the top, and to the bottom of the chosen piece (if there are any).

Consider the following position as an example:

bwbw
wwww
bbwb
bwwb
Here "b" denotes pieces lying their black side up and "w" denotes pieces lying their white side up. If we choose to flip the 1st piece from the 3rd row (this choice is shown at the picture), then the field will become:

bwbw
bwww
wwwb
wwwb
The goal of the game is to flip either all pieces white side up or all pieces black side up. You are to write a program that will search for the minimum number of rounds needed to achieve this goal.
Input

The input consists of 4 lines with 4 characters "w" or "b" each that denote game field position.
Output

Write to the output file a single integer number - the minimum number of rounds needed to achieve the goal of the game from the given position. If the goal is initially achieved, then write 0. If it's impossible to achieve the goal, then write the word "Impossible" (without quotes).
Sample Input

bwwb
bbwb
bwwb
bwww
Sample Output

4
*/
#include<iostream>
#define INF 65535
using namespace std;

void flip();
int judge();
void search(int totalNum, int doneNum, int pre);

int board[4][4] = {0};
int visit[16] = {0};
int answer;

int main()
{
    int x,y;
    char buf;
    
    for (int i = 0; i < 16; ++i)
    {
        x = i/4;
        y = i%4;
        cin >> buf;
        if (buf == 'w')
        {
            board[i/4][i%4] = -1;//白色记为-1
        }
        else
            board[i/4][i%4] = 1;//黑色记为1
    }//输入棋盘
    
    answer = INF; //初始化要翻无穷多次
    
    for (int i = 0; i < 16; ++i) {
        for(int j=0;j<16;j++){visit[j]=0;}
        search(i, 0, -1); //搜索翻这么多棋子的所有情况
        if(answer < INF) break; //有答案就不用搜了
    }
    
    if(answer == INF)
        cout<<"Impossible"<<endl;
    else
        cout<<answer<<endl;
    return 0;
}

void flip()
{
    int x, y;
        for(int i = 0; i < 16; ++i)
         {
             if(visit[i]) //如果标记为 1，表示这个棋子要翻
             {
                 x = i/4; // 计算出棋子再棋盘中的位置
                 y = i%4;
                 
                 board[x][y] = -board[x][y]; //翻自己
                 
                 if ( (x-1)>=0 )
                 {
                     board[x-1][y] = -board[x-1][y]; //翻上
                 }
                 if ( (x+1)<=3 )
                 {
                     board[x+1][y] = -board[x+1][y]; //翻下
                 }
                 if ( (y-1)>=0 )
                 {
                     board[x][y-1] = -board[x][y-1]; //翻右
                 }
                 if ( (y+1)<=3 )
                 {
                     board[x][y+1] = -board[x][y+1]; //翻右
                 }
             }
         }//翻棋子
  
    return;
}

int judge()
{
    int x,y;;
    for (int i = 1; i < 16; ++i)
    {
        x = i/4;
        y = i%4;
        if (board[x][y] != board[0][0])//从第2个开始，当前这个不等于第1个
        {
            return 0;
        }
    }
    return 1;
}

void search(int totalNum, int doneNum, int pre)//要翻的个数，已翻的个数，之前翻的是第几个
{
    if(answer < INF)
        return;
    
         if(doneNum == totalNum) //当翻棋的数量达到了，就进行判断
         {
             flip(); //翻棋
             if(judge()) //判断全为同一种颜色
                 answer = totalNum;    //记录答案
             else
                 flip(); //否则将棋盘恢复原状
             return;
         }
    
         for(int i = pre+1; i < 16; ++i) //从上一个翻的棋子的下一个开始选择，这样可以防止出现重复的情况
         {
             visit[i] = 1;//选中的标记为 1
             search(totalNum, doneNum+1, i); //搜索翻下一个的情况，
             visit[i] = 0; //清除标记
         }
}