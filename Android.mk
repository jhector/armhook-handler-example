LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	handler.c

LOCAL_C_INCLUDES += \
	$(ARMHOOK_ROOT_PATH)/core/helper \

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := libhandler
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	target.c

LOCAL_C_INCLUDES += \
	$(ARMHOOK_ROOT_PATH)/core/helper \

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := example_target
include $(BUILD_EXECUTABLE)
