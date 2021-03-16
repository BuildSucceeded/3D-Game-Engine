#include "framework.h"
#include "Settings.h"
#include "EngineBase.h"
#include "Engine.h"
#include "Cube.h"

Engine::Engine()
{
    Light* ambientLight = new Light(ambiental, Point3D::Create(0, 0, 0), Point3D::Create(0, 0, 0), ColorUnion::Create(63, 63, 63, 255));
    AddLight(ambientLight);

    Cube* cube = new Cube();
    AddGameObject(cube);
}

Engine::~Engine()
{
}

void Engine::KeyDown(WPARAM wParam)
{
    EngineBase::KeyDown(wParam);

    // Add keys handling below

}

void Engine::KeyUp(WPARAM wParam)
{
    EngineBase::KeyUp(wParam);

    // Add keys handling below

}

void Engine::Logic(double elapsedTime)
{
    EngineBase::Logic(elapsedTime);

    // This is the logic part of the engine. Add your game logic here.
    // It runs every frame and it receives the elapsed time between the last frame and this one, in seconds.
    // Use this value for a smooth and consistent movement, regardless of the CPU or graphics speed


}