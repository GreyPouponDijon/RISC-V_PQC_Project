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

vpath %.S . $(TOP) $(CM33_USER_C_MODULES)
$(CM33_BUILD)/%.o: %.S
	$(ECHO) "CC $<"
	$(Q)$(CM33_CC) $(CM33_CFLAGS) -c -o $@ $<

vpath %.s . $(TOP) $(CM33_USER_C_MODULES)
$(CM33_BUILD)/%.o: %.s
	$(ECHO) "AS $<"
	$(Q)$(CM33_AS) -o $@ $<

define cm33_compile_c
$(ECHO) "CC $<"
$(Q)$(CM33_CC) $(CM33_CFLAGS) -c -MD -o $@ $<
@# The following fixes the dependency file.
@# See http://make.paulandlesley.org/autodep.html for details.
@# Regex adjusted from the above to play better with Windows paths, etc.
@$(CP) $(@:.o=.d) $(@:.o=.P); \
  $(SED) -e 's/#.*//' -e 's/^.*:  *//' -e 's/ *\\$$//' \
      -e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.d) >> $(@:.o=.P); \
  $(RM) -f $(@:.o=.d)
endef

define cm33_compile_cpp
$(ECHO) "CXX $<"
$(Q)$(CM33_CXX) $(CM33_CXXFLAGS) -c -MD -o $@ $<
@# The following fixes the dependency file.
@# See http://make.paulandlesley.org/autodep.html for details.
@# Regex adjusted from the above to play better with Windows paths, etc.
@$(CP) $(@:.o=.d) $(@:.o=.P); \
  $(SED) -e 's/#.*//' -e 's/^.*:  *//' -e 's/ *\\$$//' \
      -e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.d) >> $(@:.o=.P); \
  $(RM) -f $(@:.o=.d)
endef
vpath %.c . $(TOP) $(CM33_USER_C_MODULES)
$(CM33_BUILD)/%.o: %.c
	$(call cm33_compile_c)

vpath %.cc . $(TOP) $(CM33_OBJ_CPP)
$(CM33_BUILD)/%.o: %.cc
	$(call cm33_compile_cpp)

# $(sort $(var)) removes duplicates
#
# The net effect of this, is it causes the objects to depend on the
# object directories (but only for existence), and the object directories
# will be created if they don't exist.
CM33_OBJ_DIRS = $(sort $(dir $(CM33_OBJ))) 
$(CM33_OBJ): | $(CM33_OBJ_DIRS)
$(CM33_OBJ_DIRS):
	$(MKDIR) -p $@

CM33_OBJ_CPP_DIRS = $(sort $(dir $(CM33_OBJ_CPP)))
$(CM33_OBJ_CPP): | $(CM33_OBJ_CPP_DIRS)
$(CM33_OBJ_CPP_DIRS):
	$(MKDIR) -p $@

cm33_clean:
	$(RM) -rf $(CM33_BUILD)

.PHONY: cm33_clean
