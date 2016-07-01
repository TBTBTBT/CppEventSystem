#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "EventSystem.hpp"

using namespace std;
using namespace Tabata;

EventManager<int,int> events;
EventManager<int> events2;
void Test(int i,int j) {
    cout << "abc" << i << j;

}
void Test2(int i,int j) {
    cout << "def" << i << j;
    
}
void Test3(int i,int j) {
    cout << "ghi" << i << j;
    
}
void Test4(int i,int j) {
    cout << "jkl" << i << j;
    
}
void Test2_1(int i) {
    cout << "ABC" << i;
    
}
int main(int argc, const char * argv[]) {
    events.AddListener("OnClick",&Test);
    events.AddListener("OnClick",&Test2);
    events.AddListener("OnAwake",&Test3);
    events.AddListener("OnAwake",&Test4);
    events.Invoke("OnAwake",3,2);// 出力は ghi12jkl12
   // events2.AddListener("On",&Test2_1);
   // events2.Invoke("On",1);
    
    return 0;
}
