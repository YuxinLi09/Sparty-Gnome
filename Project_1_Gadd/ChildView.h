
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "GnomeGame.h"
#include "Gnome.h"
#include <string>

// CChildView window


/**
 * Childview class
 */
class CChildView : public CWnd
{
public:
	// Construction
	CChildView();

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	// Destrucor
	virtual ~CChildView();

protected:
	/// paints the screen
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

private:

	CGnomeGame mGnomeGame; ///< GnomeGame var

	/// True until the first time we draw
	bool mFirstDraw = true;

	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates

	

public:
	/// Level 0 constructor
	afx_msg void OnLevelLevel0();

	/// Level 1 constructor
	afx_msg void OnLevelLevel1();

	/// Level 2 constructor
	afx_msg void OnLevelLevel2();

	/// Level 3 constructor
	afx_msg void OnLevelLevel3();
	
	/// timer that helps us with animation
	/// \param nIDEvent basecall
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	///  helps us with eraseing background and reupdating it 
	/// \param pDC basecall
	/// \return FASLE
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	/// Add a gnome charactor to game
	void CChildView::AddGnome();

	/// Load the levels for the game
	void CChildView::LoadLevels();

};

