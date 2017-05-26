#include "stdafx.h"

void StartEvent()
{
	std::wstring mapPath(L"map/data.dat");
	map->Transition(1);

	actor = new Character;
	map->Spawn(actor);

}