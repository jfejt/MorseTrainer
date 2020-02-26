#include<portaudio.h>
#include<ncurses.h>

typedef struct
{
    int sine[100];
    int phase;
    int pattern;
    int length;
    int frames;
    int lastframe;
    int framesperunit;
} morseData; //struct of paramaters for output audio wave.

//callback function that is sent to portaudio in order to generate a sound wave
static int morseCallback(const void*,void*,unsigned long,const PaStreamCallbackTimeInfo*,PaStreamCallbackFlags,void*);

class player
{
    public:
        player(int); //init portaudio
        ~player();
		bool play(int pattern, int length); //play morse code of pattern, with duration of length
        void clear(); //reset portaudio buffers
        int getErrorCode(); //retrieve error codes from portaudio
        const char* getErrorText(); //retrieve error text from portaudio
        void reinit(); //reinitilize portaudio
        void DEBUGprintdata();  //prints all paramaters to console
    private:
        int errorcode;
        int unitLength;
        morseData playerdata;
        const PaDeviceInfo* outdeviceinfo;
        PaStreamParameters outputParameters;
};
