#include "stdafx.h"

/*
	���� ���۽� �߻��� �̺�Ʈ
	actor : �÷��̾ ������ ĳ����

*/

void StartEvent()
{
	map->Transition(0); // �� 0���� �̵�
	actor = new Character; // ĳ���� ����
	map->Spawn(actor); // �ʿ� ����
	actor->SetPosition(200, 400); // ĳ���� ��ǥ ����
}