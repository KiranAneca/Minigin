#pragma once
#include "RenderComponent.h"
#include "GridComponent.h"
#include "Observer.h"
#include "SubjectComponent.h"

#include "iostream"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
	
};
