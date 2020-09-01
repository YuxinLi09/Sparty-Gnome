#include "pch.h"
#include "ItemBackground.h"
#include "DeclarationBackground.h"

using namespace Gdiplus;
using namespace xmlnode;
using namespace std;

const wstring BackgroundFile = L"images/backgroundColorDesert.png";

/**
 * Constructor for the background declaration
 * \param game game to link
 * \param dec declaration to bind
 */
CItemBackground::CItemBackground(CGnomeGame* game,std::shared_ptr<CDeclaration> dec) : CItem(game,BackgroundFile)
{
	mDeclaration = dec;
}

/**
 * Loads the background from the linked Declaration
 * \param node Xml Node that contains the data.
 */
void CItemBackground::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);
	SetImage(mDeclaration->GetImageName());

}

