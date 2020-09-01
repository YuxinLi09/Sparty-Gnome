/**
 * \file DeclarationBackground.h
 *
 * \author Ethan Peterson et. al
 *
 * Declaration class for background. Used for reading a declaration object from the level xml
 */

#pragma once
#include "Declaration.h"
#include <string>


/**
 *  Background Class Declaration
 */
class CDeclarationBackground :
	public CDeclaration
{
public:
	///delete default constructor
	CDeclarationBackground() = delete;
	///disable copy constructor
	CDeclarationBackground(CDeclarationBackground&) = delete;
	/// constructor
	/// \param id the id we are using currently
	/// \param filename file being used as the declaration
	CDeclarationBackground(const std::wstring& id, const std::wstring& filename);

	///Getter for the image
	/// Gets the background image
	/// \return Image for the background
	virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mBackground; };

	/// Returns the left image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mBackground; };

	/// Returns the right image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mBackground; };

private:
	/// The background image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mBackground;
};

