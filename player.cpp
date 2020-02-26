#include"player.h"
#include<cmath>
#include<cstddef>
using namespace std;

//callback function sent to PortAudio library; modulates a sine wave based on binary represenatation of morse code data (1 is on, 0 is off)
static int morseCallback(
const void* inputBuffer,
void* outputBuffer,
unsigned long framecount,
const PaStreamCallbackTimeInfo* timeInfo,
PaStreamCallbackFlags statusFlags,
void* userData) {
    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;
    morseData* streamData=(morseData*)userData;
    int* buffer=(int*)outputBuffer;
    int i;
    int j;
    for (i=0;i<framecount;i++) {
        if ((streamData->frames)%(streamData->framesperunit)==((streamData->framesperunit)-1))
            streamData->pattern=streamData->pattern>>1;
        j= streamData->sine[streamData->phase]*(streamData->pattern&1);
        *buffer++=j;
        *buffer++=j;
        streamData->phase+=2;
        streamData->frames++;
        if (streamData->phase==100)
            streamData->phase=0;
    }
    return 0;
}

//inittilizes portaudio instance and sets a the time unit length (how long a dit (.) is. A dah (_) is always three time units long, and a pause between dits, and dahs are always one unit)
player::player(int init) {
    PaError error;
    //initialize PA
    error= Pa_Initialize();
    errorcode=(int)error;
    unitLength=init;
    int i;
    for (i=0;i<100;i++)
        playerdata.sine[i]=2147483647*sin( ((double)i/(double)100) * 3.14159 * 2.0 );
    outdeviceinfo=Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice());
    outputParameters.device = Pa_GetDefaultOutputDevice();
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paInt32;
    outputParameters.suggestedLatency = outdeviceinfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo= NULL;
    return;
}

//destroyse PortAudio instance
player::~player() {
    Pa_Terminate();
    return;
}

//takes binary representation of morse patern (and it's length), and send's it to PortAudio to generate the sound, using the callback defined above
bool player::play(int pattern,int length) {
    playerdata.phase=0;
    playerdata.pattern=pattern;
    playerdata.length=length;
    playerdata.frames=0;
    playerdata.framesperunit=(((outdeviceinfo->defaultSampleRate)/1000)*unitLength);
    playerdata.lastframe=playerdata.framesperunit*length;
    PaStream* stream;
    errorcode=Pa_OpenStream(
        &stream,
        NULL,
        &outputParameters,
        outdeviceinfo->defaultSampleRate,
        256,
        paNoFlag,
        morseCallback,
        &playerdata);
    if(errorcode!=paNoError)
        return false;
    errorcode=Pa_StartStream(stream);
    if(errorcode!=paNoError)
        return false;
    Pa_Sleep((length+2)*unitLength);
    errorcode=Pa_StopStream(stream);
    if(errorcode!=paNoError)
        return false;
    return true;
}

//resets port audio so that another sound can be played
void player::clear() {
    errorcode=paNoError;
    playerdata.phase=0;
    playerdata.pattern=0;
    playerdata.length=0;
    playerdata.frames=0;
    playerdata.lastframe=0;
    return;
}

//retrieve errorcode from portAudio
int player::getErrorCode() {
    return errorcode;
}

//retrieve error text from PortAudio
const char* player::getErrorText() {
    return Pa_GetErrorText(errorcode);
}

//print parameter values to the console (for debugging)
void player::DEBUGprintdata(){
    printw("phase: %i\n",playerdata.phase);
    printw("pattern: %i\n",playerdata.pattern);
    printw("length: %i\n", playerdata.length);
    printw("frames: %i\n", playerdata.frames);
    printw("lastframe: %i\n",playerdata.lastframe);
    printw("framesperunit: %i\n",playerdata.framesperunit);
    refresh();
}

//reinitilize PortAudio (so that we can recover from errors)
void player::reinit(){
    Pa_Terminate();
    PaError error;
    //initialize PA
    error= Pa_Initialize();
    errorcode=(int)error;
    return;
}

