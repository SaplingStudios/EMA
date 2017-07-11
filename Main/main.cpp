// "Walk Of Life" Data Structure Test
//Only ever include the data structure - insures only registered plugins work
#include "dataStructure.h"
#include "ThreadManager.h"
#include <random>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

void init(Bin& bin, ostream& os = cout);
void graphics(const Bin* const bin, const ThreadManager* const manager);

int main()
{
    //Create Bin
    Bin bin(500, 500, 50);

    init(bin); //Initialize the content of the bin

    //This is the multithreading a thread for each for
     //updating the hexes
     //updating the entities
     //Timing the update cycle and adjusting resolution
    ThreadManager manager(bin);

    //Start drawing the screen, in a seperate thread
    manager.startGraphics(&graphics);

    //Will "endlessly" update the map (spawns and updates the described threads)
    manager.startUpdatingMap();

    char command;
    cin >> command;
}


void init(Bin& bin, ostream& os)
{
    os << "INIT: Initializing Map...\n";

    //Random number stuff
    random_device seed;
    mt19937 gen(seed());

    //Make two generators for generating entities in random locations
    uniform_real_distribution<double> randRangeWidth (0.0, bin.getWidth() );
    uniform_real_distribution<double> randRangeHeight(0.0, bin.getHeight());

    os << "INIT: Generating 10 flowers\n";
    for(int numOfNodes = 0; numOfNodes < 10; ++numOfNodes)
    {
        bin.insert(new Flower(randRangeWidth(gen), randRangeHeight(gen)));
    }
    os << "INIT: Generating 10 dogs\n";
    for(int numOfNodes = 0; numOfNodes < 10; ++numOfNodes)
    {
        bin.insert(new Dog(randRangeWidth(gen), randRangeHeight(gen)));
    }

    os << "INIT: Done!\n\n";
}

void graphics(const Bin* const bin, const ThreadManager* const manager)
{
    string spin = "|\\-/";
    while (1)
        for (int i = 0; i < 4; ++i)
        {
            //Build print statement
            ostringstream output;
            output << "Resolution: " << manager->getResolution();
            output << "; Speed: " << manager->getSpeed();
            output << "; Tick Count: " << manager->getTick() << " " << spin[i];

            //Print it
            cout << output.str();
            cout.flush();

            //Delay for the spinner
            for(double delay = 0; delay <= 40000000; ++delay) {}

            //Refreash/clear screen
            for (size_t t = 0; t < output.str().size(); ++t)
                cout << "\b"; //clear last character

            //Just to remove the compiler warning for unused vars
            output << bin->getWidth();
        }
}
