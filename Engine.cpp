#include "framework.h"
#include "Settings.h"
#include "EngineBase.h"
#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Logic(double elapsedTime)
{
    EngineBase::Logic(elapsedTime);

    // This is the logic part of the engine. Add your game logic here.
    // It runs every frame and it receives the elapsed time between the last frame and this one, in seconds.
    // Use this value for a smooth and consistent movement, regardless of the CPU or graphics speed


}