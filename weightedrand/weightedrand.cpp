#include<weightedrand.h>

using namespace std;

char max(char a,char b){
    return a>b?a:b;
}

weightedRand::weightedRand():head(NULL),value(0),min(1);

weightedRand::weightedRand(int newMin):head(NULL),value(0),min(newMin);

weightedRand::~weightedRand(){
    if (head!=NULL)
        delete head;
    return;
}

void weightedRand::promote(char,int){
    return;
}

bool weightedRand::add(char c){
    if (head == NULL){
        head = new node(c);
        return true;
    }
    temp = new node(c);
    current = head;


    if (temp->value > temp->value){


    
    return retval;
    }

bool weightedRand::remove(char c){
    return retval;
}

bool weightedRand::exists(char c){
    return retval;
}

int weightedRand::getWeighted(char c){
    return retval;
}

void weightedRand::setMin(int i){
    min = i;
    return;
}


