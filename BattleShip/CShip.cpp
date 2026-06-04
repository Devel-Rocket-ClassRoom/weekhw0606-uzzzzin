#include "CShip.h"

CShip::CShip(SHIP_TYPE _shipType)
	: m_shipType(_shipType)
	, m_shipAliveCount(m_shipType)
{
	m_shipPosArr = new tPosition[m_shipType]{ {0,0}, };
}

CShip::~CShip()
{
	delete[] m_shipPosArr;
	m_shipPosArr = nullptr;
}

void CShip::AddShipPos(int _idx, tPosition _pos)
{
	m_shipPosArr[_idx] = _pos;
}

void CShip::DieShipPos(int _idx)
{
	if (-1 != m_shipPosArr[_idx].X && -1 != m_shipPosArr[_idx].Y)
	{
		m_shipPosArr[_idx].X = -1;
		m_shipPosArr[_idx].Y = -1;

		m_shipAliveCount -= 1;
	}
}

int CShip::IsMyShipPos(int _col, int _row)
{
	for (int i = 0; i < m_shipType; ++i)
	{
		if (_col == m_shipPosArr[i].X)
		{
			if (_row == m_shipPosArr[i].Y)
			{
				return i;
			}
		}
	}
	return -1;
}
