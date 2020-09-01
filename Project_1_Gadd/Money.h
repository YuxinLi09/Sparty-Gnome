/**
 * \file Money.h
 *
 * \author Samuel Duckworth
 *
 * 
 */

#pragma once
#include "Item.h"
#include "GnomeGame.h"
#include <string>

class CDeclaration;
/**
 * Class defining a money item
 */
class CMoney 
    : public CItem
{
public:
	///disable default constructor
	CMoney() = delete;

    /// Copy constructor (disabled)
    CMoney(const CMoney&) = delete;

	///money constructor
    /// \param dec
    /// \param game
    CMoney(CGnomeGame* game, std::shared_ptr<CDeclaration> dec);

    /// load for the money
    /// \param node the item we are loading 
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
    
    /// set the value of the money item 
    /// \param value set the value
	void SetMoney(int value);

    /// check if the money item on screen has been collected
    /// \return mBank Check for if collectred
    virtual bool CheckPresentable() override { return !mBank; };

    ///collide for the money item 
    /// \param item whats being hit
    virtual void Collide(CItem* item) override
    {
        if (CItem::CheckPresentable() && !mBank)
        {
            GetGnomeGame()->IncreaseMoney(int(mValue));
            mBank = true;
            ClearPresentTime();
        }
    }

    /// get the value of the money item 
    /// \return mValue return the value 
    double GetValue() { return mValue; }
   
    /// Draw for the money up item 
    virtual void Draw(Gdiplus::Graphics*) override;

    /// update function for an item
    void Update();

private:

    bool mBank = false; ///< bool for the money item if we have collected it 
    double mValue; ///< value for the money item
    ///declaration pointer
    std::shared_ptr<CDeclaration> mDeclaration; ///< decalrtion for the money item
    CVector mV; ///<velocity it moves at 
    CVector mPos; ///<Position after moved
    CVector mInitPos; ///<Initial Position for money

};

