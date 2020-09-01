/**
 * \file Gnome.cpp
 *
 * \author Yiteng Zhang
 */

#include "pch.h"
#include "Gnome.h"
#include <vector>

using namespace std;
using namespace Gdiplus;

/// Gnome image filename
 /// base gnome image 
const wstring GnomeImage = L"images/gnome.png";
/// gnome walk left image 1
const wstring GnomeLeftImage1 = L"images/gnome-walk-left-1.png";
/// gnome walk left image 2
const wstring GnomeLeftImage2 = L"images/gnome-walk-left-2.png";  
/// gnome walk right image 1
const wstring GnomeRightImage1 = L"images/gnome-walk-right-1.png";
/// gnome walk left image 2
const wstring GnomeRightImage2 = L"images/gnome-walk-right-2.png";  
/// gnome sad image
const wstring GnomeSadImage = L"images/gnome-sad.png";

 /**
  * Constructor for Gnome class
  * \param game game we are using
  */
CGnome::CGnome(CGnomeGame* game) : CItem(game, GnomeImage)
{
    // Set image and pointer to game
    SetImageFile(GnomeImage);
    mCurrentImage = GnomeImage;
    /// Assign gnome to mGnome
    mGame = game;
    SetLocation(600, 700);
    mPos.SetX(600);
    mPos.SetY(700);
}

/**
 * Destructor for Gnome Class
 */
CGnome::~CGnome()
{
};


void CGnome::Draw(Gdiplus::Graphics* graphics)
{
    CItem::Draw(graphics);
}



void CGnome::Update(double elapsed)
{
    CItem::Update(elapsed);
    // Gravity
    // Compute a new velocity with gravity added in.
    CVector newV(mV.X(), mV.Y() + Gravity * elapsed);
    // Update position
    CVector newP = mPos + newV * elapsed;
    if (!GetGnomeGame()->GetProceed())
    {
        if (!GetGnomeGame()->GetDead()) {
            //
            // Try updating the Y location. 
            //
            SetLocation(mPos.X(), newP.Y());
            auto collided = GetGnomeGame()->CollisionYTest(this);
            if (collided != nullptr)
            {
                if (newV.Y() > 0)
                {
                    // We are falling, stop at the collision point
                    newP.SetY(collided->GetY() - collided->GetHeight() / 2 - GetHeight() / 2 - Epsilon);
                }
                else
                {
                    // We are rising, stop at the collision point
                    newP.SetY(collided->GetY() + collided->GetHeight() / 2 + GetHeight() / 2 + Epsilon);
                }
                // If we collide, we cancel any velocity
                // in the Y direction
                newV.SetY(0);
            }
            //
            // Try updating the X location
            //
            SetLocation(newP.X(), mPos.Y());
            mPos.SetX(newP.X());
        }
    }
    if (!GetGnomeGame()->GetProceed())
    {
        
        if (!GetGnomeGame()->GetDead()) {
            auto collided = GetGnomeGame()->CollisionXTest(this);
            if (collided != nullptr)
            {
                if (newV.X() > 0)
                {
                    // We are moving to the right, stop at the collision point
                    if (!GetGnomeGame()->GetDead())
                        newP.SetX(collided->GetX() - collided->GetWidth() / 2 - GetWidth() / 2 - Epsilon);
                }
                else
                {
                    // We are moving to the left, stop at the collision point
                    if (!GetGnomeGame()->GetDead())
                        newP.SetX(collided->GetX() + collided->GetWidth() / 2 + GetWidth() / 2 + Epsilon);
                }
                // If we collide, we cancel any velocity
                // in the X direction
                newV.SetX(0);
            }
            SetLocation(mPos.X(), newP.Y());
            mPos.SetY(newP.Y());
        }
        // Update the velocity and position
        mV = newV;
        SetLocation(newP.X(), newP.Y());
        mPos = newP;
        if (!GetGnomeGame()->GetDead())
        {
            SetImageFile(GnomeSadImage); ///Set gnome image to gnome sad image if gameover
        }
        if (mV.X() > 0) {
            if (int(elapsed * 500) % 2 == 1) {
                SetImageFile(GnomeRightImage1);
            }
            else if (int(elapsed * 500) % 2 == 0) {
                SetImageFile(GnomeRightImage2);
            }
        }
        else if (mV.X() < 0) {
            if (int(elapsed * 500) % 2 == 1) {
                SetImageFile(GnomeLeftImage1);
            }
            else if (int(elapsed * 500) % 2 == 0) {
                SetImageFile(GnomeLeftImage2);
            }
        }
        else if (mV.X() == 0)
        {
            SetImageFile(GnomeImage);
        }
        if (GetY() < 1024) GetGnomeGame()->ClearGameOverTime();
        else if (GetY() >= 1024) {
            GetGnomeGame()->SetGnomeDead();
        }
    }
}
