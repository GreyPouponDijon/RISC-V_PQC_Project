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

ifneq ($(MKENV_INCLUDED),1)
# We assume that mkenv is in the same directory as this file.
THIS_MAKEFILE = $(lastword $(MAKEFILE_LIST))
include $(dir $(THIS_MAKEFILE))mkenv.mk
endif

vpath %.S . $(TOP) $(VPR_USER_C_MODULES)
$(VPR_BUILD)/%.o: %.S
	$(ECHO) "CC $<"
	$(Q)$(VPR_CC) $(VPR_CFLAGS) -c -o $@ $<

vpath %.s . $(TOP) $(VPR_USER_C_MODULES)
$(VPR_BUILD)/%.o: %.s
	$(ECHO) "AS $<"
	$(Q)$(VPR_AS) -o $@ $<

define vpr_compile_c
$(ECHO) "CC $<"
$(Q)$(VPR_CC) $(VPR_CFLAGS) -c -MD -o $@ $<
@# The following fixes the dependency file.
@# See http://make.paulandlesley.org/autodep.html for details.
@# Regex adjusted from the above to play better with Windows paths, etc.
@$(CP) $(@:.o=.d) $(@:.o=.P); \
  $(SED) -e 's/#.*//' -e 's/^.*:  *//' -e 's/ *\\$$//' \
      -e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.d) >> $(@:.o=.P); \
  $(RM) -f $(@:.o=.d)
endef

define vpr_compile_cpp
$(ECHO) "CXX $<"
$(Q)$(VPR_CXX) $(VPR_CXXFLAGS) -c -MD -o $@ $<
@# The following fixes the dependency file.
@# See http://make.paulandlesley.org/autodep.html for details.
@# Regex adjusted from the above to play better with Windows paths, etc.
@$(CP) $(@:.o=.d) $(@:.o=.P); \
  $(SED) -e 's/#.*//' -e 's/^.*:  *//' -e 's/ *\\$$//' \
      -e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.d) >> $(@:.o=.P); \
  $(RM) -f $(@:.o=.d)
endef
vpath %.c . $(TOP) $(VPR_USER_C_MODULES)
$(VPR_BUILD)/%.o: %.c
	$(call vpr_compile_c)

vpath %.cc . $(TOP) $(VPR_OBJ_CPP)
$(VPR_BUILD)/%.o: %.cc
	$(call vpr_compile_cpp)

# $(sort $(var)) removes duplicates
#
# The net effect of this, is it causes the objects to depend on the
# object directories (but only for existence), and the object directories
# will be created if they don't exist.
VPR_OBJ_DIRS = $(sort $(dir $(VPR_OBJ))) 
$(VPR_OBJ): | $(VPR_OBJ_DIRS)
$(VPR_OBJ_DIRS):
	$(MKDIR) -p $@

VPR_OBJ_CPP_DIRS = $(sort $(dir $(VPR_OBJ_CPP)))
$(VPR_OBJ_CPP): | $(VPR_OBJ_CPP_DIRS)
$(VPR_OBJ_CPP_DIRS):
	$(MKDIR) -p $@

vpr_clean:
	$(RM) -rf $(VPR_BUILD)

.PHONY: vpr_clean
