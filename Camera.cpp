#include "Camera.h"

Camera::Camera()
{
	this->position = Point3D::Create(0, 0, 0);
	this->rotation = Point3D::Create(0, 0, 0);

    leftPressed = false;
    rightPressed = false;
    upPressed = false;
    downPressed = false;
}

Camera::Camera(Point3D position, Point3D rotation)
{
	this->position = position;
	this->rotation = rotation;

    leftPressed = false;
    rightPressed = false;
    upPressed = false;
    downPressed = false;
}

void Camera::HandleKeyDown(WPARAM wParam)
{
    if (wParam == VK_LEFT)
        leftPressed = true;
    if (wParam == VK_RIGHT)
        rightPressed = true;
    if (wParam == VK_UP)
        upPressed = true;
    if (wParam == VK_DOWN)
        downPressed = true;
}

void Camera::HandleKeyUp(WPARAM wParam)
{
    if (wParam == VK_LEFT)
        leftPressed = false;
    if (wParam == VK_RIGHT)
        rightPressed = false;
    if (wParam == VK_UP)
        upPressed = false;
    if (wParam == VK_DOWN)
        downPressed = false;
}

void Camera::Logic(double elapsedTime)
{
    if (upPressed)
    {
        this->position.z += 500 * cos(this->rotation.y) * elapsedTime;
        this->position.x += 500 * sin(this->rotation.y) * elapsedTime;
    }
    if (downPressed)
    {
        this->position.z -= 500 * cos(this->rotation.y) * elapsedTime;
        this->position.x -= 500 * sin(this->rotation.y) * elapsedTime;
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