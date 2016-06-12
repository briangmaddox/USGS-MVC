
prefix		=	/home/bmaddox
exec_prefix	=	${prefix}
host_os		=	linux
srcdir		=	.
top_srcdir	=	.
gen_depend	=	no
enable_debug	=	no
enable_purify	=	no

# Where to find includes for libraries that mvc depends on.
INCPATHS = -I$(prefix)/include

# Where to install mvc's include files.
INCDEST = $(prefix)/include/mvc

# Where to install mvc's library.
LIBDEST = $(prefix)/lib

ifeq ($(enable_debug),yes)
DEBUG = -g
else
DEBUG = -O
endif

ifeq ($(enable_purify),yes)
PURIFY = purify
else
PURIFY =
endif

CC=$(PURIFY) gcc
CXX=$(PURIFY) g++
CXXFLAGS= $(DEBUG) $(INCPATHS)

INSTALLFILE = $(srcdir)/config/install-sh -c
INSTALLDIR  = $(srcdir)/config/install-sh -d

SRCS=   ColorManager.cc \
	Component.cc \
	Component2D.cc \
	Controller.cc \
	Debug.cc \
	DisplayDevice.cc \
	FileDisplayDevice.cc \
	FileView2D.cc \
	Global.cc \
	InputDevice.cc \
	LinkedList.cc \
	Model2D.cc \
	MVCUtils.cc \
	MVC.cc \
	Projection2D.cc \
	RectProj2D.cc \
	SelectController.cc \
	TestController.cc \
	View2D.cc \
	XDisplayDevice.cc \
	XPsuedoColorDisplayDevice.cc \
	XTrueColorDisplayDevice.cc \
	XView2D.cc \
	XMultiView2D.cc \
	ZoomController.cc

OBJS=$(SRCS:.cc=.o)

all: libmvc.a installlib installinc
	@echo "Done."

libmvc.a: $(OBJS)
	ar ru libmvc.a $(OBJS)

# Preserve the time stamp on the include files.
installinc: 
	@echo "Installing includes"
	@test -d $(INCDEST) || $(INSTALLDIR) $(INCDEST)
	@tar cf /tmp/mvc.tar *.h ; \
	cd $(INCDEST); tar xf /tmp/mvc.tar ; \
	rm -rf /tmp/mvc.tar

installlib:
	@echo "Installing library"
	@test -d $(LIBDEST) || $(INSTALLDIR) $(LIBDEST)
	@cp libmvc.a $(LIBDEST)

clean::
	rm -f $(OBJS) *.a core

realclean: 
	rm -rf *.d config.cache config.status config.log

ifeq ($(gen_depend),yes)
# Automatic generation of dependencies
%.d: %.cc
	@echo "Regenerating dependencies for $<";$(SHELL) -ec '$(CC) \
	$(INCPATHS) -MM $(CPPFLAGS) $< | sed '\''s/$*.o/& $@/g'\'' > $@'


include $(SRCS:.cc=.d)

endif


