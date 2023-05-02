#include "Input.h"
#include <iostream>
#include "OgreInput.h"

namespace XDGameEngine
{
    Input::Input()
    {
        std::cout << " INPUTMANAGER CREATED\n";
        aDown = dDown = wDown = fDown = jDown = sDown =
            spaceDown = leftArrowDown = rightArrowDown = false;
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
        else if (std::strcmp(key, "s") == 0)
            return sDown;
        else if (std::strcmp(key, "space") == 0)
            return spaceDown;
        else if (std::strcmp(key, "leftArrow") == 0)
            return leftArrowDown;
        else if (std::strcmp(key, "rightArrow") == 0)
            return rightArrowDown;
        else
            return false;
    }

	void Input::InputPressed(const OgreBites::KeyboardEvent& evt) noexcept
	{
        if (evt.keysym.sym == 'w')
        {
            wDown = true;
        }

        if (evt.keysym.sym == 's')
        {
            sDown = true;
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

        if (evt.keysym.sym == SDLK_SPACE)
        {
            spaceDown = true;
        }

        if (evt.keysym.sym == SDLK_LEFT)
        {
            leftArrowDown = true;
        }

        if (evt.keysym.sym == SDLK_RIGHT)
        {
            rightArrowDown = true;
        }

	}

	void Input::InputReleased(const OgreBites::KeyboardEvent& evt) noexcept
	{
        if (evt.keysym.sym == 'w')
        {
            wDown = false;
        }

        if (evt.keysym.sym == 's')
        {
            sDown = false;
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

        if (evt.keysym.sym == SDLK_SPACE)
        {
            spaceDown = false;
        }

        if (evt.keysym.sym == SDLK_LEFT)
        {
            leftArrowDown = false;
        }

        if (evt.keysym.sym == SDLK_RIGHT)
        {
            rightArrowDown = false;
        }

	}
}