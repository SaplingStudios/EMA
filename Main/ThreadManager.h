#ifndef SIM_MANAGER
#define SIM_MANAGER 1

#include "dataStructure.h"

#include <chrono>  /*Timing*/
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadManager
{
public:
    ThreadManager(Bin& bin);

    void startGraphics( void (*graphics)(const Bin* const, const ThreadManager* const) ) const;

    void startUpdatingMap();

    unsigned int getResolution() const;

    unsigned int getTick() const;

    void setSpeed(const unsigned int newSpeed);

    unsigned int getSpeed() const;

private:
    //Helper functions to allow these to be seperate threads
    void continueUpdatingMap();
    void map();
    void entities();

    Bin* bin;
    unsigned int resolution = 1;  //how fine we is calculating
    unsigned long long int tick = 0; //the time, in seconds, of the game
    unsigned int speed = 1;  //The fast forwarding capability
    std::chrono::system_clock::time_point t1, t2;

    //Lock stuff - for syncronization:
    std::mutex originalLock;
    std::condition_variable sync;
    bool ready = false;
    volatile bool mapBool = false;
    volatile bool entBool = false;
};

#endif