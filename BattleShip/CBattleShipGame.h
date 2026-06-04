#pragma once

enum SHIP_DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class CShip;
struct tPosition;

class CBattleShipGame
{
private:
	int*	m_mapAnswer;	// 정답 맵, 0 : 빈 곳, 1 : 배가 있는 곳
	int*	m_mapPlay;		// 플레이중인 맵, 0 : 빈 곳, 1 : 격추시킨 곳, 2 : 격추 시도 했지만 빈 곳
	int		m_mapRowSize;
	int		m_mapColSize;

	CShip*	m_shipArr; // Ship 4개가 담긴 Array

	int		m_remainTurnCount; // 남아있는 턴 수 
	int		m_aliveShipCount; // 살아있는 배 개수

private:
	void GenerateShipMap(); // 맵을 생성하는 함수
	void PlaceShip(CShip* _curShip); // 배를 랜덤한 위치에 놓는 함수

	bool CanPlaceShip(CShip* _curShip, tPosition _pos, SHIP_DIR _dir); // 해당 좌표와 방향으로 배를 놓을 수 있는지 없는지
	void AttackShip(); // 유저가 배를 공격하는 구간의 함수
public:
	void PrintAnswerMap();
	void PrintPlayMap();

public:
	void Run();

public:
	CBattleShipGame();
	~CBattleShipGame();
};
