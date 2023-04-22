#include "Input.h"
#include <iostream>
#include "OgreInput.h"

namespace XDGameEngine
{
    Input::Input() // Private constructor to prevent instantiation
    {
        std::cout << " INPUTMANAGER CREATED\n";
        aDown = dDown = wDown = fDown = jDown = false;
    }

	Input::~Input()
	{
		std::cout << " INPUTMANAGER DESTRUCTED\n";
	}

    bool Input::GetKeyDown(const char* key) const noexcept
    {
        if (std::strcmp(key, "w") == 0)
            return wDown;
        else if (std::strcmp(key, "a") == 0)
            return aDown;
        else if (std::strcmp(key, "d") == 0)
            return dDown;
        else if (std::strcmp(key, "j") == 0)
            return jDown;
        else if (std::strcmp(key, "f") == 0)
            return fDown;
        else
            return false;
    }

	void Input::InputPressed(const OgreBites::KeyboardEvent& evt) noexcept
	{
        if (evt.keysym.sym == 'w')
        {
            wDown = true;
        }

        if (evt.keysym.sym == 'a')
        {
            aDown = true;
        }

        if (evt.keysym.sym == 'd')
        {
            dDown = true;
        }

        if (evt.keysym.sym == 'j')
        {
            jDown = true;
        }

        if (evt.keysym.sym == 'f')
        {
            fDown = true;
        }
	}

	void Input::InputReleased(const OgreBites::KeyboardEvent& evt) noexcept
	{
        if (evt.keysym.sym == 'w')
        {
            wDown = false;
        }

        if (evt.keysym.sym == 'a')
        {
            aDown = false;
        }

        if (evt.keysym.sym == 'd')
        {
            dDown = false;
        }

        if (evt.keysym.sym == 'j')
        {
            jDown = false;
        }

        if (evt.keysym.sym == 'f')
        {
            fDown = false;
        }
	}
}