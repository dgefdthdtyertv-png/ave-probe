ARCHS = arm64
TARGET = iphone:clang:17.0:17.0
INSTALL_TARGET_PROCESSES = aveprobe
include $(THEOS)/makefiles/common.mk
APPLICATION_NAME = aveprobe
aveprobe_FILES = ave_probe.c
aveprobe_FRAMEWORKS = IOKit
include $(THEOS_MAKE_PATH)/application.mk
