/**
 * \file Item.h
 *
 * \author
 *
 * Class that implements the item in GnomeGame.
 *
 */

#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"
#include "Vector.h"
#include <sstream>

class CGnomeGame;

/// Gravity in virtual pixels per second per second
const double Gravity = 1000.0;

/// Horizontal character speed in pixels per second
const double HorizontalSpeed = 500.00;

const double JumpSpeed = -800; ///< the jump speed for the gnome

/// Small value to ensure we do not stay in collision
const double Epsilon = 0.1;

 /**
  * Implements an Item
  */
class CItem
{
public:
    /// Default constructor (disabled)
    CItem() = delete;

    /// Copy constructor (disabled)
    CItem(const CItem&) = delete;

    virtual ~CItem();

    /// The X location of the item
    /// \returns mX location in pixels 
    double GetX() const { return mP.X(); }

    /// The Y location of the item
    /// \returns mY location in pixels 
    double GetY() const { return mP.Y(); }

    ///Set the item location
    /// \param x X location
    /// \param y Y location 
	void SetLocation(double x, double y) { mP.Set(x, y); }


    virtual void Draw(Gdiplus::Graphics* graphics);

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// update  items pos or condition
    virtual void Update(double elapsed); 

    /// Get the gnomegame this item is in
    /// \returns mGnomeGame pointer
    CGnomeGame* GetGnomeGame() { return mGnomeGame; }
    
    virtual bool HitTest(int x, int y);

    /// Set item Horizontal Velocity
    virtual void SetHorizontalVelocity(int) {};

    /// Set the Gnome VerticalVelocity
    virtual void SetVerticalVelocity() {};

    /// Clears the Gnome Horizontal Velocity
    virtual void ClearHorizontalVelocity() {};
    
    /// Function to get gnome y velocity
    /// \return 0 the velocity in the Y direction for the gnome
    virtual double GetVelocityY() { return 0; };

    /// Function to get gnome x velocity
    /// \return mV.X() the velocity in the x direction for the gnome
    virtual double GetVelocityX() { return mV.X(); };

    /// Function to check if the gnome collided with an item
    /// \param distance the distance for objects and gnome
    virtual void CollideGnome(double distance) { mP.SetX(GetX() + distance); SetLocation(mP.X(), mP.Y()); };

    /// Function to set item image 
    /// \param file the file for objects
    void SetImage(const std::shared_ptr<Gdiplus::Bitmap>& file);

    /// Function to assist load for items from xml with appropiate image
	void SetImageFile(const std::wstring& file);

    /// Load for the items
    /// \param node what we are using to load
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);


    /// Function to get the image for item
    /// \return mItemImage the image in files for object
    std::shared_ptr<Gdiplus::Bitmap> GetImage() { return mItemImage; }

    /// Get the width of the item image
    /// \returns width
    virtual double GetWidth() { return mItemImage->GetWidth(); };

    /// Get the height of the item image
    /// \returns height
    virtual double GetHeight() { return mItemImage->GetHeight(); };

    /// Functions to help decide what items to draw
    /// \returns the presenting status of an item 
    virtual bool CheckPresentable() { return mPresented; };

    /// Remove an item from display
    void RemoveDisplay() { mPresented = false; };

    /// Add an item to display
    void AddDisplay() { mPresented = true; };

    /// Function to help decide what items have collided and does approperate operation for said item
    /// \param item object we are working with
    virtual void Collide(CItem* item) {};

    /// Function to draw need caption for items
    /// \param graphics what we are drawing on
    virtual void DrawCaption(Gdiplus::Graphics* graphics) {};

    /// Function to get presented time
    /// \returns mTime
    double GetPresentTime() { return mTime; }

    /// Function to clear the mTime
    void ClearPresentTime() { mTime = 0; }

protected:
    /// Constructor
    CItem(CGnomeGame* , const std::wstring& );

private:
    bool mMirror = false;   ///< True mirrors the item image

    /// The image of this item
    std::shared_ptr<Gdiplus::Bitmap> mItemImage;

    
    CGnomeGame* mGnomeGame;///< The gnomegame this item is contained in

    bool mPresented = true; ///< condition for if item is still on screen 

    CVector mV; ///< Velocity Vector for Item
    CVector mP; ///< Pos Vector for Item
    double mTime=0; ///< Timer to record how long the caption will remain on the screen

    double mGameOverTime = 0;///< Timer to record how long the game over will be active for 
};

