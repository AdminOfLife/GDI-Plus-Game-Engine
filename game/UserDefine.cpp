#include "stdafx.h"

/*
	게임 시작시 발생할 이벤트
	actor : 플레이어가 조종할 캐릭터

*/

void StartEvent()
{
	map->Transition(0); // 맵 0으로 이동
	actor = new Character; // 캐릭터 생성
	map->Spawn(actor); // 맵에 스폰
	actor->SetPosition(200, 400); // 캐릭터 좌표 설정
}