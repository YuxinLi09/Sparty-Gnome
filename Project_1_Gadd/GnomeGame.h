/**
 * \file GnomeGame.h
 *
 * \author Yuxin Li
 *
 * Class that implements the GnomeGame.
 *
 */

#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Gnome.h"

class CScoreBoard;
class CLevel;
class CItem;
class CItemBackground;

/// Game area height in virtual pixels
const static int Height = 1024;

 /**
  * Implements a GnomeGame
  */
class CGnomeGame
{
public:
    /// constructor
    CGnomeGame();
    /// destructor
    virtual ~CGnomeGame();
    void CGnomeGame::OnDraw(Gdiplus::Graphics*,int,int);
    void CGnomeGame::Add(std::shared_ptr<CItem>);
	void AddBackground(std::shared_ptr<CItemBackground> item);
    void CGnomeGame::ClearGame();
    void CGnomeGame::Update(Gdiplus::Graphics* ,double);

    void Save(const std::wstring& filename);

    void Load(const std::wstring& filename);

	void AddGnome(const int x, const int y);

    /// Get the width of the gnomegame screen
    /// \returns screen width
    float GetScreenWidth() const { return mScreenWidth; }

    /// Get the height of the gnomegame screen
    /// \returns screen height
    float GetScreenHeight() const { return mScreenHeight; }

    /// Get the money of the gnomegame 
    /// \returns mMoney our money val
    double GetMoney() const { return mMoney; }

    /// Get the time of the gnomegame 
    /// \returns mTime our time val
    double GetTime() const { return mTime; }

    /// tells us if items collided ex:gnome and wall
    /// \param gnome The item we collide with
    /// \return bool
    bool Collided(CItem* gnome);
    
    /// refresh the screen
	void Refresh();

    /// Get the gnome this item is in
    /// \returns Gnome pointer
    std::shared_ptr<CItem> GetGnome() { return mItems[0]; }
    
    /// Increase money gained when hit TuitionUp
    void SetCoefficient() { mCoefficient *= 1.1; }; 

    ///tests to see if gnome has collided in the x direction
    ///\param gnome item to be tested with
    ///\return item taht is collided
    std::shared_ptr<CItem> CollisionXTest(CItem*);

    ///tests to see if gnome has collided in the y direction
    ///\param gnome item to be tested with
    ///\return item taht is collided
    std::shared_ptr<CItem> CollisionYTest(CItem*);

    ///gets living state of gnome
    ///\return mGnomeDead if gnome is dead or alive
    bool GetDead() { return mGnomeDead; };
    
    ///increases money value using a coefficent
    ///\param money value previously
    void IncreaseMoney(int money) { mMoney += int(mCoefficient * money); }

    ///gets the coefficent used to increase money value
    ///\return double coefficent to increase money
    double GetCoefficient() { return mCoefficient; };

    ///sets mGnomeDead gnome to true
    void SetGnomeDead() { mGnomeDead = true; };

    ///sets x direction velocity
    ///\param sign velocity to set
    void SetHorizontalVelocity(int);

    ///clears velocity in x direction
    void ClearHorizontalVelocity();

    ///collides items with gnome
    void CollideGnome(double);

    ///getter for sign of game velocity
    ///\return int sign of velocity
    int GetSign() const { return mSign; }

    ///setter for victory status
    void SetVictory() { mCompleted = true; }

    ///getter to get victory status
    ///\return bool if game has been completed
    bool GetVictory() { return mCompleted; };

    ///setter to set the proceed status
    ///\param status bool to set proceed status
    void SetProceed(bool status) { mProceed = status; mCompleted = false; }

    ///getter to get if the game can proceed
    ///\return bool mProceed 
    bool GetProceed() { return mProceed; };

    ///increments the level by one
    void IncrementCounter() { mCnt++; }

    ///setter to set game level
    ///\param newCnt int for what level the game is on
    void SetCnt(int newCnt) { mCnt = newCnt; }

    ///getter to get which level you are on
    ///\return int which level game is on
    int GetCnt() { return mCnt; }

    ///getter for how long it has been game over
    /// \return double of how long game has been over
    double GetGameOverTime() { return mGameOverTime; }

    ///resets game over time to 0
    void ClearGameOverTime() { mGameOverTime = 0; }

    ///getter to see if the game is frozen
    /// \return bool if the game if frozen or not
    bool GetFreeze() { return mFreeze; }

    /// setter to unfreeze the game
    /// \return bool false freeze state
    void SetUnfreeze() { mFreeze = false; }

    ///getter to get state of super or not
    /// \return bool
    bool GetSuper() { return mSuper; }

    ///setter to set mSuper as true or false
    /// \param status bool to set super as
    void SetSuper(bool status) { mSuper = status; }

    ///getter for the invincibility time
    /// \return double time of super
    double GetSuperTime() { return mSuperTime; }

    ///sets the invinicibility time back to 0
    void ClearSuperTime() { mSuperTime = 0; }

private:
    /// A collection of items that are contained in gnomegame
    std::vector<std::shared_ptr<CItem> > mItems;

	/// A collection of items that are contained in gnomegame
	std::vector<std::shared_ptr<CItemBackground> > mBackgrounds;

    int mMoney = 0;///< total player money
    double mTime = 0; ///< time the player has taken

    float mScreenHeight; ///< screen height currently
    float mScreenWidth; ///< screen width currently

    float mScale; ///< scale of the game window
           
    std::shared_ptr<CScoreBoard> mScoreBoard; ///< scoreboard we are using 
    std::shared_ptr<CLevel> mLevel; ///< level we are on

    bool mLeftPressed; ///< variable used if left arrow is pressed
    bool mRightPressed; ///< variable used if right arrow is pressed
    bool mSpacePressed; ///< variable used if space arrow is pressed

    double mLevelWidth; ///< width of the level
    double mLevelHeight; ///< height of the level


    bool mGnomeDead = false; ///< used to check when gnome has died

    /// Used to increase money
    double mCoefficient = 1;

    /// Used to check if player completed the level
    bool mCompleted = false;

    int mSign = 0; ///< used to set sign of gnome velocity

    int mCnt = 1; ///< system counter to record current level;

    bool mProceed = false; ///< indicates if a player can proceed to next level

    double mGameOverTime = 0; ///< how long the game over will show

    bool mFreeze = true;  ///< indicates if a player is freezed

    bool mSuper = false; ///< indicates if a player is in super mode

    double mSuperTime = 0; ///< indicated how long the player will remain invincible
};

