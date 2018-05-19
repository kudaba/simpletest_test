# Generated by Sharpmake -- Do not edit !
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  CXX        = g++
  AR         = ar
  OBJDIR     = ../.temp/build/debug/simpletestproject_linux_gcc
  TARGETDIR  = ../.temp/bin
  TARGET     = $(TARGETDIR)/simpletestproject_linux_gcc_debug
  DEFINES   += 
  INCLUDES  += -I../simpletest
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) -std=c++11 -g -Wall -Werror -pthread
  CXXFLAGS  += $(CFLAGS) -fexceptions -fno-rtti 
  LDFLAGS   += -pthread
  LIBS      +=  
  RESFLAGS  += $(DEFINES) $(INCLUDES)
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
  define POSTFILECMDS
  endef
endif

ifeq ($(config),release)
  CXX        = g++
  AR         = ar
  OBJDIR     = ../.temp/build/release/simpletestproject_linux_gcc
  TARGETDIR  = ../.temp/bin
  TARGET     = $(TARGETDIR)/simpletestproject_linux_gcc_release
  DEFINES   += 
  INCLUDES  += -I../simpletest
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) -std=c++11 -g -O3 -Wall -Werror -pthread
  CXXFLAGS  += $(CFLAGS) -fexceptions -fno-rtti 
  LDFLAGS   += -pthread
  LIBS      +=  
  RESFLAGS  += $(DEFINES) $(INCLUDES)
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
  define POSTFILECMDS
  endef
endif

ifeq ($(config),debug)
  OBJECTS += $(OBJDIR)/simpletest.o
  OBJECTS += $(OBJDIR)/basictests.o
  OBJECTS += $(OBJDIR)/exceptiontests.o
  OBJECTS += $(OBJDIR)/executionordertests.o
  OBJECTS += $(OBJDIR)/failtests.o
  OBJECTS += $(OBJDIR)/memorytests.o
  OBJECTS += $(OBJDIR)/threadingtests.o
  OBJECTS += $(OBJDIR)/typetostringtests.o
  OBJECTS += $(OBJDIR)/main.o

endif

ifeq ($(config),release)
  OBJECTS += $(OBJDIR)/simpletest.o
  OBJECTS += $(OBJDIR)/basictests.o
  OBJECTS += $(OBJDIR)/exceptiontests.o
  OBJECTS += $(OBJDIR)/executionordertests.o
  OBJECTS += $(OBJDIR)/failtests.o
  OBJECTS += $(OBJDIR)/memorytests.o
  OBJECTS += $(OBJDIR)/threadingtests.o
  OBJECTS += $(OBJDIR)/typetostringtests.o
  OBJECTS += $(OBJDIR)/main.o

endif

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking SimpleTestProject
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) if not exist $(subst /,\\,$(TARGETDIR)) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) if not exist $(subst /,\\,$(OBJDIR)) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning SimpleTestProject
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)
endif

$(OBJDIR)/simpletest.o: ../simpletest/simpletest.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/basictests.o: ../src/exampletests/basictests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/exceptiontests.o: ../src/exampletests/exceptiontests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/executionordertests.o: ../src/exampletests/executionordertests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/failtests.o: ../src/exampletests/failtests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/memorytests.o: ../src/exampletests/memorytests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/threadingtests.o: ../src/exampletests/threadingtests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/typetostringtests.o: ../src/exampletests/typetostringtests.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

$(OBJDIR)/main.o: ../src/main.cpp | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
	$(SILENT) $(POSTFILECMDS)

-include $(OBJECTS:%.o=%.d)
