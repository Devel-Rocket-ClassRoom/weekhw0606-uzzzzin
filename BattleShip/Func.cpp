#include "Func.h"
#include <iostream>

void FisherYatesShuffle(int* _arr, int _len)
{
	// 1. 인덱스는 배열의 마지막 요소에서 첫번째 요소로 진행
	// 2. 인덱스가 가리키는 요소와 0-인덱스까지의 요소 중 임의의 요소를 선택
	// 3. 인덱스가 가이키는 요소와 임의로 선택된 요소를 교환
	// 4. 인덱스는 1 감소

	int curCursorIdx = _len - 1; // 현재 커서는 배열의 제일 끝 요소의 인덱스

	//PrintArray(_arr, _len);
	for (int i = curCursorIdx; i > 0; --i)
	{
		int randChangeIdx = rand() % curCursorIdx; // 랜덤하게 바꿀 커서 인덱스 값

		// 랜덤 커서 인덱스의 배열값과 현재 커서 인덱스의 배열값을 스왑
		int temp = _arr[curCursorIdx];
		_arr[curCursorIdx] = _arr[randChangeIdx];
		_arr[randChangeIdx] = temp;
	}
	//PrintArray(_arr, _len);
}
