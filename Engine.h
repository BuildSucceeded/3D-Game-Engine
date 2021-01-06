#pragma once

#include "resource.h"
#include "EngineBase.h"

class Engine : public EngineBase
{
public:
	Engine();
	~Engine();

	void Logic(double elapsedTime) override;

};

