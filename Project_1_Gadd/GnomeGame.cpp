#include "pch.h"
#include "GnomeGame.h"
#include "Level.h"
#include "ScoreBoard.h"
#include "Gnome.h"
#include "ItemBackground.h"
#include "TuitionUp.h"
using namespace Gdiplus;
using namespace std;

/**
 * GnomeGame constructor
 */
CGnomeGame::CGnomeGame()
{
    mScoreBoard = make_shared<CScoreBoard>(this) ; /// use shared ptr
    mLevel = make_shared<CLevel>(this);
}

/**
 * Destructor.
 */
CGnomeGame::~CGnomeGame()
{
}

/** Draw the gnomegame
* \param graphics The GDI+ graphics context to draw on
* \param width the width we are using
* \param height the height we are using
*/
void CGnomeGame::OnDraw(Gdiplus::Graphics* graphics, int width, int height)
{
    // Determine the height of the screen
    mScreenHeight = float(height);

    mScale = float(height) / float(Height);
    graphics->ScaleTransform(mScale, mScale);

    // Determine the width of the screen
    mScreenWidth = (float)width / mScale;

    // Determine the virtual width
    auto virtualWidth = (float)width / mScale;
    auto xOffset = (float)-GetGnome()->GetX() + virtualWidth / 2.0f;

    auto save = graphics->Save();
    graphics->TranslateTransform(xOffset, 0);

    //Anything drawn here will have xOffset added to every X location
	for (auto background : mBackgrounds)
	{
        if(background->GetX() - background->GetWidth() / 2 <= GetGnome()->GetX() + virtualWidth / 1.5 && background->GetX() + background->GetWidth() / 2 >= GetGnome()->GetX() - virtualWidth / 1.5)
        {
            background->Draw(graphics);
        }
        
		
	}
    for (auto item : mItems)
    {
        item->Draw(graphics);
    }
    graphics->Restore(save);

}

/**
 * Add an item to the gnomegame
 * \param item New item to add
 */
void CGnomeGame::Add(std::shared_ptr<CItem> item)
{
    mItems.push_back(item);
}

/**
 * Add an item to the gnomegame
 * \param item New background to add
 */
void CGnomeGame::AddBackground(std::shared_ptr<CItemBackground> item)
{
	mBackgrounds.push_back(item);
}

void CGnomeGame::SetHorizontalVelocity(int sign) {
    mSign = sign;
    for (auto item : mItems)
    {
        item->SetHorizontalVelocity(sign);
    }
};

void CGnomeGame::ClearHorizontalVelocity() {
    mSign = 0;
    for (auto item : mItems)
    {
        item->ClearHorizontalVelocity();
    }
};


void CGnomeGame::CollideGnome(double distance) {
    for (auto item : mItems)
    {
        item->CollideGnome(distance);
    }
}

/**
 * Clear the GnomeGame data.
 *
 * Deletes all known items in the game progress.
 */
void CGnomeGame::ClearGame()
{
    mItems.clear();
	mBackgrounds.clear();
}

/** Handle updates for animation
* \param elapsed The time since the last update
* \param graphics the graphics we are drawing on
*/
void CGnomeGame::Update(Gdiplus::Graphics* graphics, double elapsed)
{
    mTime += elapsed;
    mGameOverTime += elapsed;
    mSuperTime += elapsed;
    mScoreBoard->Draw(graphics);

    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
    if (GetDead())
    {
        wstringstream caption;
        const float screenHeight = GetScreenHeight();
        const float screenWidth = GetScreenWidth();

        caption << L"You Lose!";

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 90);
        SolidBrush pink(Color(255, 105, 180));

        const int offset = 24;

        double len = caption.str().size();

        graphics->DrawString(caption.str().c_str(), -1, &font, PointF(Gdiplus::REAL(screenWidth / 2 - (len * offset)), Gdiplus::REAL(screenHeight / 2)), &pink);
        if (GetGameOverTime() > 3)
        {
            SetProceed(true);
        }
    }
    else if (GetFreeze())
    {
        wstringstream caption;
        const float screenHeight = GetScreenHeight();
        const float screenWidth = GetScreenWidth();

        caption << L"Level "<<GetCnt()<<" Begin!";

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 80);
        SolidBrush pink(Color(255, 105, 180));

        const int offset = 24;

        double len = caption.str().size();

        graphics->DrawString(caption.str().c_str(), -1, &font, PointF(Gdiplus::REAL(screenWidth / 2 - (len * offset)), Gdiplus::REAL(screenHeight / 2)), &pink);
        if (mTime > 3)
        {
            SetUnfreeze();
        }
    }
    else if (GetSuper())
    {
        wstringstream caption;
        const float screenHeight = GetScreenHeight();
        const float screenWidth = GetScreenWidth();

        caption << L"INVINCIBLE MODE";

        FontFamily fontFamily(L"Arial");
        Gdiplus::Font font(&fontFamily, 25);
        SolidBrush gold(Color(255, 140, 0));

        double len = caption.str().size();

        graphics->DrawString(caption.str().c_str(), -1, &font, PointF(20, 130), &gold);
        if (mSuperTime > 10)
        {
            SetSuper(false);
        }
    }

}
/**
 * Tells system to save the level
 *
 * Open an XML file and stream the level data to it.
 *
 * \param filename The filename of the file to save the aquarium to
 */
void CGnomeGame::Save(const std::wstring& filename)
{
    /// This will call level's load once I add the var
}

/**
* Deletes current games's items
*/
void CGnomeGame::Refresh()
{
    mItems.clear();
	mBackgrounds.clear();
    mMoney = 0;
    mTime = 0;
    mCoefficient = 1;
    mGnomeDead = false;
    mCompleted = false;
    mProceed = false;
    mFreeze = true;
}
/**
 * Load the level from a .lvl XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * \param filename The filename of the file to load the level's items from.
 */
void CGnomeGame::Load(const std::wstring& filename)
{
    mLevel->Load(filename);
}

std::shared_ptr<CItem> CGnomeGame::CollisionXTest(CItem* gnome)
{
    for (auto item : mItems)
    {
        if (item.get() == gnome) {
            continue;
        }

        if (abs(item->GetY() - gnome->GetY()) <= (item->GetHeight() + gnome->GetHeight()) / 2)
        {
            double horizontalD = abs(item->GetX() - gnome->GetX()) - (item->GetWidth() + gnome->GetWidth()) / 2;

            if (horizontalD <= 0)
            { 
                item->Collide(gnome);

                if (item->CheckPresentable())
                {
                    return item;
                }
            }
        }
    }
    return nullptr;
}

std::shared_ptr<CItem> CGnomeGame::CollisionYTest(CItem* gnome)
{
    for (auto item : mItems)
    {
        if (item.get() == gnome) {
            continue;
        }

        if (abs(item->GetX() - gnome->GetX()) <= (item->GetWidth() + gnome->GetWidth()) / 2)
        {
            double verticalD = abs(item->GetY() - gnome->GetY()) - (item->GetHeight() + gnome->GetHeight()) / 2;

            if (verticalD <= 0)
            {
                item->Collide(gnome);

                if (item->CheckPresentable())
                {
                    return item;
                }
            }
        }
    }
    return nullptr;
}

///adds a gnome to the game
///\param x coordinate to place gnome
///\param y coordinate to place gnome
void CGnomeGame::AddGnome(const int x, const int y)
{
    shared_ptr<CGnome> gnome = make_shared<CGnome>(this);
    gnome->SetLocation(x, y);
    Add(gnome);
}
