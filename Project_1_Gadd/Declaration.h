/**
 * \file Declaration.h
 *
 * \author Ethan Peterson et al
 *
 * Base Declaration class used to read the declaration type from the xml
 */

#pragma once
#include <string>
#include <memory>

/**
 *  Declaration Base Class 
 */
class CDeclaration
{
public:
    /// Default constructor (disabled)
    CDeclaration() = delete;

    /// Copy constructor (disabled)
    CDeclaration(const CDeclaration&) = delete;

    /// Constructor
    /// \param id The ID from the XML
    CDeclaration(const std::wstring& id);

    /// Destructor
    virtual ~CDeclaration() {};

    ///Gets the items ID
    /// \returns mID the ID of a specific item
	std::wstring GetID() const { return mID; }

	/// function to get image name
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetImageName() = 0;

    /// Returns the left image for the case of a platform for example
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetLeft() = 0;

    /// Returns the left image for the case of a platform for example
    /// \returns the bitmap image referenced in the xml
	virtual std::shared_ptr<Gdiplus::Bitmap> GetRight() = 0;
	
    /// Returns the value of money referenced in the xml
    /// \returns the integer value
	virtual int GetValue() { return 0; }

private:
    std::wstring mID; ///< ID for a item in xml
};

