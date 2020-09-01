/**
 * \file Door.h
 *
 * \author Samuel Duckworth
 *
 * 
 */

#pragma once
#include "Item.h"
#include <memory>

class CDeclaration;

 /**
  * Door  Declaration
  */
class CDoor :
	public CItem
{
public:
	///deleting the default constructor
	CDoor() = delete;

    CDoor(const CDoor&) = delete;

    ///money constructor
    CDoor(CGnomeGame* game, std::shared_ptr<CDeclaration>dec);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    ///collide for the door item 
    /// \param item whats being hit
    virtual void Collide(CItem* item) override;
    
    /// Draw for the money up item 
    /// \param graphics 
    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
	///image of door
    std::shared_ptr<CDeclaration> mDeclaration; ///< declartion for the item 
};

