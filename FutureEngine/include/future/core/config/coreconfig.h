/*
 *	Copyright 2013 by Lucas Stufflebeam mailto:info@indiegameadventures.com
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

#ifndef FUTURE_CORE_CONFIG_H
#define FUTURE_CORE_CONFIG_H

// Forward declares
class IFutureOStream;
class IFutureIStream;

/*!
 *	\brief		Static class containing runtime configurations for the core library
 *
 *	\details 	These settings are read in from the system data file when the application first starts up. Some
 *				of these settings can be changed at runtime and others cannot. Be aware that changing these at
 *				runtime may cause undefined behavior. It is recommended that any systems using the changed options
 *				be restarted after that change is made. Settings should be set at compile time using the resource
 *				manager tool.
 *	
 *	\author		Lucas Stufflebeam
 *	\version 	1.0
 *	\date		August 2013
 */
class FutureCoreConfig
{
public:
	//! Allows use of the profiler to gain event time and function call information
	static const bool			ProfilingEnabled() {return m_profileEnabled; }

	//! If true, then extra steps will taken with each memory allocation to track it, allowing for profiling information and leak detection
	static const bool			TrackMemory() {return m_trackMemory; }
	/* If true, the memory system will collect usefull statistics about the program memory.
	 * Profiles things like: allocation time, allocations by size, fragmenting information, allocation lifetime, etc...
	 * Requires TrackMemory and ProfileEnabled to be true.
	 */
	static const bool			ProfileMemory() {return m_profileMemory && m_profileEnabled && m_trackMemory; }

	//! If true then any allocations that would push the current memory use past InternalMemoryLimit will fail
	static const bool			ForceInternalMemoryLimit() {return m_forceMemoryLimit; }
	//!	The maximum amount of memory the memory system can allocate. This does not include constant expressions or other memory not allocated using the memory system
	static const u32			InternalMemoryLimit() {return m_memoryLimit; }
	//! The default size of the memory heap, if this is 0 then no heap will be created and all allocations will be passed to malloc
	static const u32			DefaultMemoryHeapSize() {return m_heapSize; }
	//! The number of default pool allocators to create
	static const u32			DefaultMemoryPoolAllcoators() {return m_numPools; }
	//! An array of size DefaultMemoryPoolAllcoators() holding the block size for each pool allocator
	static const u32 *			DefaultMemoryPoolAllocatorBlockSizes() {return m_poolBlockSizes; }
	//! An array of size DefaultMemoryPoolAllocators() holding the number of blocks each pool allocator should create
	static const u32 *			DefaultMemoryPoolAllocatorPoolSizes() {return m_poolNumBlocks; }

	/* Determines is multithreading is supported.
	 * If disabled, FutureThread will throw errors if a second thread is created. All free thread checks are 
	 * also removed. Race conditions, memory curruption and lots of other bad things will happen if used incorrectly.
	 * Greatly increases performance if only using one thread but should always be enabled if using more than one.
	 * This cannot be set at runtime but must set by using the multithreaded or singlethreaded versions of the libraries.
	 */
	static const bool			MultithreadingEnabled() {return m_multithreaded; }
	/* If true, the thread pool will keep track of the amount of time spent on specific tasks
	 * This includes tracking time spent handling internal operations on the main thread, wait times for jobs, thread idle time, and job execution time.
	 * Requires ProfilingEnabled to be true.
	 */
	static const bool			ProfileThreadPool() {return m_profileThreadPool && m_profileEnabled; }
	//! The number of default threads the thread pool should create. This will return 0 in a single threaded environment.
	static const u8				ThreadPoolThreads() {return m_trackMemory; }

	/* 	This option controls the entire program flow by determining how threads should operate.
	 *	If true, then each system will run on a seperate thread. Each system will essentially be single threaded and operate as it's
	 *	own seperate program but will syncronize it's resources with other systems during the PreSync and PostSync phases. If this is
	 *	false then all system phases will be executed syncronously on the main thread. This will free up thread resources to allow
	 *	each system to make full use of the ThreadPool and create it's own threads. This also simplifies the Pre and Post Sync functions
	 *	as each system can directly modify the scene graph without fear of the information being overwritten by other systems or breaking
	 *	things. Both modes have pros and cons. True has potential to be faster but causes a one frame delay between as systems, increases
	 *	memory use, and makes the programmers job much harder. False uses much less memory and allows systems to interact with eachother
	 *	directly but is potentially slower and forces each system to be multithreaded instead of single threaded.  This is currently
	 *	always false as it is not supported yet. Requires MultithreadingEnabled to be true.
	 */
	static const bool			AsynchronousSystemUpdate() {return false/*m_asyncSystems*/; }
	//! If true, then a set of default systems are applied to the application at start up. If false, all systems must be supplied manually
	static const bool			AutoPopulateDefaultSystems() {return m_autoPopulate; }


