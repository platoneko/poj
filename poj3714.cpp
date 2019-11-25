/*
Raid

Description
After successive failures in the battles against the Union, the Empire
retreated to its last stronghold. Depending on its powerful defense system,
the Empire repelled the six waves of Union's attack. After several sleepless
nights of thinking, Arthur, General of the Union, noticed that the only
weakness of the defense system was its energy supply. The system was
charged by N nuclear power stations and breaking down any of them would
disable the system.
The general soon started a raid to the stations by N special agents who were
paradroped into the stronghold. Unfortunately they failed to land at the
expected positions due to the attack by the Empire Air Force. As an
experienced general, Arthur soon realized that he needed to rearrange the
plan. The first thing he wants to know now is that which agent is the nearest
to any power station. Could you, the chief officer, help the general to
calculate the minimum distance between an agent and a station?
Input
The first line is a integer T representing the number of test cases.
Each test case begins with an integer N (1 ≤ N ≤ 100000).
The next N lines describe the positions of the stations. Each line consists of
two integers X (0 ≤ X ≤ 1000000000) and Y (0 ≤ Y ≤ 1000000000) indicating
the positions of the station.
The next following N lines describe the positions of the agents. Each line
consists of two integers X (0 ≤ X ≤ 1000000000) and Y (0 ≤ Y ≤ 1000000000)
indicating the positions of the agent.
Output
For each test case output the minimum distance with precision of three
decimal placed in a separate line.
Sample Input
2 4
0 0
0 1
1 0
1 1
2 2
2 3
3 2
3 3
4
0 0
0 0
0 0
0 0
0 0
0 0
0 0
0 0
Sample Output
1.414
0.000
*/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#define INF 1e32
using namespace std;

void solution();
inline double getDist(double ax, double ay, double bx, double by) {
    return sqrt(pow(ax-bx, 2) + pow(ay-by, 2));
}
struct Point {
    int x;
    int y;
    bool agent;
};
double minDist(int left, int right, Point *points);
bool comparePoint(const Point &a, const Point &b) {
    if (a.x > b.x) return true;
    else if (a.x == b.x) return a.y > b.y;
    else return false;
}

int main() {
    int rnd;
    scanf("%d", &rnd);
    for (int i = 0; i < rnd; ++i) {
        solution();
    }
    return 0;
}

void solution() {
    int n;
    scanf("%d", &n);
    Point points[n<<1];
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &points[i].x, &points[i].y);
        points[i].agent = false;
    }
    for (int i = n; i < n<<1; ++i) {
        scanf("%d%d", &points[i].x, &points[i].y);
        points[i].agent = true;
    }
    sort(points, points+(n<<1), comparePoint);
    double dist = minDist(0, n<<1, points);
    printf("%.3f\n", dist);
}

double minDist(int left, int right, Point *points) {
    if (right-left == 2) {
        if (points[left].agent ^ points[left+1].agent) {
            return getDist(points[left].x, points[left].y, points[left+1].x, points[left+1].y);
        } else {
            return INF;
        }
    }
    if (right - left == 3) {
        double dist1 = INF, dist2 = INF, dist3 = INF;
        if (points[left].agent ^ points[left+1].agent) {
            dist1 = getDist(points[left].x, points[left].y, points[left+1].x, points[left+1].y);
        }
        if (points[left+1].agent ^ points[left+2].agent) {
            dist2 = getDist(points[left+1].x, points[left+1].y, points[left+2].x, points[left+2].y);
        }
        if (points[left].agent ^ points[left+2].agent) {
            dist3 = getDist(points[left].x, points[left].y, points[left+2].x, points[left+2].y);
        }
        return dist1 < dist2 ? (dist1 < dist3 ? dist1 : dist3) : (dist2 < dist3 ? dist2 : dist3);
    }
    int mid = (left+right)>>1;
    double dist, midDist;
    double leftDist = minDist(left, mid, points);
    double rightDist = minDist(mid, right, points);
    dist = min(leftDist, rightDist);
    int candLeft = mid-1, candRight = mid+1;
    while (candRight < right) {
        if (abs(points[candRight].x - points[mid].x) >= dist)
            break;
        ++candRight;
    }
    while (candLeft >= left) {
        if (abs(points[candRight].x - points[mid].x) >= dist)
            break;
        --candLeft;
    }
    ++candLeft;
    for (int i = candLeft; i < mid; ++i) {
        for (int j = mid; j < candRight; ++j) {
            double tmp = INF;
            if (points[i].agent ^ points[j].agent) {
                tmp = getDist(points[i].x, points[i].y, points[j].x, points[j].y);
            }
            dist = min(tmp, dist);
        }
    }
    return dist;
}
