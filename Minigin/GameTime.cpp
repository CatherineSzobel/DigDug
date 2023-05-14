#include "GameTime.h"
#include <iostream>
void dae::GameTime::Wait(float amount)
{
	while (amount <= 0)
	{
		amount -= GetDeltaTime();
	}
}
