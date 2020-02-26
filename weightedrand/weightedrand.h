

using namespac std;

class node;

class weightedRand(){
    public:
        weightedRand();
        weightedRand(int);
        ~weightedRand();
        void promote(char,int);
        bool add(char);
        bool remove(char);
        bool exists(char);
        int getWeight(char);
        void setMin(int);
    private:
        node* head;
        int value;
        int min;
};      

class node{
    public:
        node();
        node(char);
        ~node();
    private:
        int value;
        int subvalue;
        char charecter;
        node* left;
        node* right;
        friend class weightedRand;
};

