#ifndef RIGIBODY_
#define RIGIBODY_

//#include <string>
#include "AComponent.h"

namespace XDGameEngine
{
    class Rigibody : public XDGameEngine::AComponent
    {
    protected:
        uint32_t m_id = 'RGBD';

    private:

    public:
        Rigibody();
        ~Rigibody();

        void printTruc();
        int intest = 0;
        void printIntest()
        {
            std::cout << "Rigibody test = " << intest << std::endl;
        }
    };
}

#endif