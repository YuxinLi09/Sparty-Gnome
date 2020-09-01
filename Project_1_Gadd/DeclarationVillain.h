/**
 * \file DeclarationVillain.h
 *
 * \author Ethan Peterson
 *
 * Declaration class used for xml Loading on the Villain Class
 */

#pragma once

#include "Declaration.h"
#include <memory>


 /**
  *  Villain Class Declaration
  */
class CDeclarationVillain : public CDeclaration
{
public:
    /// Default constructor (disabled)
    CDeclarationVillain() = delete;

    /// Copy constructor (disabled)
    CDeclarationVillain(const CDeclarationVillain&) = delete;

    /// constructor
    /// \param id the id we are using currently
    /// \param filename file being used as the declaration
    CDeclarationVillain(const std::wstring& id, const std::wstring& filename);

    /// Gets the wall image
    /// \return Image for the villain
    virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mVillain; };

    /// Gets the left image
    /// \return Image for the villain
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mVillain; };

    /// Gets the right image
    /// \return Image for the villain
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mVillain; };

private:
	std::shared_ptr<Gdiplus::Bitmap> mVillain; ///< image we are loading
};

