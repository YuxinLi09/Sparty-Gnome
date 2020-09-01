/**
 * \file Gnome.h
 *
 * \author Yiteng Zhang
 *
 * Holds the class to represent gnome
 */
#pragma once

#include "GnomeGame.h"
#include "Item.h"
#include "Vector.h"

/**
 * Class defining the Gnome
 */
class CGnome : public CItem
{
public:
	/// Disabling the default constructor
	CGnome() = delete;
	/// Disabling the Copy constructor
	CGnome(const CGnome&) = delete;
    /// Constructor 
    CGnome(CGnomeGame* );
    /// Destructor 
    ~CGnome();

    /// Draw the Gnome
    /// \param graphics the graphics we are drawing on
    /// \return mYPos the y position of the gnome
    virtual void CGnome::Draw(Gdiplus::Graphics* graphics) override;
   
    /// Update for the gnome
    /// \param elapsed the time in which has passed since redrawing
    void Update(double elapsed); ///####

    ///Set Vertical Velocity for the gnome
    virtual void SetVerticalVelocity() { mV.SetY(JumpSpeed); };

    ///Clear Horizontal Velocity for the gnome
    virtual void ClearHorizontalVelocity() { mV.SetX(0); };
    
    /// Set our x  velocity
    /// \param sign
    virtual void SetHorizontalVelocity(int sign) { mV.SetX(sign * HorizontalSpeed); };

    /// Get the y velocity for the gnome
    /// \return mV.Y() 
    virtual double GetVelocityY() { return mV.Y(); };

    ///collide for the gnome item 
    /// \param distance distance between items
    virtual void CollideGnome(double distance) {};

private:
    CVector mV; ///< Velocity Vector for Gnome
    CVector mPos; ///< Gnome pos vactor
    CGnomeGame* mGame; ///< Game we are using
    std::wstring mCurrentImage; ///< current image
};

