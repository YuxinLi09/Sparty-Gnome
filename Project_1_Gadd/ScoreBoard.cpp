/**
 * \file ScoreBoard.cpp
 *
 * \author Zach Fincher
 *
 * Implementation of a scoreboard
 */

#include "pch.h"
#include "ScoreBoard.h"
#include "GnomeGame.h"
#include <string>
#include <sstream>
#include <windows.h>



using namespace Gdiplus;
using namespace std;


CScoreBoard::CScoreBoard(CGnomeGame* Game) : mGame(Game)
{
    mGame = Game;

}

/*
* Destructtor for the scoreboard
*/
CScoreBoard::~CScoreBoard()
{

}

/** Draw the ScoreBoard
* \param graphics The GDI+ graphics context to draw on
*/
void CScoreBoard::Draw(Gdiplus::Graphics* graphics)
{
    wstringstream totalStr;
    wstringstream timeStr1;
    wstringstream timeStr;
    const double pixelWidth = 42.0;
    const int minutes = int(mGame->GetTime()) / 60;
    const int seconds = int(mGame->GetTime()) % 60;

    const float screenHeight = mGame->GetScreenHeight();
    const float screenWidth = mGame->GetScreenWidth();

    // get the mintues and the seconds
    int minutesStr = minutes;
    int secondsStr = seconds;
    double moneyStr = mGame->GetMoney();
  
    // convert
    totalStr << L"$"<< L"" << moneyStr;
    if (seconds < 10)
    {
        timeStr << L"" << minutesStr << L":0" << L"" << secondsStr;
    }
    else
    {
        timeStr << L"" << minutesStr << L":" << L"" << secondsStr;
    }

    double totalStrLen = totalStr.str().size();

    FontFamily fontFamily(L"Arial");
    Gdiplus::Font font(&fontFamily, 48);

    const int offset = 90;

    SolidBrush green(Color(32, 178, 170));
    //Not sure which green is used in the demo, 
    //color table can be found here https://www.rapidtables.com/web/color/index.html

    //time
    graphics->DrawString(timeStr.str().c_str(), -1, &font, PointF(2, 2), &green);

    //money
    graphics->DrawString(totalStr.str().c_str(), -1, &font, PointF(Gdiplus::REAL(screenWidth - (totalStrLen * offset)), 2), &green);
 
}
