#include "framework.h"
#include "Settings.h"
#include "EngineBase.h"
#include "Engine.h"
#include "BlenderObject.h"

Engine::Engine()
{
    Light* ambientLight = new Light(ambiental, Point3D::Create(0, 0, 0), Point3D::Create(0, 0, 0), ColorUnion::Create(255, 255, 255, 255));
    AddLight(ambientLight);

    // https://www.cgtrader.com/items/2770292/download-page
    BlenderObject* bObj = new BlenderObject(L"Flower.obj", L"Flower.png", 2000);
    bObj->Load();
    AddGameObject(bObj);

    //Light* dirLight = new Light(directional, Point3D::Create(0, 0, 0), Point3D::Create(1, 0, 0), ColorUnion::Create(255, 255, 255, 255));
    //AddLight(dirLight);
    //Light* posLight = new Light(fixed, Point3D::Create(4000, 0, 4000), Point3D::Create(0, 0, 0), ColorUnion::Create(255, 0, 0, 255), 20000);
    //AddLight(posLight);

    //Cube* cube1 = new Cube(Point3D::Create(2000, 0, 8000));
    //AddGameObject(cube1);
    //Cube* cube2 = new Cube(Point3D::Create(-2000, 0, 8000));
    //AddGameObject(cube2);
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