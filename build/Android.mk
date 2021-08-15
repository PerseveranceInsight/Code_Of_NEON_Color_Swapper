LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := neon_col_swap

LOCAL_CFLAGS += -D__DEBUG__
LOCAL_CFLAGS += -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-label -Wno-return-type
ifeq ($(EN_DEBUG_SYM), true)
LOCAL_CFLAGS += -g -ggdb
endif

PROJECT_SRC = $(LOCAL_PATH)/../src
PROJECT_INC = $(LOCAL_PATH)/../inc
PROJECT_UTIL_INC = $(LOCAL_PATH)/../util/inc
PROJECT_UTIL_SRC = $(LOCAL_PATH)/../util/src

LOCAL_C_INCLUDES += $(PROJECT_INC) \
					$(PROJECT_UTIL_INC) \

LOCAL_SRC_FILES += $(PROJECT_SRC)/neon_col_swap_main.c \
				   $(PROJECT_SRC)/neon_col_swap.c \
				   $(PROJECT_UTIL_SRC)/android_arm_util.c 

LOCAL_LDLIBS := -lm -llog
LOCAL_LDFLAGS := -nodefaultlibs -lc -lm -ldl

include $(BUILD_EXECUTABLE)
