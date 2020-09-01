/**
 * \file DeclarationTuitionUp.h
 *
 * \author Ethan Peterson et al
 *
 * Declaration class for TuitionUp. Used for reading a declaration object from the level xml
 */

#pragma once
#include "Declaration.h"
#include <string>


/**
 *  TuitionUp Class Declaration
 */
class CDeclarationTuitionUp :
	public CDeclaration
{
public:


	///delete default constructor
	CDeclarationTuitionUp() = delete;
	///disable copy constructor
	CDeclarationTuitionUp(CDeclarationTuitionUp&) = delete;


	CDeclarationTuitionUp(const std::wstring& id, const std::wstring& filename);

	///Getter for the image
	/// Gets the background image
	/// \return Image for the background
	virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mTuitionUp; };

	/// Returns the left image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mTuitionUp; };

	/// Returns the right image for the case of a platform for example
	/// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mTuitionUp; };

private:
	/// The money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mTuitionUp;

	double mValue; ///< value of the item we increase by 
	
};

