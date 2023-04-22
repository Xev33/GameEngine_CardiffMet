#ifndef INPUT_
#define INPUT_

//#include <string>
#include "AComponent.h"
#include "OgreInput.h"
#include <string>

namespace XDGameEngine
{
    class Input
    {
    protected:
    private:
        //static Input instance_;

        /**
        * Key States
        *
        */
        bool aDown, wDown, fDown, jDown, dDown;

        Input(); // Private constructor to prevent instantiation
        Input(const Input&) = delete; // Delete copy constructor
        Input& operator=(const Input&) = delete; // Delete assignment operator

    public:
        ~Input();

        void InputPressed(const OgreBites::KeyboardEvent& evt) noexcept;
        void InputReleased(const OgreBites::KeyboardEvent& evt) noexcept;

        bool GetKeyDown(const char* key) const noexcept;

        //static Input& Instance() { return instance_; }

        static Input& Instance() {
            static Input instance;
            return instance;
        }

        void DoSomething() {
            // Implementation of DoSomething...
        }



    };
}

#endif