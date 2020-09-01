
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project_1_Gadd.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/** This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
// Implement this for the final stuff, currently using the stuff at the bottom for testing material
	CPaintDC paintDC(this);       // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);  // Create GDI+ graphics context

	CRect rect;
	GetClientRect(&rect);

	if (mFirstDraw)
	{
		mGnomeGame.Load(L"levels/level1.xml");
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}
	if (mGnomeGame.GetProceed()) {
		LoadLevels();
	}
	/*
	* Compute the elapsed time since the last draw
	*/
	/// Maximum amount of time to allow for elapsed
	const double MaxElapsed = 0.1;
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mGnomeGame.OnDraw(&graphics, rect.Width(), rect.Height());
	//
	// Prevent tunnelling
	//
	while (elapsed > MaxElapsed)
	{
		mGnomeGame.Update(&graphics, MaxElapsed);

		elapsed -= MaxElapsed;
	}

	// Consume any remaining time
	if (elapsed > 0)
	{
		mGnomeGame.Update(&graphics, elapsed);
	}

}


/**
 * Function to handle when a key is pressed down
 * \param nChar 
 * \param nRepCnt 
 * \param nFlags 
 */
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_RIGHT:
		if (!mGnomeGame.GetDead())
		{
			if(!mGnomeGame.GetVictory()) 
				if(!mGnomeGame.GetFreeze()) mGnomeGame.GetGnome()->SetHorizontalVelocity(1);
		}
		break;

	case VK_LEFT:
		// left arrow pressed
		if (!mGnomeGame.GetDead())
		{
			if (!mGnomeGame.GetVictory()) 
				if (!mGnomeGame.GetFreeze()) mGnomeGame.GetGnome()->SetHorizontalVelocity(-1);
		}
		break;

	case VK_SPACE:
		// space bar pressed
		if (!mGnomeGame.GetFreeze())
		{
			if (!mGnomeGame.GetVictory()) {
				if (mGnomeGame.GetGnome()->GetVelocityY() == 0)
				{
					mGnomeGame.GetGnome()->SetVerticalVelocity();
				}
			}
		}
		break;
	}
}

/**
 * Function to handle when a key is realeased
 * \param nChar 
 * \param nRepCnt 
 * \param nFlags 
 */
void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_RIGHT:
	case VK_LEFT:
		// left or right arrow released
		mGnomeGame.ClearHorizontalVelocity();
		break;
	}
}

/**
* Function to load level 0 from menu
*/
void CChildView::OnLevelLevel0()
{
	// Call Game to load the level
	mGnomeGame.Load(L"levels/level0.xml");
	mGnomeGame.SetCnt(0);
}

/**
* Function to load level 1 from menu
*/
void CChildView::OnLevelLevel1()
{
	// Call Game to load the level
	mGnomeGame.Load(L"levels/level1.xml");
	mGnomeGame.SetCnt(1);
}

/**
* Function to load level 2 from menu
*/
void CChildView::OnLevelLevel2()
{
	// Call Game to load the level
	mGnomeGame.Load(L"levels/level2.xml");
	mGnomeGame.SetCnt(2);
}

/**
* Function to load level 3 from menu
*/
void CChildView::OnLevelLevel3()
{
	// Call Game to load the level
	mGnomeGame.Load(L"levels/level3.xml");
	mGnomeGame.SetCnt(3);
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return FALSE;
}

/**
 *  Add a Gnome item to game.
 */
void CChildView::AddGnome()
{
	auto item = make_shared<CGnome>(&mGnomeGame);
	mGnomeGame.Add(item);
	Invalidate();
}

void CChildView::LoadLevels()
{
	int lev = mGnomeGame.GetCnt();
	mGnomeGame.SetProceed(false);
	switch (lev) {
	case 1:
		mGnomeGame.Load(L"levels/level1.xml");
		break;
	case 2:
		mGnomeGame.Load(L"levels/level2.xml");
		break;
	case 3:
		mGnomeGame.Load(L"levels/level3.xml");
		break;
	default:
		mGnomeGame.SetCnt(1);
		mGnomeGame.Load(L"levels/level1.xml");
	}
}