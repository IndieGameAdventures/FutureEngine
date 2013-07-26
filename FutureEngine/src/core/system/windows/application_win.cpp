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
*	Application class used by Windows 7 and Windows 8 Desktop
*/

#include <future/core/system/windows/application_win.h>

FutureApplication * FutureApplication::ms_instance;

int WINAPI WinMain (_In_ HINSTANCE hInstance,
					_In_opt_ HINSTANCE hPrevInstance,
					_In_ LPSTR lpCmdLine,
					_In_ int nShowCmd
					)
{
	FutureApplicationImpl::CreateInstance(hInstance);
	FutureMain();
	FutureApplicationImpl::GetInstance()->Shutdown();
	FutureApplicationImpl::DestroyInstance();
    return 0;//futureWinMSG.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

void FutureApplicationImpl::CreateInstance(HINSTANCE inst)
{
	FUTURE_ASSERT(!ms_instance);
	ms_instance = new FutureApplicationImpl(inst);
}

void FutureApplicationImpl::DestroyInstance()
{
	FUTURE_ASSERT(ms_instance);
	delete ms_instance;
	ms_instance = NULL;
}

FutureApplicationImpl::FutureApplicationImpl(HINSTANCE inst)
	: FutureApplication(),
	  m_instance(inst)
{
	m_window = new FutureWindow();
	FutureWindowInfo info;
	info.m_fullScreen = false;
	info.m_height = 480;
	info.m_width = 640;
	info.m_name = "Future Test Window";
	m_window->SetInstance(m_instance);
	m_window->SetWindProc(WndProc);
	m_window->Create(info);
}

FutureApplicationImpl::~FutureApplicationImpl()
{
	if(m_window)
	{
		m_window->Destroy();
		delete m_window;
		m_window = NULL;
	}
}
	
void	FutureApplicationImpl::Initialize()
{
	FutureApplication::Initialize();
}

void	FutureApplicationImpl::Shutdown()
{
	FutureApplication::Shutdown();
}

void	FutureApplicationImpl::RunMainLoop()
{
	while(m_running)
	{
		if(PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);

			if(m_msg.message == WM_QUIT)
			{
				m_running = false;
			}
		}
		
		m_systemController->PreSynchronizeAll();
		m_systemController->UpdateAll();
		m_systemController->PostSynchronizeAll();

	}
}

