/**
 * \file DeclarationDoor.h
 *
 * \author Samuel Duckworth
 *
 * Declaration class for door. Used for reading a declaration object from the level xml
 */
#pragma once
#include "Declaration.h"
#include <memory>

 /**
  *  Door Class Declaration
  */
class CDeclarationDoor :
	public CDeclaration
{
public:

	///delete default constructor
	CDeclarationDoor() = delete;

	///disable copy constructor
	CDeclarationDoor(CDeclarationDoor&) = delete;

	CDeclarationDoor(const std::wstring& id, const std::wstring& filename);

	///Getter for the image
	/// Gets the background image
	/// \return Image for the background
	virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mDoorImage; };

	/// Returns the left image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mDoorImage; };

	/// Returns the right image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mDoorImage; };

private:
	
	std::shared_ptr<Gdiplus::Bitmap> mDoorImage; ///< item we are loading
};

