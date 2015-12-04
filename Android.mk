LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
	runner.c

LOCAL_C_INCLUDES += \
	$(ARMHOOK_ROOT_PATH)/core/helper \

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := librunner
include $(BUILD_SHARED_LIBRARY)
