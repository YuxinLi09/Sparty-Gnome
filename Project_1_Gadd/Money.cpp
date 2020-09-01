/**
 * \file Money.cpp
 *
 * \author Samuel Duckworth
 */

#include "pch.h"
#include "Money.h"
#include "Declaration.h"
using namespace std;
using namespace Gdiplus;
/// 100 dollar image
const wstring MoneyFile100 = L"images/money100.png";
/// 1000 dollar image
const wstring MoneyFile1000 = L"images/money1000.png";

/*
 * CMoney constructor
 * \param game
 * \param dec
 */
CMoney::CMoney(CGnomeGame* game, std::shared_ptr<CDeclaration> dec) : CItem(game, MoneyFile100)
{
    mDeclaration = dec;
}

void CMoney::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    CItem::XmlLoad(node);
    SetImage(mDeclaration->GetImageName());
    mValue = mDeclaration->GetValue();
    mInitPos.Set(GetX(), GetY());
    mPos.Set(GetX(), GetY());
    mV.SetX(0);
    mV.SetY(0);
}

/**
 * Called after the prune state is set
 */
void CMoney::SetMoney(int value)
{
    mValue = value;
    if (mValue == 100)
    {
        SetImageFile(MoneyFile100);
    }
    else if (mValue == 1000)
    {
        SetImageFile(MoneyFile1000);
    }
}

void CMoney::Draw(Gdiplus::Graphics *graphics)
{
    CItem::Draw(graphics);
    double timePresented = GetPresentTime();
    if (!CheckPresentable())
    {
        if (timePresented < 1)
        {
            wstringstream moneyStr;

            moneyStr << L"$" << L"" << GetValue()*GetGnomeGame()->GetCoefficient();

            FontFamily fontFamily(L"Arial");
            Gdiplus::Font font(&fontFamily, 20);
            SolidBrush green(Color(34, 139, 34));
            graphics->DrawString(moneyStr.str().c_str(), -1, &font, PointF(Gdiplus::REAL(mInitPos.X()), Gdiplus::REAL(mInitPos.Y())), &green);

        }

    }
    if (mBank)
    {
        Update();
    }

}


void CMoney::Update()
{
    double initSpeed = 25;
    CVector newV(mV.X(), mV.Y() - initSpeed);
    // Update position
    CVector newP = mPos + newV;
    mV = newV;
    SetLocation(newP.X(), newP.Y());
    mPos = newP;
    if (mPos.Y() == 0)
    {
        RemoveDisplay();
    }
}