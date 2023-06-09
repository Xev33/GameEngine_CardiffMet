# GAME ENGINE USING OGRE AND BULLET
# Xavier DAVID
# 2022-2023
#
# Originally based on the Official Ogre Tutorials 
# (Tutorial Framework) http://www.ogre3d.org/tikiwiki/ 
# heavily modified for CMU students - CIS5012. 

# Set the Executable name. 
set(APP "GameEngine_XavierDAVID")

project(${APP})

cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)


set(HDRS
	./src/Game.h
	./src/Player.h
	./src/Cube.h
	./src/NPC.h
	./src/AComponent.h
	./src/CollisionShape.h
	./src/Scene.h
	./src/Input.h
	./src/MeshRenderer.h
	./src/ComponentFactory.h
	./src/TriggerZone.h
	./src/GameObject.h
	./src/Transform.h
	./src/Rigibodies.h
	./src/Light.h
)

set(SRCS
	./src/Game.cpp
	./src/Player.cpp
	./src/Cube.cpp
	./src/NPC.cpp
	./src/main.cpp
	./src/Scene.cpp
	./src/Input.cpp
	./src/MeshRenderer.cpp
	./src/ComponentFactory.cpp
	./src/CollisionShape.cpp
	./src/TriggerZone.cpp
	./src/GameObject.cpp
	./src/Transform.cpp
	./src/Rigibodies.cpp
	./src/Light.cpp
)

include("tools/cmake/common.cmake")

# As of Ogre 1.13 Bullet is a plugin, so as long as
# its found by CMake we've nothing else to do. 

include("tools/cmake/bulletBase.cmake")

include("tools/cmake/ogreBase.cmake")


