#pragma once
#include <windows.h>

//키코드 열거형//
enum KeyCode { UpArrow = 0, DownArrow = 1, LeftArrow = 2, RightArrow = 3, Space = 4, Z = 5 };

//키 상태 열거형//
enum State { keyUpRep = 0, keyDown = 1, keyDownRep = 2, keyUp = 3 };

class Input
{
	//키 상태 열거형//
	enum State { keyUpRep = 0, keyDown = 1, keyDownRep = 2, keyUp = 3 };

private:
	static State state[6];
	static int   vKey[6];

public:
	static void Update(); //키입력 상태 갱신

	//키 상태 체크 함수//
	static bool GetKey    (KeyCode code); //키가 눌리고 있는 중인지 체크함수
	static bool GetKeyDown(KeyCode code); //키가 눌림 체크함수
	static bool GetKeyUp  (KeyCode code); //키가 놓임 체크함수
};

