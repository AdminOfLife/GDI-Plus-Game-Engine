#pragma once

#define INPUT_NO 0x0000 // 키가 눌리지 않은 상태
#define INPUT_PRESSED 0x0001 // 키가 눌린 상태
#define INPUT_TAPPED 0x0002 // 키를 최초로 누른 경우에만
#define INPUT_STOPPED 0x0004 // 누르고 있던 키를 뗀 경우

struct InputBinding
{
public:
	InputBinding(INT _keyCord, SHORT _keyEvent, Function *_function) : keyCord(_keyCord), keyEvent(_keyEvent), function(_function) { prevEvent = 0x0000; }
	INT keyCord;
	SHORT keyEvent;
	SHORT prevEvent;
	Function *function;
};

class InputComponent
{
private:
	std::vector<InputBinding> bindings;
public:
	~InputComponent();
	void AddBinding(INT keyCord, SHORT keyEvent, Function *function);
	void Update();
};