/**
 * \file DeclarationWall.h
 *
 * \author Ethan Peterson
 *
 * Declaration class used for xml Loading on the Wall class
 */

#pragma once

#include "Declaration.h"
#include <memory>

 /**
  *  Wall Class Declaration
  */
class CDeclarationWall : public CDeclaration
{
public:
    /// Default constructor (disabled)
    CDeclarationWall() = delete;

    /// Copy constructor (disabled)
    CDeclarationWall(const CDeclarationWall&) = delete;

    /// constructor
    /// \param id the id we are using currently
    /// \param filename file being used as the declaration
    CDeclarationWall(const std::wstring& id, const std::wstring& filename);
    
    /// Gets the wall image
    /// \return Image for the wall
    virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() { return mWall; };

    /// Gets the left image
    /// \return Image for the wall
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() { return mWall; };

    /// Gets the left image
    /// \return Image for the wall
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() { return mWall; };

private:
	std::shared_ptr<Gdiplus::Bitmap> mWall; ///< image we are loading
};

