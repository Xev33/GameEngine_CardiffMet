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

        /**
        * Key States
        */
        bool aDown, wDown, fDown, jDown, dDown;

        Input(); // Private constructor to prevent instantiation
        Input(const Input&) = delete; // Delete copy constructor
        Input& operator=(const Input&) = delete; // Delete assignment operator

    public:
        ~Input();

        /**
        * Method to update all inputs if it has been pressed
        */
        void InputPressed(const OgreBites::KeyboardEvent& evt) noexcept;

        /**
        * Method to update all inputs if it has been released
        */
        void InputReleased(const OgreBites::KeyboardEvent& evt) noexcept;

        /**
        * The method to call for any class to know about an input state
        */
        bool GetKeyDown(const char* key) const noexcept;

        /**
        * The singleton instance getter
        */
        static Input& Instance() noexcept
        {
            static Input instance;
            return instance;
        }
    };
}

#endif