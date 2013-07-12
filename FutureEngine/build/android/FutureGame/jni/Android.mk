LOCAL_PATH := $(call my-dir)/../../../../

include $(CLEAR_VARS)
LOCAL_MODULE := FutureGame
LOCAL_SRC_FILES := 	src/game/system/system.cpp \
					src/game/system/platform/system_android.cpp

LOCAL_CFLAGS := -D_ANDROID=1 -D_DEBUG=1
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include/
LOCAL_LDLIBS := -lm -landroid
LOCAL_STATIC_LIBRARIES := android_native_app_glue FutureCore
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include/
LOCAL_EXPORT_LDLIBS := -lm -landroid

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := FakeFutureGame
LOCAL_STATIC_LIBRARIES := FutureGame
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)