	/* Determines is immediate event dispatching is enabled.
	 * If this is true then events will be dispatched to listeners. Events are dispatched immediately to all valid listeners.
	 * This is the recommended way of handling events.
	 */
	static const bool			EventDispatchingEnabled() {return m_eventDispatching; }
	/* Determines is event polling is enabled.
	 * Both this and FUTURE_ENABLE_EVENT_DISPATCHING can be true allowing for both dispatching and polling, each has it's own
	 * benifit. Polling requires the notification center or the event dispatcher to be asked if it has an event each frame. 
	 * Events will be listed as available on the frame following when they actually happened. This will ensure that all pollers
	 * have a chance to poll for the event. This also means that events will be received one frame after they occured. The
	 * dispatcher will hold on to the event until the PostSync phase of the frame following the creation of the event.
	 */ 
	static const bool			EventPollingEnabled() {return m_eventPolling; }
	/* Determines is dispatched events should be fires asynchronously.
	 * If this is true the event dispatchers will create a ThreadPool Job for the event to dispatch it on the a different thread
	 * than it was created on. This is usually much faster than syncronous dispatching as it does not block the current thread
	 * until dispatching has finished. But it does create more work for the programmer as it is possible for multiple events to
	 * be recieved at the time, including conflicting events. Events may also be recieved in the middle of crucial functions
	 * and create potential problems. It's much faster though. This requires MultithreadingEnabled and EventDispatchingEnabled.
	 */
	static const bool			EventAsynchronousDispatchingEnabled() {return m_eventAsync; }

	//! Allows Enabling/Disabling of Event Dispatching at runtime
	static void					SetEventDispatchingEnabled(bool enabled) { m_eventDispatching = enabled; }
	//! Allows Enabling/Disabling of Event Polling at runtime
	static void					SetEventPollingEnabled(bool enabled) { m_eventPolling = enabled; }
	//! Allows Enabling/Disabling of Asynchronous Event Dispatching at runtime
	static void					SetEventAsynchronousDispatchingEnabled(bool enabled) { m_eventAsync = enabled; }

	//! Returns the current default language used to load resources when a language is not specified.
	static const Language		ResourceDefaultLanguage() { return m_language; }
	//! Sets the default language to use when loading resources.
	static void					SetResourceDefaultLanguage(Language language) { m_language = language; }

	//! Stores resource names and allows access to names by functions in the resource manager: Default - True for debug and profile, false for release
	static const bool			StoreResourceNames() { return m_storeResourceNames; }
	//! Allows for accessing resources by name instead of only by id. This is not recommended as it is expensive but here just in case
	static const bool			SearchResourceNames() { return m_searchResourceNames; }

#ifndef FUTURE_TOOL
protected:
	friend class FutureResourceManager;
#endif

	//! Loads the configuration options from the stream
	static bool	LoadConfig(IFutureIStream * stream);
	//! Dumps the configuration options to the stream
	static bool	DumpConfig(IFutureOStream * stream);

	static bool		m_profileEnabled;
	static bool		m_trackMemory;
	static bool		m_profileMemory;
	static bool		m_forceMemoryLimit;
	static u32		m_memoryLimit;
	static u32		m_heapSize;
	static u32		m_numPools;
	static u32 *	m_poolBlockSizes;
	static u32 *	m_poolNumBlocks;
	static bool 	m_multithreaded;
	static bool		m_profileThreadPool;
	static u8		m_defaultThreads;
	static bool		m_asyncSystems;
	static bool		m_autoPopulate;
	static bool		m_eventDispatching;
	static bool		m_eventPolling;
	static bool		m_eventAsync;
	static Language	m_language;
	static bool		m_storeResourceNames;
	static bool		m_searchResourceNames;
};


#endif
