#pragma once

#define INPUT_NO 0x0000 // Ű�� ������ ���� ����
#define INPUT_PRESSED 0x0001 // Ű�� ���� ����
#define INPUT_TAPPED 0x0002 // Ű�� ���ʷ� ���� ��쿡��
#define INPUT_STOPPED 0x0004 // ������ �ִ� Ű�� �� ���

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