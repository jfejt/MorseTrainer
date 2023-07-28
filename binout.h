#include<iostream>
#include<ncurses/ncurses.h>
using namespace std;

//print binary representations of int to console
void printbin(int input) {
    int i;
    int s=sizeof(int)*4;
    for (i=0;i<=s;i++) {
        cout << ((input&(1<<i))>>i);
    }
    cout <<endl;
}


void printwbin(int input) {
    int i;
    int s=sizeof(int)*4;
    for (i=0;i<=s;i++) {
        printw("%i",((input&(1<<i))>>i));
    }
    return;
}
