/**
 * \file Level.h
 *
 * \author Logan Wolfe
 *
 * Holds the class to represent a level
 */
#pragma once
#include "Item.h"
#include "GnomeGame.h"
#include "Declaration.h"
#include <vector>
#include <memory>
#include "XmlNode.h"

/**
 * Class representing a level
 */
class CLevel
{
public:
	CLevel(CGnomeGame* game);
	/// Disabling the default constructor
	CLevel() = delete;
	/// Disabling the Copy constructor
	CLevel(const CLevel&) = delete;

	~CLevel();

    void Load(const std::wstring& filename);

	void Refresh();

	void XmlDecItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);
        
private:
	/// collection of declarations for the current level
	std::vector< std::shared_ptr<CDeclaration> > mDeclarations;
	/// collection of items stored into a vector to push to the game
	std::vector< std::shared_ptr<CItem> > mItems;
	/// game the level is associated with
	CGnomeGame* mGame;
	/// A collection of items that are contained in gnomegame
	std::vector<std::shared_ptr<CItemBackground> > mBackgrounds;
    
    
};

