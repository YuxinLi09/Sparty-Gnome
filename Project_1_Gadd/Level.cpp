/**
 * \file Level.cpp
 *
 * \author Logan Wolfe
 */

#include "pch.h"
#include "Level.h"

#include "Declaration.h"
#include "DeclarationBackground.h"
#include "DeclarationWall.h"
#include "DeclarationMoney.h"
#include "DeclarationPlatform.h"
#include "DeclarationVillain.h"
#include "DeclarationTuitionUp.h"
#include "DeclarationDoor.h"
#include "DeclarationOSUDefender.h"
#include "DeclarationSuperS.h"
#include "Item.h"
#include "ItemBackground.h"
#include "Wall.h"
#include "Platform.h"
#include "Door.h"
#include "Money.h"
#include "Villain.h"
#include "TuitionUp.h"
#include "OSUDefender.h"
#include "SuperS.h"



using namespace Gdiplus;
using namespace xmlnode;
using namespace std;

/// the background file we are using as base
const wstring BackgroundFile = L"images/backgroundColorDesert.png";
/**
 * Constructor for Level class
 * \param game Game to associate the level to
 */
CLevel::CLevel(CGnomeGame* game)
{
	/// Assign the game to mGame
	mGame = game;
}

/**
 * Destructor for Level Class
 */
CLevel::~CLevel()
{
};

/**
 * Load the level from a .lvl XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * \param filename The filename of the file to load the level's items from.
 */
void CLevel::Load(const std::wstring& filename)
{
    /// Code to populate the mDeclarations with the declarations
        // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        // Once we know it is open, clear the existing data
        Refresh();

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        const int startX = root->GetAttributeIntValue(L"start-x", 1);
        const int startY = root->GetAttributeIntValue(L"start-y", 1);

        mGame->AddGnome(startX, startY);

        for (auto node : root->GetChildren())
        {
            /// Call to populate mItems with items based on declarations
            if (node->GetType() == NODE_ELEMENT && node->GetName() == L"declarations")
            {
                /// loop through all children of Declaration
                for (auto kid : node->GetChildren())
                {
                    XmlDecItem(kid);
                }
            }
			///get children of node with check for which node dealing with
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"items")
			{
				/// loop through all children of Declaration
				for (auto itemKid : node->GetChildren())
				{
					XmlItem(itemKid);
				}
				
			}
            
        }


    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
    // Send the items to the game!
    for (auto item : mItems)
    {
        mGame->Add(item);
    }
	// Send the items to the game!
	for (auto background : mBackgrounds)
	{
		mGame->AddBackground(background);
	}
}
/**
* Deletes current level's declaration, and items in both level and game
*/
void CLevel::Refresh()
{
    mDeclarations.clear();

    mItems.clear();

	mBackgrounds.clear();

    mGame->Refresh();

}
/**
* Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CLevel::XmlDecItem(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    // A pointer for the declaration we are loading
    shared_ptr<CDeclaration> dec;

    // We have an declaration. What type?
    wstring type = node->GetName();
    if (type == L"background")
    {
        dec = make_shared<CDeclarationBackground>(node->GetAttributeValue(L"id",L""), L"images/" + node->GetAttributeValue(L"image",L""));
    }

    if (type == L"wall")
    {
        dec = make_shared<CDeclarationWall>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""));
    }

    if (type == L"platform")
    {
        dec = make_shared<CDeclarationPlatform>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"mid-image", L""), L"images/" + node->GetAttributeValue(L"left-image", L""), L"images/" + node->GetAttributeValue(L"right-image", L""));
    }

    if (type == L"villain")
    {
        dec = make_shared<CDeclarationVillain>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""));
    }

    if (type == L"money")
    {
        dec = make_shared<CDeclarationMoney>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""), node->GetAttributeIntValue(L"value", 1));
    }

    if (type == L"tuition-up")
    {
        dec = make_shared<CDeclarationTuitionUp>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""));
    }

    if (type == L"door")
    {
        dec = make_shared<CDeclarationDoor>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""));
    }

    if (type == L"defender")
    {
        dec = make_shared<CDeclarationOSUDefender>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""));
    }

    if (type == L"spartan")
    {
        dec = make_shared<CDeclarationSuperS>(node->GetAttributeValue(L"id", L""), L"images/" + node->GetAttributeValue(L"image", L""));
    }
    
    if (dec != nullptr)
    {
        mDeclarations.push_back(dec);
    }
    

}
/**
* Handle an item node.
* \param node Pointer to XML node we are handling
*/
void CLevel::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	// A pointer for the item we are loading
	shared_ptr<CItem> item;
	shared_ptr<CItemBackground> background;
	wstring id;
	// We have an item. What type?
	wstring type = node->GetName();
	if (type == L"background")
	{	
		for (auto declaration : mDeclarations)
		{
			id = node->GetAttributeValue(L"id", L"");
			if (id == declaration->GetID())
			{
				background = make_shared<CItemBackground>(mGame, declaration);
			}
		}
		
	}
    if (type == L"wall")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CWall>(mGame, declaration);
            }
        }
    }

    if (type == L"platform")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CPlatform>(mGame, declaration);
            }
        }
    }

    if (type == L"door")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CDoor>(mGame, declaration);
            }
        }
    }

    if (type == L"money")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CMoney>(mGame, declaration);
            }
        }
    }

    if (type == L"villain")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CVillain>(mGame, declaration);
            }
        }
    }

    if (type == L"tuition-up")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CTuitionUp>(mGame, declaration);
            }
        }

    }

    if (type == L"defender")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<COSUDefender>(mGame, declaration);
            }
        }

    }

    if (type == L"spartan")
    {
        for (auto declaration : mDeclarations)
        {
            id = node->GetAttributeValue(L"id", L"");
            if (id == declaration->GetID())
            {
                item = make_shared<CSuperS>(mGame, declaration);
            }
        }

    }

	if (item != nullptr)
	{
		item->XmlLoad(node);
		mItems.push_back(item);
	}
	if (background != nullptr)
	{
		background->XmlLoad(node);
		mBackgrounds.push_back(background);
	}
}