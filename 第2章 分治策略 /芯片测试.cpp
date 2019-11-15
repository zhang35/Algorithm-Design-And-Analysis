#include <list>
#include <iostream>
using namespace std;

struct Chip{
    int label;
    int state;
};

int ChipTestChip(list<Chip>::iterator host, list<Chip>::iterator guest);
int ChipTest(list<Chip> &chips);

int main()
{
    cout << "input number of chips:" << endl;
    int n;
    cin >> n;
    list<Chip> chips(n);
    list<Chip>::iterator it;
    int i=0;
    cout << "input "<< n << " states: 0->bad; 1->good" << endl;
    for (it=chips.begin(); it!=chips.end(); it++) {
        it->label = i+1;
        i++;
        cin >> it->state;
    }
    cout << ChipTest(chips) << endl;
    return 0;
}

//2.3 芯片测试
//重要结论1：若半数（含）以上芯片显示某芯片为好的，则它一定是好的；
//因为好的占半数以上，如果是坏的会有半数以上显示其为坏的。
//重要结论2：两两测试，如果均为好的（都好或都坏），则任丢一个；否则（至少有一个坏的）全丢掉
//这样可以保证每次至少丢一个，且不同时丢掉两个好的；保证剩下的仍然好的占半数以上
int ChipTestChip(list<Chip>::iterator host, list<Chip>::iterator guest){
    if (host->state==1){
        return guest->state;
    }
    else{
        return rand()%2;
    }
}
int ChipTest(list<Chip> &chips){
    unsigned long n = chips.size();
    if (n<3){
        return chips.begin()->label;
    }
    list<Chip>::iterator it1;
    list<Chip>::iterator it2;
    if (n==3){
        it1 = chips.begin();
        it2 = chips.begin();
        it2++;
        if (ChipTestChip(it1, it2) & ChipTestChip(it2, it1)){
            return it1->label;
        }
        else{
            return chips.end()->label;
        }
    }
    //当n为奇数时，单独判断轮空的最后一个,参考关键结论1
    //是好的，则结束；是坏的，则去掉
    if (n%2!=0){
        it1 = chips.begin();
        it2 = chips.end();
        int count = 0;
        for (int i=0; i<n-1; i++) {
            count += ChipTestChip(it1, it2);
            it1++;
        }
        if (count >= n/2){
            return it2->label;
        }
        else{
           cout << "pop :" << it2->label << endl;
           chips.pop_back();
           n--;
        }
    }
    
    //相邻的两个为一组，从头到尾测试
    it1 = chips.begin();
    for (int i=0; i<n/2; i++){
        it2 = it1;
        it2++;
        //两个都好或都坏, 丢掉后面那个
           cout << "testing " << it1->label << " <-> " << it2->label;
            int r1 = ChipTestChip(it1, it2);
            int r2 = ChipTestChip(it2, it1);
            cout << " result: " << r1 << " " << r2 << endl;
        if (r1 & r2){
           cout << "pop :" << it2->label << endl;
           it1 ++;
           it1 ++;
           chips.erase(it2);
        }
        //否则全丢掉
        else {
            cout << "pop: " << it1->label << " & " << it2->label << endl;
            it2++;
            chips.erase(it1, it2); //erase作用范围为[first,last)
            it1 = it2;
        }
    }
    //递归处理剩下的
    return ChipTest(chips);
}


