#include "Camera.h"

Camera::Camera()
{
	this->position = Point3D::Create(0, 0, 0);
	this->rotation = Point3D::Create(0, 0, 0);

    leftPressed = false;
    rightPressed = false;
    aPressed = false;
    wPressed = false;
    sPressed = false;
    dPressed = false;
}

Camera::Camera(Point3D position, Point3D rotation)
{
	this->position = position;
	this->rotation = rotation;

    leftPressed = false;
    rightPressed = false;
    aPressed = false;
    wPressed = false;
    sPressed = false;
    dPressed = false;
}

void Camera::HandleKeyDown(WPARAM wParam)
{
    if (wParam == VK_LEFT)
        leftPressed = true;
    if (wParam == VK_RIGHT)
        rightPressed = true;
    if (wParam == 0x41) // A Key
        aPressed = true;
    if (wParam == 0x57) // W key
        wPressed = true;
    if (wParam == 0x53) // S Key
        sPressed = true;
    if (wParam == 0x44) // D key
        dPressed = true;
}

void Camera::HandleKeyUp(WPARAM wParam)
{
    if (wParam == VK_LEFT)
        leftPressed = false;
    if (wParam == VK_RIGHT)
        rightPressed = false;
    if (wParam == 0x41) // A Key
        aPressed = false;
    if (wParam == 0x57) // W key
        wPressed = false;
    if (wParam == 0x53) // S Key
        sPressed = false;
    if (wParam == 0x44) // D key
        dPressed = false;
}

void Camera::Logic(double elapsedTime)
{
    if (wPressed)
    {
        this->position.z += 10000 * cos(this->rotation.y) * elapsedTime;
        this->position.x += 10000 * sin(this->rotation.y) * elapsedTime;
    }
    if (sPressed)
    {
        this->position.z -= 10000 * cos(this->rotation.y) * elapsedTime;
        this->position.x -= 10000 * sin(this->rotation.y) * elapsedTime;
    }
    if (aPressed)
    {
        this->position.z += 10000 * sin(this->rotation.y) * elapsedTime;
        this->position.x -= 10000 * cos(this->rotation.y) * elapsedTime;
    }
    if (dPressed)
    {
        this->position.z -= 10000 * sin(this->rotation.y) * elapsedTime;
        this->position.x += 10000 * cos(this->rotation.y) * elapsedTime;
    }
    if (leftPressed)
        this->rotation.y -= elapsedTime;
    if (rightPressed)
        this->rotation.y += elapsedTime;
}

Point3D Camera::GetPosition()
{
    return position;
}

Point3D Camera::GetRotation()
{
    return rotation;
}