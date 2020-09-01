#pragma once
#include "Item.h"

class CDeclaration;
/**
 * Class defining a background
 */
class CItemBackground :
	public CItem
{
public:
    /// Default constructor (disabled)
    CItemBackground() = delete;

    /// Copy constructor (disabled)
    CItemBackground(const CItemBackground&) = delete;

	/// constructor
    CItemBackground(CGnomeGame* game, std::shared_ptr<CDeclaration> dec);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// collide for the background
    /// \param item
    virtual void Collide(CItem* item) override {};

private:
	std::shared_ptr<CDeclaration> mDeclaration; ///< declartion for the item 

};

