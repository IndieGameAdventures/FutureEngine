LOCAL_PATH := $(call my-dir)/../../../..

include $(CLEAR_VARS)
LOCAL_MODULE := FutureCore
LOCAL_SRC_FILES := 	src/core/debug/log.cpp \
		  			src/core/debug/assert.cpp \
		  			src/core/debug/debug.cpp \
		  			src/core/memory/allocators/heapallocator.cpp \
		  			src/core/memory/allocators/poolallocator.cpp \
		  			src/core/memory/allocators/mallocallocator.cpp \
		  			src/core/memory/allocators/stackallocator.cpp \
		  			src/core/memory/tracker/memorytracker.cpp \
		  			src/core/memory/memory.cpp \
		  			src/core/object/managedobject.cpp \
		  			src/core/thread/criticalsection/criticalsection.cpp \
		 			src/core/thread/pool/job.cpp \
		  			src/core/thread/pool/threadpool.cpp \
		  			src/core/thread/thread/thread.cpp \
		  			src/core/thread/thread/null_thread.cpp \
		  			src/core/thread/thread/posix_thread.cpp \
		  			src/core/thread/thread/workerthread.cpp \
		  			src/core/utils/timer.cpp \
		  			src/core/utils/string.cpp \

LOCAL_CFLAGS := -D_ANDROID=1
LOCAL_CFLAGS := -D_DEBUG=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/
LOCAL_LDLIBS := -llog
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/
LOCAL_EXPORT_LDLIBS := -llog
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := FakeFutureCore
LOCAL_STATIC_LIBRARIES := FutureCore
include $(BUILD_SHARED_LIBRARY)
