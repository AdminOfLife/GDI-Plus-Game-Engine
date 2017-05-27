#include "stdafx.h"

/*
actor	: 플레이어가 조종할 캐릭터
map		: 맵
scene	: 출력 제어 클래스
*/

// 게임 시작시 발생하는 이벤트
void StartEvent()
{
	actor = new Character; // 캐릭터 생성
	actor->SetPosition(200, 400); // 캐릭터 좌표 설정
	map->Transition(1); // 맵 0으로 이동
}

// 맵에서 발생하는 이벤트
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