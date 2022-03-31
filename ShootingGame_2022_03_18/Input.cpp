#include "ShootingGame.h"

//enum KeyCode            {UpArrow=0,       DownArrow=1     , LeftArrow=2    ,RightArrow=3    , Space=4        , Z=5 };

Input::State Input::state[6] = { State::keyUpRep, State::keyUpRep, State::keyUpRep,State::keyUpRep ,State::keyUpRep ,State::keyUpRep };
int   Input::vKey[6]  = { VK_UP          , VK_DOWN        , VK_LEFT        , VK_RIGHT        , VK_SPACE      ,   'Z' };

void Input::Update()
{
    for (int i = 0; i < 6; i++)
    {
        if (state[i] == State::keyUpRep) //놓고있는 상태
        {
            if (GetAsyncKeyState(vKey[i]) != 0)
            {
                state[i] = State::keyDown;  //누르는 상태로..전이
            }
        }
        else if (state[i] == State::keyDown) //누르는 상태
        {
            if (GetAsyncKeyState(vKey[i]) != 0)
            {
                state[i] = State::keyDownRep; //누르고 있는 상태로...전이
            }
            else {
                state[i] = State::keyUp; //놓는 상태로...전이
            }
        }
        else if (state[i] == State::keyDownRep) //누르고 있는 상태
        {
            if (GetAsyncKeyState(vKey[i]) == 0)
            {
                state[i] = State::keyUp;  //놓는 상태로..전이
            }
        }
        else if (state[i] == State::keyUp) //놓는 상태
        {
            if (GetAsyncKeyState(vKey[i]) == 0)
            {
                state[i] = State::keyUpRep; //놓고 있음 상태로..전이
            }
            else {
                state[i] = State::keyDown; //누르는 상태로..전이
            }
        }
    }
}

bool Input::GetKey(KeyCode code) //키가 눌리고 있는 중인지 체크함수
{
    if (state[code] == State::keyDown || state[code] == State::keyDownRep)
    {
        return true;
    }
    else {
        return false;
    }
}

bool Input::GetKeyDown(KeyCode code) //키가 눌림 체크함수
{
    if (state[code] == State::keyDown)
    {
        return true;
    }
    else {
        return false;
    }
}

bool Input::GetKeyUp(KeyCode code) //키가 놓임 체크함수
{
    if (state[code] == State::keyUp)
    {
        return true;
    }
    else {
        return false;
    }
}