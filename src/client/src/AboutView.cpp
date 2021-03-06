#include "stdafx.h"
#include "AboutView.h"

#include "crackers.h"
#include "IHtmlDataLoader.h"
#include "Rect.h"
#include "resourceppc.h"
#include "Tools.h"

using namespace std;
using namespace Tools;

//----------
// interface
//----------

AboutView::AboutView
	( HINSTANCE         instance
	, bool              highRes
	, IHtmlDataLoader & htmlDataLoader
	)
	: instance (instance)
	, HTMLayoutWindow(L"about.htm", highRes, htmlDataLoader)
{
}

void AboutView::Create(HWND parent)
{
	this->parent = parent;

	wstring wndClass = LoadStringResource(IDC_ABOUT_VIEW);

	if (!RegisterClass(wndClass))
		throw std::exception("Class could not be registered.");
}

//--------------------------
// IAboutView implementation
//--------------------------

void AboutView::Hide()
{
	::CloseWindow(hwnd_);
}

void AboutView::Show()
{
	wstring wndTitle = LoadStringResource(IDS_APP_TITLE);
	wstring wndClass = LoadStringResource(IDC_ABOUT_VIEW);

	DWORD windowStyle   (WS_POPUP);
	DWORD windowExStyle (WS_EX_CAPTIONOKBTN);

	Rect rect;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, FALSE);

	hwnd_ = ::CreateWindowEx
		( windowExStyle    // dwExStyle
		, wndClass.c_str() // lpClassName
		, wndTitle.c_str() // lpWindowName
		, windowStyle      // dwStyle
		, rect.GetX()      // x
		, rect.GetY()      // y
		, rect.GetWidth()  // nWidth
		, rect.GetHeight() // nHeight
		, parent           // hWndParent
		, NULL             // hMenu
		, instance         // hInstance
		, this             // lpParam
		);
	if (!hwnd_)
		throw std::exception("Window creation failed.");

	SHMENUBARINFO menuBarInfo = { sizeof(menuBarInfo) };
	menuBarInfo.hwndParent = hwnd_;
	menuBarInfo.nToolBarId = IDR_OK_MENUBAR;
	menuBarInfo.hInstRes   = instance;
	::SHCreateMenuBar(&menuBarInfo);
	menuBar = menuBarInfo.hwndMB;

	ResizeWindow();

	ShowWindow(hwnd_, SW_SHOW);
}

//------------------------
// window message handlers
//------------------------

void AboutView::OnCommand(Msg<WM_COMMAND> & msg)
{
	switch (msg.CtrlId())
	{
	case IDM_OK: SignalClose(); break;
	case IDOK:   SignalClose(); break;
	}
}

void AboutView::OnKeyUp(Msg<WM_KEYUP> & msg)
{
	if (msg.VKey() == 0x1b)
	{
		SignalClose();
		msg.handled_ = true;
	}
}

void AboutView::ProcessMessage(WndMsg &msg)
{
	static Handler mmp[] =
	{
		&AboutView::OnCommand,
		&AboutView::OnKeyUp,
	};
	try
	{
		if (!Handler::Call(mmp, this, msg))
			__super::ProcessMessage(msg);
	}
	catch (const std::exception & e)
	{
		::NKDbgPrintfW(L"%s\n", ConvertToUnicode(e.what()).c_str());
		throw e;
	}
}

//------------------
// utility functions
//------------------

ATOM AboutView::RegisterClass(const wstring & wndClass)
{
	WNDCLASS wc = { 0 };
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = &AboutView::WndProc<AboutView>;
	wc.hInstance     = instance;
	wc.hIcon         = LoadIcon(instance, MAKEINTRESOURCE(IDI_CLIENT));
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = wndClass.c_str();
	return ::RegisterClass(&wc);
}

void AboutView::ResizeWindow()
{
	Rect desktopRect;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &desktopRect, FALSE);

	Rect menuBarRect;
	::GetWindowRect(menuBar, &menuBarRect);

	int windowWidth  (desktopRect.GetWidth());
	int windowHeight (desktopRect.GetHeight() - menuBarRect.GetHeight());

	::MoveWindow
		( hwnd_              // hwnd
		, desktopRect.GetX() // x
		, desktopRect.GetY() // y
		, windowWidth        // nWidth
		, windowHeight       // nHeight
		, TRUE			     // bRepaint
		);
}
