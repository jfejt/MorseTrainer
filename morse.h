
using namespace std;

//translater between ascii characters and morse code patterns

class alphabet{
    public:
        alphabet(char* filename); //constructor that takes reference file as parameter, and uses that to initlize the reference table
        int translate(char); //translates character into morse code pattern
        int getLength(char); //translates character into length of morse code pattern (i.e _.. woudl be 3, ..._. would be 5)
    private:
        int ditdah(char*,int*); //takes input string of _ and ., and outpust binary representation of morse code that can be read by sound processor, and outputs lenght indirectly with input int*
        int length[128]; //reference table of binary lengths of tranlated morse code characters
        int array[128]; //reference table of binary representations of traslated morse code characters
};


