# Android build of xmp-lite for SDL_mixer

LOCAL_PATH	:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := xmp
LOCAL_CFLAGS    := -O3 -Wall -DLIBXMP_CORE_PLAYER
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_SRC_FILES := \
    src/control.c \
    src/dataio.c \
    src/effects.c \
    src/filter.c \
    src/filetype.c \
    src/format.c \
    src/hio.c \
    src/lfo.c \
    src/load.c \
    src/load_helpers.c \
    src/memio.c \
    src/misc.c \
    src/mix_all.c \
    src/mixer.c \
    src/period.c \
    src/player.c \
    src/read_event.c \
    src/scan.c \
    src/smix.c \
    src/virtual.c \
    src/loaders/common.c \
    src/loaders/itsex.c \
    src/loaders/sample.c \
    src/loaders/it_load.c \
    src/loaders/mod_load.c \
    src/loaders/s3m_load.c \
    src/loaders/xm_load.c \

include $(BUILD_STATIC_LIBRARY)
