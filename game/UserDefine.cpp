#include "stdafx.h"

/*
actor	: �÷��̾ ������ ĳ����
map		: ��
scene	: ��� ���� Ŭ����
*/

// ���� ���۽� �߻��ϴ� �̺�Ʈ
void StartEvent()
{
	actor = new Character; // ĳ���� ����
	actor->SetPosition(200, 400); // ĳ���� ��ǥ ����
	map->Transition(1); // �� 0���� �̵�
}

// �ʿ��� �߻��ϴ� �̺�Ʈ
void MapEvent(UINT id)
{
	if (id == 0)
	{
		int x, y;
		actor->GetPosition(x, y);
		if (x < 0 || y < 0 || x > map->GetWidth() || y > map->GetHeight())
		{
			map->Transition(1);
			actor->SetPosition(100, 200);
		}
	}
	else if (id == 1)
	{
		int x, y;
		actor->GetPosition(x, y);
		if (x < 0 || y < 0 || x > map->GetWidth() || y > map->GetHeight())
		{
			map->Transition(0);
			actor->SetPosition(100, 200);
		}
	}
}