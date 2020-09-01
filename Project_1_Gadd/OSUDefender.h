/**
 * \file OSUDefender.h
 *
 * \author Zach Fincher
 *
 * 
 */

#pragma once
#include "Item.h"
#include "GnomeGame.h"
#include <memory>


class CDeclaration;

/**
 *  implements Defender class
 */
class COSUDefender : public CItem
{
public:
	/// delete the default constructor
	COSUDefender() = delete;
	/// delete the copy constructor
	COSUDefender(const COSUDefender&) = delete;

	COSUDefender(CGnomeGame*game, std::shared_ptr<CDeclaration>dec);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Function to help decide what items have collided and does approperate operation for said item
	/// \param item object we are working with
	virtual void Collide(CItem* item) override 
	{ 
		if (CheckPresentable())
		{
			if (!GetGnomeGame()->GetSuper())
			{
				GetGnomeGame()->SetGnomeDead();
			}
			else
			{
				RemoveDisplay();
			}
		}
	}

	/// update  defender pos or condition
	/// \param elapsed time we are needing to determine state
	void Update(double elapsed);

private:
	std::shared_ptr<CDeclaration> mDeclaration; ///< declartion for the item 
	CVector mV; ///<velocity
	CVector mPos; ///<Position
	CVector mInitPos; ///<Initial Position for Villain
};


