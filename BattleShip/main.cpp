#include <iostream>
#include "CBattleShipGame.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	unsigned int seed = time(0);
	//seed = 1;
	srand(seed);

	CBattleShipGame* pBattleShipGame = new CBattleShipGame;
	pBattleShipGame->Run();

	delete pBattleShipGame;
	pBattleShipGame = nullptr;
}

//목표
//플레이어는 컴퓨터가 숨겨놓은 적 함선을 찾아 격침시킨다.
//
//맵 크기는 10 x 10이다.
//각 칸에는 함선 또는 빈 칸이 위치한다.
//
//적 함선 종류
//총 4척: 크기 5, 4, 3, 2 (항공모함, 전함, 순양함, 구축함 등)
//
//함선 배치
//함선은 맵에 겹치지 않게 가로 또는 세로로 랜덤 배치된다.
//
//플레이어의 목표
//제한된 공격 횟수(30회) 내에 모든 적 함선을 명중시켜 격침시키는 것.
//
//게임 진행 방식
//플레이어는(x, y) 좌표를 입력해 공격한다.
//공격 결과(명중 / 실패)는 바로 표시되고, 플레이어의 맵에 기록된다.
//이미 공격한 좌표는 다시 공격할 수 없다.
//
//함선 격침
//한 함선의 모든 칸을 명중시키면 "격침" 메시지가 출력된다.
//
//게임 종료 조건
//모든 적 함선을 격침시키면 승리.
//주어진 횟수 내에 격침하지 못하면 패배하며, 패배 시 적 함선의 실제 위치가 공개된다.
//
//추가 정보
//남은 공격 횟수와 남은 적 함선 수가 항상 안내된다.