/**
 * \file DeclarationPlatform.h
 *
 * \author Yiteng Zhang
 *
 * Declaration class used for xml Loading on the Platform Class
 */


#pragma once
#include "Declaration.h"
#include <memory>

 /**
  * Door Platform Declaration
  */
class CDeclarationPlatform :
	public CDeclaration
{
public:

	///delete default constructor
	CDeclarationPlatform() = delete;

    /// Copy constructor (disabled)
    CDeclarationPlatform(const CDeclarationPlatform&) = delete;

    /// constructor
    /// \param id the id we are using currently
    /// \param filename file being used as the declaration
	/// \param filename2 file for left
	/// \param filename3 file for right
    CDeclarationPlatform(const std::wstring& id, const std::wstring& filename, const std::wstring& filename2, const std::wstring& filename3);

    /// Gets the platform image
    /// \return Image for the platfrom
    virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mPlatformImage; };

    /// Returns the left image for the case of a platform for example
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() override { return mLeft; }

    /// Returns the right image for the case of a platform for example
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() override { return mRight; }
private:
	/// The money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mPlatformImage;
    /// The left money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mLeft;
    /// The right money image as a bitmap reference, recieved from the xml
	std::shared_ptr<Gdiplus::Bitmap> mRight;

};
