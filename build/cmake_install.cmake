# Install script for directory: D:/Cardiff Courses/03_GameEngine/GameEngine_Repo_XavierDavid

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Cardiff Courses/03_GameEngine/GameEngine_Repo_XavierDavid/build/dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/./" TYPE DIRECTORY FILES "D:/Cardiff Courses/03_GameEngine/GameEngine_Repo_XavierDavid/dist/media")
  endif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES "D:/Cardiff Courses/03_GameEngine/GameEngine_Repo_XavierDavid/dist/bin/resources.cfg")
  endif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE RENAME "resources.cfg" FILES "D:/Cardiff Courses/03_GameEngine/GameEngine_Repo_XavierDavid/dist/bin/resources_d.cfg")
  endif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Codec_Assimp.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Codec_STBI.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/DefaultSamples.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreBites.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreBullet.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreMain.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreMeshLodGenerator.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreOverlay.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgrePaging.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreProperty.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreRTShaderSystem.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreTerrain.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/OgreVolume.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Plugin_BSPSceneManager.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Plugin_DotScene.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Plugin_OctreeSceneManager.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Plugin_OctreeZone.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Plugin_PCZSceneManager.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/Plugin_ParticleFX.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/RenderSystem_Direct3D11.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/RenderSystem_GL.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/RenderSystem_GL3Plus.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/RenderSystem_GLES2.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/SDL2.dll"
      "D:/Cardiff Courses/03_GameEngine/ogre/build/sdk/bin/zlib.dll"
      )
  endif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee]|[Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo]|[Dd][Ee][Bb][Uu][Gg])$")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Cardiff Courses/03_GameEngine/GameEngine_Repo_XavierDavid/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
