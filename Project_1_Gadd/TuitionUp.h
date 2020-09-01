/**
 * \file TuitionUp.h
 *
 * \author Logan Wolfe
 *
 * Holds the Tuition class
 */

#pragma once
#include "Item.h"
#include <memory>
class CDeclaration;

/**
 * TuitionUp Item Class
 */
class CTuitionUp : public CItem
{
public:
	/// delete the default constructor
	CTuitionUp() = delete;
	/// delete the copy constructor
	CTuitionUp(const CTuitionUp&) = delete;

	CTuitionUp(CGnomeGame *, std::shared_ptr<CDeclaration> );

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /// check if item is presented
    /// \return mBonus
    virtual bool CheckPresentable() override { return !mBonus; };
    
    /// Collide override
    /// \param item what we are working with
    virtual void Collide(CItem* item) override;

    /// Draw for the tuition up item 
    virtual void Draw(Gdiplus::Graphics*) override;
    
    /// update function for an item
    void Update();

private:
    bool mBonus = false; ///< check if we have the bonus on for money
	double mValue; ///< item value
    std::shared_ptr<CDeclaration> mDeclaration; ///< declartion for the item 
    CVector mV; ///< item vector for velocity
    CVector mPos; ///< item vector for pos which is updated
    CVector mInitPos; ///< item vector for inital position
};

