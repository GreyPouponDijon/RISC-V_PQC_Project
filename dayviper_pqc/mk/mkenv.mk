# The MIT License (MIT)
# 
# Copyright (c) 2013-2019 Damien P. George
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

ifneq ($(lastword a b),b)
$(error These Makefiles require make 3.81 or newer)
endif

# Set TOP to be the path to get from the current directory (where make was
# invoked) to the top of the tree. $(lastword $(MAKEFILE_LIST)) returns
# the name of this makefile relative to where make was invoked.
#
# We assume that this file is in the mk directory so we use $(dir ) twice
# to get to the top of the tree.

THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))
TOP := $(patsubst %mk/mkenv.mk,%,$(THIS_MAKEFILE))

# Turn on increased build verbosity by defining BUILD_VERBOSE in your main
# Makefile or in your environment. You can also use V=1 on the make command
# line.

ifeq ("$(origin V)", "command line")
BUILD_VERBOSE=$(V)
endif
ifndef BUILD_VERBOSE
BUILD_VERBOSE = 0
endif
ifeq ($(BUILD_VERBOSE),0)
Q = @
else
Q =
endif
# Since this is a new feature, advertise it
ifeq ($(BUILD_VERBOSE),0)
$(info Use make V=1 or set BUILD_VERBOSE in your environment to increase build verbosity.)
endif

# default settings; can be overridden in main Makefile

BUILD ?= build

RM = rm
ECHO = @echo
CP = cp
MKDIR = mkdir
SED = sed
CAT = cat
TOUCH = touch
PYTHON = python3

VPR_AS = $(VPR_CROSS_COMPILE)as
VPR_CC = $(VPR_CROSS_COMPILE)gcc
VPR_CXX = $(VPR_CROSS_COMPILE)g++
VPR_GDB = $(VPR_CROSS_COMPILE)gdb
VPR_LD = $(VPR_CROSS_COMPILE)ld
VPR_OBJCOPY = $(VPR_CROSS_COMPILE)objcopy
VPR_OBJDUMP = $(VPR_CROSS_COMPILE)objdump
VPR_NM = $(VPR_CROSS_COMPILE)nm
VPR_SIZE = $(VPR_CROSS_COMPILE)size
VPR_STRIP = $(VPR_CROSS_COMPILE)strip
VPR_AR = $(VPR_CROSS_COMPILE)ar

CM33_AS = $(CM33_CROSS_COMPILE)as
CM33_CC = $(CM33_CROSS_COMPILE)gcc
CM33_CXX = $(CM33_CROSS_COMPILE)g++
CM33_GDB = $(CM33_CROSS_COMPILE)gdb
CM33_LD = $(CM33_CROSS_COMPILE)ld
CM33_OBJCOPY = $(CM33_CROSS_COMPILE)objcopy
CM33_OBJDUMP = $(CM33_CROSS_COMPILE)objdump
CM33_NM = $(CM33_CROSS_COMPILE)nm
CM33_SIZE = $(CM33_CROSS_COMPILE)size
CM33_STRIP = $(CM33_CROSS_COMPILE)strip
CM33_AR = $(CM33_CROSS_COMPILE)ar

all:
.PHONY: all

.DELETE_ON_ERROR:

MKENV_INCLUDED = 1
