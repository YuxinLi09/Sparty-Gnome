
// Project_1_Gadd.h : main header file for the Project_1_Gadd application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols



/**
 *CProject1GaddApp:
 *See Project_1_Gadd.cpp for the implementation of this class
 */
class CProject1GaddApp : public CWinApp
{
public:
	CProject1GaddApp() noexcept;


// Overrides
public:
	/// Loads the game instance
	///\returns bool
	virtual BOOL InitInstance();

	/// Exits the game instance
	///\returns int
	virtual int ExitInstance();

// Implementation

public:
	/// Talks about the app?
	afx_msg void OnAppAbout();
	/// Declares message
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput; ///< base gdiplus startup info
	ULONG_PTR gdiplusToken = 0; ///< base gdiplus tkn
};

extern CProject1GaddApp theApp;
