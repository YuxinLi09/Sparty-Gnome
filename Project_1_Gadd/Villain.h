/**
 * \file Villain.h
 *
 * \author Ethan Peterson
 *
 * Class defining the Villain Object. Derived from CItem
 */

#pragma once

#include<string>
#include"Item.h"
#include "GnomeGame.h"

class CDeclaration;

 /**
  * Class defining a Villain object
  */
class CVillain : public CItem
{
public:
    /// Default constructor (disabled)
    CVillain() = delete;

    /// default constructor
    ~CVillain();
    /// Copy constructor (disabled)
    CVillain(const CVillain&) = delete;

    CVillain(CGnomeGame* game, std::shared_ptr<CDeclaration> dec);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);
    
    /// Collide function used to test if the gnome collides with a villain object
    /// \param item the Gnome (player) item
    virtual void Collide(CItem* item) override 
    { 
        if (CheckPresentable())
        {
            if (!GetGnomeGame()->GetSuper())
            {
                GetGnomeGame()->ClearGameOverTime();
                GetGnomeGame()->SetGnomeDead();
            }
            else
            {
                RemoveDisplay();
            }
        }
    }

    void CVillain::Update(double elapsed);

private:
    std::shared_ptr<CDeclaration> mDeclaration; ///< Declaration object used to load from the xml
    CVector mV; ///<velocity
    CVector mPos; ///<Position
    CVector mInitPos; ///<Initial Position for Villain
    //int mSpeed = 222;
};