/**
 * \file DeclarationMoney.h
 *
 * \author Samuel Duckworth
 *
 * Declaration class for money. Used for reading a declaration object from the level xml
 */
#pragma once
#include "Declaration.h"
#include <memory>

 /**
 *  Money Class Declaration
 */
class CDeclarationMoney : 
	public CDeclaration
{
public:

    ///delete default constructor
    CDeclarationMoney() = delete;

    ///delete default copy constructor
    CDeclarationMoney(const CDeclarationMoney&) = delete;

    /// constructor
    /// \param id the id we are using currently
    /// \param filename file being used as the declaration
    /// \param val The value of the money recieved by the level xml
    CDeclarationMoney(const std::wstring& id, const std::wstring& filename, const int val);

    /// Gets the wall image
    /// \return Image for the wall
    virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mMoney; };

    /// Returns the left image for the case of a platform for example
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mMoney; };

    /// Returns the right image for the case of a platform for example
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mMoney; };

    /// Returns the value of money referenced in the xml
    /// \returns the integer value
	int GetValue() override { return mValue; }

private:

    /// The money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mMoney;

	/// The value specified by the xml for the money
	int mValue;

};


