#include <iostream>
#include <math.h>
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;

struct Point{
    float x;
    float y;
    int label;
};

float MinDistance(Point *P, int l, int r);

int main()
{
    int n = 4;
    Point points[] = {{0.5, 2}, {2, 3}, {-2, 4}, {1, -1}};
    for (int i=0; i<n; i++){
       points[i].label = i; 
    }
    cout << "Points: " << endl;
    for (int i=0; i<n; i++){
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;
    }
    float minDistance = MinDistance(points, 0, n-1);
    cout << "min distance is :" << minDistance << endl;
    return 0;
}
//按照横坐标排序
int QuickSortPartitionByX(Point s[], int l, int r){
    Point temp = s[l];
    while (l < r)
    {
        while(l < r && s[r].x >= temp.x)
            r--;
        if(l < r)
            s[l++] = s[r]; //直接替换掉最左元素（已在temp中存有备份）
        while(l < r && s[l].x <= temp.x)
            l++;
        if(l < r)
            s[r--] = s[l];
    }
    s[l] = temp;  //l的位置放了temp，所以其左侧都小于temp，右侧都大于temp
    return l;
}
void QuickSortByX(Point s[], int l, int r)
{
    if (l>=r){
        return;
    }
    int i = QuickSortPartitionByX(s, l, r);
    QuickSortByX(s, l, i - 1);
    QuickSortByX(s, i + 1, r);
}

//按照纵坐标排序
int QuickSortPartitionByY(Point s[], int l, int r){
    Point temp = s[l];
    while (l < r)
    {
        while(l < r && s[r].y >= temp.y)
            r--;
        if(l < r)
            s[l++] = s[r]; //直接替换掉最左元素（已在temp中存有备份）
        while(l < r && s[l].y <= temp.y)
            l++;
        if(l < r)
            s[r--] = s[l];
    }
    s[l] = temp;  //l的位置放了temp，所以其左侧都小于temp，右侧都大于temp
    return l;
}
void QuickSortByY(Point s[], int l, int r)
{
    if (l>=r){
        return;
    }
    int i = QuickSortPartitionByY(s, l, r);
    QuickSortByY(s, l, i - 1);
    QuickSortByY(s, i + 1, r);
}

float Distance(Point p1, Point p2){
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2));
}

float MinDistanceRecur(Point *PX, int l, int r, Point *PY, int totalNum){
    int n = r - l + 1;
    float delta = numeric_limits<float>::max(); //delta设为最大的float, 需要#include<limits>
    if (n<2){
        return delta;  //此处取最大值，即仅剩1个点时不再更新最短距离
    }
    if (n<=3){
        for (int i=l; i<=r; i++) {
            for (int j=i+1; j<=r; j++) {
                delta = min(Distance(PX[i], PX[j]), delta);
            }
        }
        return delta;
    }
    //将P近似划分为大小相等的两部分，递归求各自最近点距
    float minLeft = MinDistanceRecur(PX, l, n/2, PY, n);
    float minRight = MinDistanceRecur(PX, n/2+1, r, PY, n);
    delta = min(minLeft, minRight);

    //求跨边界区域最近点距,找出边界线mid左右delta范围内窄缝中的点
    float mid = (PX[n/2].x + PX[n/2+1].x) / 2;
    vector<int> leftStripPoints;
    vector<int> rightStripPoints;
    for (int i=n/2; (mid-PX[i].x)<delta && i>=l; i--){
        leftStripPoints.push_back(PX[i].label);
    }
    for (int i=n/2+1; (PX[i].x-mid)<delta && i<=r; i++){
        rightStripPoints.push_back(PX[i].label);
    }

    //按y坐标轴从大到小扫描，此处开始使用PY
    for (int i=totalNum-1; i>=0; i--) {
        //如果某点落在了右半边窄缝
        if (find(rightStripPoints.begin(), rightStripPoints.end(), PY[i].label)!=rightStripPoints.end()){
            //检查纵坐标比其小delta之内，且落在左半边的点，更新最短距离
            for (int j=i-1; (j>=0 && (PY[i].y-PY[j].y)<delta && 
                        (find(leftStripPoints.begin(), leftStripPoints.end(), PY[j].label)!=leftStripPoints.end())); j--){
                delta = min(delta, Distance(PY[i], PY[j]));
            }
        }
        //如果某点落在了左半边窄缝
        if (find(leftStripPoints.begin(), leftStripPoints.end(), PY[i].label)!=leftStripPoints.end()){
            //检查纵坐标比其小delta之内，且落在右半边的点，更新最短距离
            for (int j=i-1; (j>=0 && (PY[i].y-PY[j].y)<delta && 
                        (find(rightStripPoints.begin(), rightStripPoints.end(), PY[j].label)!=rightStripPoints.end())); j--){
                delta = min(delta, Distance(PY[i], PY[j]));
            }
        }
    }
    return delta;
}
float MinDistance(Point *P, int l, int r){
    //预处理，复制出来两份数据，分别按x、y坐标排序，可将复杂度降到O(nlogn)
    //如果每次递归都进行排序，复杂度将是O(n(logn)^2)
    int totalNum = r - l + 1;
    Point *PX = new Point[totalNum ];
    memcpy(PX, P, totalNum *sizeof(Point));
    Point *PY = new Point[totalNum ];
    memcpy(PY, P, totalNum *sizeof(Point));
    float minDistance = MinDistanceRecur(PX, l, r, PY, totalNum);
    delete[] PX;
    delete[] PY;
    return minDistance;
  }
