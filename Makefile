ARCHS = arm64e
TARGET = iphone:clang:15.0:15.0
INSTALL_TARGET_PROCESSES = Filza

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = SandboxExt

SandboxExt_FILES = Tweak.x gulu_poc.c
SandboxExt_CFLAGS = -fobjc-arc
SandboxExt_FRAMEWORKS = XPC Foundation

include $(THEOS_MAKE_PATH)/tweak.mk
