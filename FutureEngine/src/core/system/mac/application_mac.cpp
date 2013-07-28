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
*	Application class used by Mac
*/

#import <future/core/system/mac/application_mac.h>

FutureApplication * FutureApplication::ms_instance;

int main(int argc, char** argv)
{
	FutureApplicationImpl::CreateInstance();
	FutureMain();
	FutureApplicationImpl::GetInstance()->Shutdown();
	FutureApplicationImpl::DestroyInstance();
    return 0;
}

void FutureApplicationImpl::CreateInstance()
{
	FUTURE_ASSERT(!ms_instance);
	NSApp = [FutureApplicationMac sharedApplication];
	ms_instance = new FutureApplicationImpl();
}

void FutureApplicationImpl::DestroyInstance()
{
	FUTURE_ASSERT(ms_instance);
	delete ms_instance;
	ms_instance = NULL;
}

FutureApplicationImpl::FutureApplicationImpl()
	: FutureApplication()
{

	m_window = new FutureWindow();
	FutureWindowInfo info;
	info.m_fullScreen = false;
	info.m_height = 480;
	info.m_width = 640;
	info.m_name = "Future Test Window";
	FutureWindowLinuxData data;
	data.m_numArgs = argc;
	data.m_args = argv;
	m_window->SetStartUpData(data);
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
	FUTURE_ASSERT(NSApp != nil);
	FUTURE_ASSERT(m_window);

	[NSApp run];
}

void	FutureApplicationImpl::UpdateMainLoop()
{
	m_systemController->PreSynchronizeAll();
	m_systemController->UpdateAll();
	m_systemController->PostSynchronizeAll();
}

void _EnableVisibilityUpdates()
{
	((FutureWindow*)FutureApplication::GetInstance()->GetWindow())->EnableVisibilityUpdates();
}

void _UpdateMainLoop()
{
	((FutureApplicationImpl*)FutureApplication::GetInstance())->UpdateMainLoop();
}

@implementation FutureApplicationMac
 
- (id)init
{
   	if((self = [super init]) != nil) 
   	{
      	[self setDelegate: self];
      	return self;
   	}
   	return nil;
}
 
- (void)dealloc
{
   	[[NSNotificationCenter defaultCenter] removeObserver: self];
   	[super dealloc];
}
 
- (void)finalize
{
   	[[NSNotificationCenter defaultCenter] removeObserver: self];
   	[super finalize];
}
 
 
- (void)_runEventLoop:(NSAutoreleasePool **)pool
{
	while(true)
   	{
      	NSEvent * event = [self   nextEventMatchingMask: NSAnyEventMask
         	                      untilDate: [NSDate distantPast]
                                  inMode: NSDefaultRunLoopMode
                                  dequeue: YES];
                                 
      	if(event == nil)
        { 
        	break;
         }

      	[self sendEvent: event];
      	if(![self isRunning])
        {
         	break;
        }
      	[*pool release];
      	*pool = [[NSAutoreleasePool alloc] init];
   	}
}
 
- (void)run
{
   	NSAutoreleasePool *  pool = [[NSAutoreleasePool alloc] init];
   	NSRunLoop *          runLoop = [[NSRunLoop currentRunLoop] retain];
   
   	[self finishLaunching];
   	EnableVisibilityUpdates();

   	_running = 1;
   
   	while([self isRunning]) 
   	{
		[self _runMainLoopUntilDate: _distantPast autoreleasePool: &pool];
      
      	[pool drain];
      	pool = [[NSAutoreleasePool alloc] init];
   }

   [runLoop release];
   [pool drain];
}
 
- (void)applicationWillFinishLaunching: (NSNotification *)notification
{
}
 
- (void)applicationWillHide:(NSNotification *)notification
{
}
 
- (void)applicationDidHide: (NSNotification *)notification
{
}
 
- (void)applicationWillTerminate: (NSNotification *)notification
{
}

 
@end

