/**
 * \file DeclarationOSUDefender.h
 *
 * \author Zach Fincher
 *
 * Declaration class for OSUDefender. Used for reading a declaration object from the level xml
 */

#pragma once
#include "Declaration.h"

/**
 * OSUDefender Declaration class
 */
class CDeclarationOSUDefender :
	public CDeclaration
{
public:
	///delete default constructor
	CDeclarationOSUDefender() = delete;
	///disable copy constructor
	CDeclarationOSUDefender(CDeclarationOSUDefender&) = delete;

	CDeclarationOSUDefender(const std::wstring& id, const std::wstring& filename);

	///Getter for the image
	/// Gets the background image
	/// \return Image for the background
	virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mDefender; };

	/// Returns the left image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mDefender; };

	/// Returns the right image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mDefender; };

private:
	/// The money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mDefender;


};

