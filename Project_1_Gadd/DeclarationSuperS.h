/**
 * \file DeclarationSuperS.h
 *
 * \author Yuxin Li
 * 
 * Declaration class for SuperS. Used for reading a declaration object from the level xml
 */

#pragma once
#include "Declaration.h"

/**
 * SuperS declaration class
 */
class CDeclarationSuperS :
    public CDeclaration
{
public:
	///delete default constructor
	CDeclarationSuperS() = delete;
	///disable copy constructor
	CDeclarationSuperS(CDeclarationSuperS&) = delete;

	CDeclarationSuperS(const std::wstring& id, const std::wstring& filename);

	///Getter for the image
	/// Gets the background image
	/// \return Image for the background
	virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mSuperS; };

	/// Returns the left image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mSuperS; };

	/// Returns the right image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mSuperS; };

private:
	/// The money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mSuperS;
};

