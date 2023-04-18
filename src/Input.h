#ifndef INPUT_
#define INPUT_

//#include <string>
#include "AComponent.h"

namespace XDGameEngine
{
    class Input : public XDGameEngine::AComponent
    {
    private:
        //static Input instance_;

    public:
        Input();
        ~Input();

        void printTruc();
        int intest = 0;
        void printIntest()
        {
            std::cout << "int test = " << intest << std::endl;
        }
        //bool getKeyPressed(std::string key);
        //bool getKeyUp(std::string key);
        //static Input& instance() { return instance_; }
    };
}

#endif