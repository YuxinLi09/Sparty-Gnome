/**
 * \file SuperS.h
 *
 * \author Yuxin Li
 *
 */

#pragma once
#include "Item.h"
#include <memory>
class CDeclaration;


/**
 * implement the super s
 */
class CSuperS : public CItem
{
public:
    /// delete the default constructor
    CSuperS() = delete;
    /// delete the copy constructor
    CSuperS(const CSuperS&) = delete;

    CSuperS(CGnomeGame*, std::shared_ptr<CDeclaration>);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
    
    /// Collide override
    /// \param item whats being collided with
    virtual void Collide(CItem* item) override;

    /// Draw function for the Super S
    virtual void Draw(Gdiplus::Graphics*) override;

private:
    std::shared_ptr<CDeclaration> mDeclaration; ///< declartion for the item 
};

