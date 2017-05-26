#include "stdafx.h"

void InputComponent::AddBinding(INT keyCord, SHORT keyEvent, Function *function)
{
	bindings.push_back(InputBinding(keyCord, keyEvent, function));
}

void InputComponent::Update()
{
	for (auto &entity : bindings)
	{
		SHORT keyState = GetAsyncKeyState(entity.keyCord);

		if (entity.keyEvent == INPUT_PRESSED && keyState & 0x8000)
		{
			entity.function->execute();
		}

		if (entity.keyEvent == INPUT_TAPPED && keyState & 0x8000 && entity.prevEvent == 0x0000)
		{
			entity.function->execute();
		}

		if (entity.keyEvent == INPUT_STOPPED && keyState == 0x0000 && entity.prevEvent & 0x8000)
		{
			entity.function->execute();
		}

		if (entity.keyEvent == INPUT_NO && (entity.keyCord) == 0x0000)
		{
			entity.function->execute();
		}
		entity.prevEvent = keyState;
	}
}

InputComponent::~InputComponent()
{
	for (auto const &entity : bindings)
	{
		delete entity.function;
	}
}