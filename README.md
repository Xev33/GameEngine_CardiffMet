# README #

### Project summary ###

The project has been made in 2 weeks.
Here is the game engine I produced for the eponymous module in the "Computer Game Design & Development" section of Cardiff Metropolitan University during the year I spent in Cardiff Wales.
This engine uses "Ogre3D" as 3D rendering engine and "Bullet physics" as physics engine.

The project has been submitted alongside with a Doxygen documentation and a written document summarising the game engine's architecture.

### Academic assessment ###

It has been asked to produce a document recaping how the game engine has been designed.

Here is the [PDF document file.](https://github.com/Xev33/GameEngine_CardiffMet/files/11746559/st20242612_CIS5012_PRAC1.pdf)

# Recap #
This game engine is an encapsulation of three main code sections:

[active]:https://img.shields.io/badge/-Active-success
[depreciated]:https://img.shields.io/badge/-Depreciated-inactive
[updating]:https://img.shields.io/badge/-Updating-purple
[passing]:https://img.shields.io/badge/-Passing-success
[outdated]:https://img.shields.io/badge/-Outdated-blue
[dev]:https://img.shields.io/badge/-Unreleased-important

[version-1.0.0]:https://img.shields.io/badge/Ver.-1.0.0-ff69b4
[version-1.0.1]:https://img.shields.io/badge/Ver.-1.0.1-ff69b4
[version-1.0.2]:https://img.shields.io/badge/Ver.-1.0.2-ff69b4
[version-1.0.3]:https://img.shields.io/badge/Ver.-1.0.3-ff69b4
[version-1.0.4]:https://img.shields.io/badge/Ver.-1.0.4-ff69b4
[version-1.0.5]:https://img.shields.io/badge/Ver.-1.0.5-ff69b4
[version-dev]:https://img.shields.io/badge/Ver.-dev-important

|**Part's name**|**Goal**|**Description**|
|:------:|:------:|:-------------:|
| [Ogre3D](https://www.ogre3d.org/) |Graphic rendering| Ogre3D is a scene-oriented, flexible 3D engine written in C++ designed to make it easier and more intuitive for developers to produce applications utilising hardware-accelerated 3D graphics.|
| [Bullet](https://github.com/bulletphysics/bullet3) |Physics simulation|Bullet is a physics engine which simulates collision detection as well as soft and rigid body dynamics.|
| XDGameEngine |Provides a component based library to use|This part encapsulates the two other APIs and use it to create and provide a **component based** programing library to whomever want to use it.|

# My architecture #

### Component ###

A component is a behaviour. In the game engine, it is represented by the Abstract Class **AComponent**. It can inherit from both Ogre3D (via the scene manager) and Bullet. (via the Dynamic world)

Here is how the component is structured in the game engine:
![GameEngineComponent](https://github.com/Xev33/GameEngine_CardiffMet/assets/106018428/ac1b55e0-dff3-4190-acda-875308f2be03)

### Game object ###

The gameobject class is a container of AComponent smart pointers. It has a vector of AComponent unique_ptr. (std::vector<std::unique_ptr<AComponent>> m_components)

The gameobject has the same type of functions as unity.
It can:
- Add a component
- Remove a component
- Get a component

It has an Update method AND an “UpdateComponents” method as well
(we don’t always want an object to update its components. For instance: A static mesh won’t have to move its mesh and therefore doesn’t need the component to be updated since the scene manager is updated elsewhere and is not from the component)

Here is the diagram:
  
![GameEngineGameObject](https://github.com/Xev33/GameEngine_CardiffMet/assets/106018428/dc2f334a-d0ce-4401-a2d2-852a97f14aa5)

### Final architecture ###
  
  This diagram recap how the overall architecture has been implemented:
  
  ![GameEngineDiagram](https://github.com/Xev33/GameEngine_CardiffMet/assets/106018428/4fc4ad7c-c2bf-45d2-8841-800f2b8d66db)


# Doxygen documentation: #

To see the entire code documentation:

* just go to the following folder: ```Doxygen/html```
* Search for a file named “index.html” 
* Double click on it 
* If asked: Select your internet navigator 
* Done! You should now have all our class attributes and methods with some inheritance trees.
  
  # Acknowledgments #
  I would like to thank the [Computer Games Design & Development](https://www.cardiffmet.ac.uk/technologies/courses/Pages/Computer-Games-Design-and-Development-BSc-(Hons).aspx) head of section: Glenn Jenckins for his exciting and informative lectures and tutorial materials throughout my time at Cardiff Metropolitan University.
