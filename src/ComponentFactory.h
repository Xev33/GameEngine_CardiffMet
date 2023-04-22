#ifndef COMPONENT_FACTORY_
#define COMPONENT_FACTORY_

#include <iostream>
#include <memory>

/* Forward declaration for the Input */
namespace XDGameEngine
{
    class AComponent;
    class GameObject;
}

namespace XDGameEngine
{
    /**
    * This class must create all components for a gameobject
    */
    class ComponentFactory
    {
    private:

    public:
        ComponentFactory();
        ~ComponentFactory();

        /**
        * Static method to allow any gameobject to create and have their component
        */
        static std::unique_ptr<XDGameEngine::AComponent> CreateComponent(uint32_t componentType, GameObject& go);

    };
}

#endif