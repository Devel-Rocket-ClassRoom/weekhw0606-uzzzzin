#include "CBattleShipGame.h"
#include <iostream>

#include "Func.h"
#include "CShip.h"

CBattleShipGame::CBattleShipGame()
	: m_mapRowSize(10)
	, m_mapColSize(10)
	, m_remainTurnCount(30)
	, m_aliveShipCount(4)
{
	m_shipArr = new CShip[4]{ CShip(DESTROYER), CShip(CRUISER), CShip(BATTLESHIP), CShip(CARRIER)};
	m_mapAnswer = new int[m_mapRowSize * m_mapColSize] {0, };
	m_mapPlay = new int[m_mapRowSize * m_mapColSize] {0, };
}

CBattleShipGame::~CBattleShipGame()
{
	delete[] m_mapAnswer;
	m_mapAnswer = nullptr;

	delete[] m_mapPlay;
	m_mapPlay = nullptr;

	delete[] m_shipArr;
	m_shipArr = nullptr;
}

void CBattleShipGame::Run()
{
	// 맵 랜덤 세팅
	GenerateShipMap();

	// 실제 게임 시작
	std::cout << "===============================" << std::endl;
	std::cout << " BATTLE SHIP 게임을 시작합니다!" << std::endl;
	std::cout << "===============================" << std::endl;

	while(true)
	{
		// 배가 다 격추당함 or 남은 턴이 없음 -> 반복문 탈출!
		if (0 == m_aliveShipCount || 0 == m_remainTurnCount)
		{
			//if (0 == m_aliveShipCount)
				//std::cout << "★☆★☆ 배를 모두 격침시켰습니다. ★☆★☆" << std::endl;		
			if (0 == m_remainTurnCount)
			{
				std::cout << "턴을 모두 소모하셨습니다... ㅜ__ㅜ" << std::endl;
				std::cout << "적 함선의 실제 위치를 보여드립니다.." << std::endl;
				PrintAnswerMap();
			}
			break;
		}

		std::cout << "[" << m_remainTurnCount << "]번의 기회가 남았습니다." << std::endl;
		std::cout << "[" << m_aliveShipCount << "]개의 배가 남았습니다." << std::endl;
		std::cout << "===============================" << std::endl;

		PrintAnswerMap();
		PrintPlayMap();

		// 배를 공격...
		AttackShip();
	}
}

void CBattleShipGame::GenerateShipMap()
{
	for (int i = 0; i < 4; ++i)
	{
		PlaceShip(&m_shipArr[i]);
	}
}

void CBattleShipGame::PlaceShip(CShip* _curShip)
{
	// 랜덤으로 처음 시작 위치 저장
	tPosition startPos = { rand() % 10, rand() % 10 };

	// 어떤 방향으로 배를 놓을 것인지 저장
	SHIP_DIR dir; // = (SHIP_DIR)dirArr[0];

	// 해당 위치와 방향에 배를 놓을 수 있는지 없는지 체크
	bool bCanPlaceShip = false;

	while(true)
	{
		if (true == bCanPlaceShip) break;

		// 해당 위치가 비어있지 않다면, 계속 비어있는 자리를 찾아요
		while(true)
		{
			startPos = { rand() % 10, rand() % 10 };
			if (0 == m_mapAnswer[startPos.Y * m_mapColSize + startPos.X]) break;
		}

		// 어디로 확장을 할 것 인지 랜덤으로 방향 저장
		int dirArr[4] = { LEFT, RIGHT, UP, DOWN };
		FisherYatesShuffle(dirArr, 4);

		for (int i = 0; i < 4; ++i)
		{
			// 해당 위치와 방향에 배를 놓을 수 있는지 없는지 체크
			dir = (SHIP_DIR)dirArr[i];
			bCanPlaceShip = CanPlaceShip(_curShip, startPos, dir);

			if (true == bCanPlaceShip) break; // startPos에 놓을 수 있다면, 반복문 탈출

			//if (3 == i && false == bCanPlaceShip) // 네가지 방향을 다 검사했는데도 놓을 곳이 없는 상황				
		}
	}

	// 해당 자리와 해당 방향으로 배를 놓음
	for (int i = 0; i < _curShip->GetShipType(); ++i)
	{
		tPosition curPos = {};

		if(LEFT == dir) 
		{
			curPos.X = startPos.X - i; 
			curPos.Y = startPos.Y;
		}
		else if (RIGHT == dir) 
		{
			curPos.X = startPos.X + i; 
			curPos.Y = startPos.Y;
		}
		else if (UP == dir)
		{
			curPos.X = startPos.X; 
			curPos.Y = startPos.Y - i;
		}
		else if (DOWN == dir)
		{
			curPos.X = startPos.X; 
			curPos.Y = startPos.Y + i;
		}

		_curShip->AddShipPos(i, curPos); // 해당 배의 인덱스에 현재 게산된 포지션을 넣음
		m_mapAnswer[curPos.Y * m_mapColSize + curPos.X] = 1;

		//switch (dir)
		//{
		//case LEFT: curPos.X = startPos.X - i; curPos.Y = startPos.Y; break;
		//case RIGHT: curPos.X = startPos.X + i; curPos.Y = startPos.Y; break;
		//case UP: curPos.X = startPos.X; curPos.Y = startPos.Y - i; break;
		//case DOWN: curPos.X = startPos.X; curPos.Y = startPos.Y + i; break;
		//}
	}
}

