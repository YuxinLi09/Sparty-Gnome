/**
 * \file Platform.cpp
 *
 * \author Yiteng Zhang
 */
#include "pch.h"
#include "Platform.h"
#include "DeclarationPlatform.h"
using namespace std;
using namespace Gdiplus;


/// Platform grass filenames
/// grass image base
const wstring GrassImage = L"images/grass.png";
/// grass image left
const wstring GrassLeftImage = L"images/grassLeft.png";
/// grass image mid
const wstring GrassMidImage = L"images/grassMid.png";
/// grass image right
const wstring GrassRightImage = L"images/grassRight.png";
/// Platform snow filenames
/// snow image base
const wstring SnowImage = L"images/snow.png";
/// snow image left
const wstring SnowLeftImage = L"images/snowLeft.png";
/// snow image mid
const wstring SnowMidImage = L"images/snowMid.png";
/// snow image right
const wstring SnowRightImage = L"images/snowRight.png";
/// Platform industrial filenames
/// platform industrial57
const wstring IndustrialImage057 = L"images/platformIndustrial_057.png";
/// platform industrial58
const wstring IndustrialImage059 = L"images/platformIndustrial_059.png";
/// platform industrial59
const wstring IndustrialImage060 = L"images/platformIndustrial_060.png";
/// platform industrial61
const wstring IndustrialImage061 = L"images/platformIndustrial_061.png";



/**
 * Constructor
 * \param game The game object we are in
 * \param dec Filename for the image
 */
CPlatform::CPlatform(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, GrassImage)
{
    mDeclaration = dec;
}


/**
 * Destructor for Platform Class
 */
CPlatform::~CPlatform()
{
};

void CPlatform::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());

	mLeft = mDeclaration->GetLeft();

	if (mLeft->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open left");
		AfxMessageBox(msg.c_str());
	}

	mMid = mDeclaration->GetImageName();

	if (mMid->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open mid");
		AfxMessageBox(msg.c_str());
	}

	mRight = mDeclaration->GetRight();
	if (mRight->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open right");
		AfxMessageBox(msg.c_str());
	}

	mWidth = node->GetAttributeIntValue(L"width", 1);
}


/**
 * Draw  for Platform Class
 * \param graphics where we draw
 */
void CPlatform::Draw(Gdiplus::Graphics* graphics)
{
	double imageWidth = 32;

	if (mLeft != nullptr)
	{
		double wid = mLeft->GetWidth();
		double hit = mLeft->GetHeight();


		graphics->DrawImage(mLeft.get(),
			(float)(GetX() - mWidth / 2 - wid / 2),
			(float)(GetY() - hit / 2),
			(float)wid, (float)hit);
	}

    if (mMid != nullptr) 
    {
        double wid = mMid->GetWidth();
        double hit = mMid->GetHeight();
		const int imageWidth = 32;

		for (int i = -1 * mWidth / imageWidth / 2; i < (mWidth / imageWidth / 2) + 1; i++)
		{
			graphics->DrawImage(this->GetImage().get(),
				float(((GetX() - hit / 2) + imageWidth * i)), float(GetY() - wid / 2),
				(float)(this->GetImage()->GetWidth()+1), (float)this->GetImage()->GetHeight());
		}
	}

    if (mRight != nullptr)
    {
        double wid = mRight->GetWidth();
        double hit = mRight->GetHeight();


        graphics->DrawImage(mRight.get(),
            (float)(GetX() + (mWidth / 2 - 1)- wid / 2),
            (float)(GetY() - hit / 2),
            (float)wid, (float)hit);
    }
}



/**
 * Update for Platform Class
 */
void CPlatform::Update()
{

}