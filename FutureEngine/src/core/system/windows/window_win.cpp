/*!
*	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
*
*	Thank you for taking a look at my code. If you like it, please click
*	the donation button at the bottom of the sidebar on my blog. Thanks!
*
*	Licensed under the Apache License, Version 2.0 (the "License");
*	you may not use this file except in compliance with the License.
*	You may obtain a copy of the License at
*
*		http://www.apache.org/licenses/LICENSE-2.0
*
*	Unless required by applicable law or agreed to in writing, software
*	distributed under the License is distributed on an "AS IS" BASIS,
*	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*	See the License for the specific language governing permissions and
*	limitations under the License.
*
*/

/*
*	The main game system, this handles start up and shut down of the entire system
*	
*/


#include <future/core/system/windows/window.h>

FutureWindow::FutureWindow()
	: m_info(),
	  m_instance(NULL),
	  m_window(NULL),
	  m_proc(NULL)
	  {}

FutureWindow::~FutureWindow()
{
	DestroyWindow();
}

void FutureWindow::CreateWindow(const FutureWindowInfo & info)
{
	FUTURE_ASSERT(!m_window);
	
	m_info.m_width = info.m_width > 0 ? info.m_width : 640;
    m_info.m_height = info.m_height > 0 ? info.m_height : 480;
    m_info.m_name = m_info.m_name != NULL ? m_info.m_name : "Future Window";
    m_info.m_fullScreen = m_info.m_fullScreen;

    WNDCLASSEX wcex;

    wcex.cbSize 		= sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = m_proc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = m_instance;
    wcex.hIcon          = LoadIcon(m_instance, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = "FutureWindowClassEX";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    FUTURE_ASSERT_CRIT(RegisterClassEx(&wcex));

   	m_window = CreateWindow(
        "FutureWindowClassEX",
        m_info.m_name, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        m_info.m_width, m_info.m_height,
        NULL, NULL, m_instance, NULL
    );

    FUTURE_ASSERT_CRIT(m_window);

    ShowWindow(m_window, SW_SHOW);
    UpdateWindow(m_window);
}

void FutureWindow::DestroyWindow()
{
	if(m_window)
	{
		::DestroyWindow(m_window);
	}
	m_window = NULL;
}

void FutureWindow::GetInfo(FutureWindowInfo & info)
{
	info.m_width = m_info.m_width;
    info.m_height = m_info.m_height;
    info.m_name = m_info.m_name;
    info.m_fullScreen = m_info.m_fullScreen;

    info.m_dpiX = m_info.m_dpiX;
    info.m_dpiY = m_info.m_dpiY;
}

void		FutureWindow::SetInstance(HINSTANCE inst)
{
	m_instance = inst;
}

void		FutureWindow::SetWindProc(WNDPROC proc)
{
	m_proc = proc;
}

HINSTANCE	FutureWindow::GetInstance()
{
	return m_instance;
}
HWND		FutureWindow::GetWindow()
{
	return m_window;
}
