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


#include <future/core/system/mac/window_mac.h>


FutureWindow::FutureWindow()
	: m_info(),
	  m_window(NULL)
{}

FutureWindow::~FutureWindow()
{
	Destroy();
}

void FutureWindow::Create(const FutureWindowInfo & info)
{
    glutInit(&m_startUpData.m_numArgs, m_startUpData.m_args);

	m_info.m_width = info.m_width > 0 ? info.m_width : 640;
    m_info.m_height = info.m_height > 0 ? info.m_height : 480;
    m_info.m_name = m_info.m_name != NULL ? m_info.m_name : "Future Window";
    m_info.m_fullScreen = m_info.m_fullScreen;

    NSString * title = [NSString stringWithUTF8String: m_info.m_name];

    NSOpenGLPixelFormatAttribute pixelAttributes[] =
    {
        NSOpenGLPFAScreenMask, CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay),
        NSOpenGLPFAColorSize, 32,
        NSOpenGLPFAClosestPolicy,
        NSOpenGLPFAAlphaSize, 1,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFADepthSize, 1,
        NSOpenGLPFAStencilSize, 1,
        NSOpenGLPFASampleBuffers, 1,
        NSOpenGLPFASamples, 2,
        NSOpenGLPFANoRecovery, 1,
        0,
    };
   
    NSOpenGLPixelFormat * pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes: pixelAttributes] autorelease];

    FUTURE_ASSERT_CRIT(pixelFormat, 4985);
     
    NSRect rect = NSMakeRect(100, 100, m_info.m_width, m_info.m_height);
   
    m_view = [[NSView alloc]initWithFrame:rect];

    FUTURE_ASSERT_CRIT(m_view, 4975);

    m_openGLContext = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];

    FUTURE_ASSERT_CRIT(m_openGLContext, 4976);

    [m_view setAutoresizingMask: (NSViewHeightSizable | NSViewWidthSizable)];
    [m_view setAutoresizesSubviews: NO];
    [m_view setPostsBoundsChangedNotifications: NO];
    [m_view setPostsFrameChangedNotifications: NO];
    [m_view allocateGState];
      
    [m_openGLContext makeCurrentContext]; 
    /*[[NSNotificationCenter defaultCenter]   addObserver:m_view 
                                            selector:@selector(_surfaceNeedsUpdate:) 
                                            name:NSViewGlobalFrameDidChangeNotification 
                                            object:m_view];*/
 

    unsigned int mask = (NSTitledWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask);

    m_window = [[NSWindow alloc] initWithContentRect:rect styleMask:mask backing:NSBackingStoreBuffered defer:NO];

    FUTURE_ASSERT_CRIT(m_window, 4979);

    [m_window setReleasedWhenClosed: NO];
    [m_window setMinSize: NSMakeSize(100.0, 100.0)];
    //[self setShowsResizeIndicator:NO];
    [m_window setContentView: m_view];
    [m_window makeFirstResponder: m_view];
    [m_window setDelegate: m_window];
   
    [m_window setTitle: title];
    [m_window setMiniwindowTitle: title];

    [m_view lockFocus];
    [m_view unlockFocus];
}

void FutureWindow::Destroy()
{
	if(m_window)
    {
        //glutDestroyWindow(m_window);
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

NSWindow * FutureWindow::GetWindow()
{
    return m_window;
}
NSView * FutureWindow::GetView()
{
    return m_view;
}

void FutureWindow::EnableVisibilityUpdates()
{
    FUTURE_ASSERT(m_view);
    [m_view enableVisibilityUpdates];
}
