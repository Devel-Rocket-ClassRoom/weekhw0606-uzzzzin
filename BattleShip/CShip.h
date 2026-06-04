#pragma once

enum SHIP_TYPE
{
	DESTROYER = 2,
	CRUISER,
	BATTLESHIP,
	CARRIER,
	SHIP_NONE,
};

struct tPosition
{
	int X = 0;
	int Y = 0;
};

class CShip
{
private:
	SHIP_TYPE		m_shipType;
	int				m_shipAliveCount; // 살아있는 조각의 개수
	tPosition*		m_shipPosArr;

public:
	SHIP_TYPE GetShipType() { return m_shipType; }
	int GetShipAliveCount() { return m_shipAliveCount; }

	void AddShipPos(int _idx, tPosition _pos);
	void DieShipPos(int _idx); // 해당 인덱스의 포지션을 죽은 포지션으로

	// 인자로 들어온 좌표가 내 배의 좌표라면 true 반환
	// -1이면 없음
	// 0 ~는 해당 인덱스의 배 부분이 해당 포지션이다
	int IsMyShipPos(int _col, int _row);

public:
	CShip(SHIP_TYPE _shipType);
	~CShip();
};