bool CBattleShipGame::CanPlaceShip(CShip* _curShip, tPosition _pos, SHIP_DIR _dir)
{
	// 확장할 수 없는 자리인지(인덱스 범위 벗어남), 그 자리에 이미 배가 들어 있는지
	if (LEFT == _dir)
	{
		for (int i = 0; i < _curShip->GetShipType(); ++i)
		{
			tPosition tempPos = { _pos.X - i, _pos.Y };

			// 인덱스 범위를 벗어난 경우 or 해당 자리에 이미 배가 들어 있음
			if (tempPos.X < 0 || 0 != m_mapAnswer[tempPos.Y * m_mapRowSize + tempPos.X])
				return false;
		}
	}
	else if (RIGHT == _dir)
	{
		for (int i = 0; i < _curShip->GetShipType(); ++i)
		{
			tPosition tempPos = { _pos.X + i, _pos.Y };

			// 인덱스 범위를 벗어난 경우 or 해당 자리에 이미 배가 들어 있음
			if (tempPos.X > m_mapColSize-1 || 0 != m_mapAnswer[tempPos.Y * m_mapRowSize + tempPos.X])
				return false;
		}
	}
	else if (UP == _dir)
	{
		for (int i = 0; i < _curShip->GetShipType(); ++i)
		{
			tPosition tempPos = { _pos.X, _pos.Y - i };

			// 인덱스 범위를 벗어난 경우 or 해당 자리에 이미 배가 들어 있음
			if (tempPos.Y < 0 || 0 != m_mapAnswer[tempPos.Y * m_mapRowSize + tempPos.X])
				return false;
		}
	}
	else if (DOWN == _dir)
	{
		for (int i = 0; i < _curShip->GetShipType(); ++i)
		{
			tPosition tempPos = { _pos.X, _pos.Y + i };

			// 인덱스 범위를 벗어난 경우 or 해당 자리에 이미 배가 들어 있음
			if (tempPos.Y > m_mapRowSize-1 || 0 != m_mapAnswer[tempPos.Y * m_mapRowSize + tempPos.X])
				return false;
		}
	}
	
	return true;
}


void CBattleShipGame::AttackShip()
{
	// 좌표 입력받기
	std::cout << "공격할 곳의 좌표를 입력하세요(X,Y) : ";
	int col, row = 0;
	std::cin >> col >> row;

	int idx = row * m_mapColSize + col;

	if (1 == m_mapAnswer[idx]) // 배가 있음
	{
		if (1 == m_mapPlay[idx])
		{
			std::cout << "이미 공격한 곳을 공격할 순 없습니다." << std::endl;
			m_remainTurnCount -= 1;
			return;
		}
		m_mapPlay[idx] = 1; // 맵에 격추 표시

		for (int i = 0; i < 4; ++i) // 4개의 배 중에서 해당 인덱스의 배 찾기
		{
			// i번째 배의 어떤 부분을 격추할 것인지..
			// i번째 배를 순회해 col,row 좌표에 배가 있는지 확인하고, 해당 인덱스를 반환함
			int shipChunkIdx = m_shipArr[i].IsMyShipPos(col, row);  

			if (-1 != shipChunkIdx)
			{
				m_shipArr[i].DieShipPos(shipChunkIdx); // i번째 배의 shipChunkIdx부분이 격추됨
				if (0 == m_shipArr[i].GetShipAliveCount())
				{
					m_aliveShipCount -= 1;
					if (0 == m_aliveShipCount)
					{
						std::cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆" << std::endl;
						std::cout << "★☆★☆ 배를 모두 격침시켰습니다. ★☆★☆" << std::endl;
						std::cout << "★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆" << std::endl;
					}

					else
						std::cout << "★★배를 격침시켰습니다!★★" << std::endl;
				}
				else
				{
					std::cout << "★배를 공격했습니다!★" << std::endl;
				}
			}
			// else -1이면 이 배가 아닌 것
		}
	}
	else // 배가 없음
	{
		if (2 == m_mapPlay[idx])
		{
			std::cout << "☆격추를 시도했지만 배가 없었던 곳입니다..☆" << std::endl;
		}
		else
		{
			m_mapPlay[idx] = 2; // 격추 시도했지만 빈 곳
			std::cout << "☆배가 없습니다...☆" << std::endl;
		}

	}

	m_remainTurnCount -= 1;
}

void CBattleShipGame::PrintAnswerMap()
{
	std::cout << " ";

	for (int i = 0; i < 10; ++i)
		std::cout << " " << i << " ";

	std::cout << std::endl;

	for (int row = 0; row < 10; ++row)
	{
		std::cout << row << " ";
		for (int col = 0; col < 10; ++col)
		{
			int temp = m_mapAnswer[row * m_mapColSize + col];
			switch (temp)
			{
			case 0: std::cout << ".  "; break;
			case 1: std::cout << "S  "; break;
			}
		}
		std::cout << std::endl;
	}
}

void CBattleShipGame::PrintPlayMap()
{
	std::cout << " ";

	for (int i = 0; i < 10; ++i)
		std::cout << " " << i << " ";

	std::cout << std::endl;

	for (int row = 0; row < 10; ++row)
	{
		std::cout << row << " ";
		for (int col = 0; col < 10; ++col)
		{
			int temp = m_mapPlay[row * m_mapColSize + col];
			switch (temp)
			{
			case 0: std::cout << ".  "; break;
			case 1: std::cout << "X  "; break;
			case 2: std::cout << "O  "; break;
			}
		}
		std::cout << std::endl;
	}
}
