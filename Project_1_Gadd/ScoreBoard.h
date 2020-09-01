/**
 * \file ScoreBoard.h
 *
 * \author Zach Fincher
 *
 *  Class that implements a scoreboard and holds all realted functionality 
 */
#pragma once

class CGnomeGame;

/**
 * Class defining the ScoreBoard
 */
class CScoreBoard
{

/* 
* Implementation of the scoreboard located on the top of the sceen at all times.
* The Scoreboard will hold the time on current level, and the money collected.
* This will reset at the start of every level, and can be changed through items
* that will either increase the value of money collected or decrease it.
*/

public:

    

    /// constructor 
    CScoreBoard(CGnomeGame* );

    /// Default constructor (disabled)
    CScoreBoard() = delete;



    /// Copy constructor (disabled)
    CScoreBoard(const CScoreBoard&) = delete;

    
    ///destructor
    ~CScoreBoard();


    void Draw(Gdiplus::Graphics* graphics);


private:

    CGnomeGame* mGame; ///< Gnomegame pointer

protected:
    
};

