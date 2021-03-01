#pragma once

#include "resource.h"
#include "EngineBase.h"

class Engine : public EngineBase
{
public:
	Engine();
	~Engine();

	void KeyUp(WPARAM wParam) override;
	void KeyDown(WPARAM wParam) override;

	void Logic(double elapsedTime) override;

};

