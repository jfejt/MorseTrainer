#include<ncurses.h>
#include"morse.h"
#include"player.h"
#include"binout.h"
#include<ctime>                  //rand seed
#include<cstdlib>                //rand
#include<unistd.h>               //sleep function

using namespace std;

int main() {
	//ncurses initilization
    initscr();
    noecho();
    scrollok(stdscr,TRUE);
    cbreak();
    srand(time(NULL));//seeding random number generator
    alphabet morse("letters.txt"); //load morse code characters
    player output(60); //init morse code audio with time unit of 60
    char ch,input;
	//while loop will generate a random morse character, print the pattern, play it, and wait for user to 
    while (1) {
        ch = (int)(rand()%26+97); //gererate random character
        printwbin(morse.translate(ch)); //translate character into morse code pattern, and print the pattern
        printw(" ");
        refresh();
        replay: // hack to play audio again if the user presses space
        output.play(morse.translate(ch),morse.getLength(ch)); //play morse code audio
        if (output.getErrorCode()!=0) {//error handling
            printw("ERROR: %s\n",output.getErrorText());
            const PaHostErrorInfo* hosterror = NULL;
            hosterror=Pa_GetLastHostErrorInfo();
            printw("HostID: %i\nHostErrorCode: %i\nErrorText: %s\n",
                hosterror->hostApiType,
                hosterror->errorCode,
                hosterror->errorText);
            refresh();
        }
        output.clear();//reset audio buffers
        input=getch(); //get user keypress
        if (input==ch)
            printw("CORRECT %c\n",ch);
        else if(input==' ')
            goto replay;
        else
            printw("WRONG %c - %c\n",input,ch);
        refresh(); //refresh the console window
    }
}
