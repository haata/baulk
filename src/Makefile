# Original Version (more of an idea at this point) from Awesome WM
builddir=.build-$(shell hostname)-$(shell gcc -dumpmachine)-$(shell gcc -dumpversion)

ifeq (,$(VERBOSE))
    MAKEFLAGS:=$(MAKEFLAGS)s
    ECHO=echo
    HEAD=head
else
    ECHO=@:
    HEAD=@:
endif


all:
	# First Run
	test -e ${builddir}/Makefile || \
		$(HEAD) -n 37 CMakeLists.txt 
	# After CMake Generation
	! test -e ${builddir}/Makefile || \
		$(MAKE) build

build: cmake
	$(ECHO) "Building…"
	$(MAKE) -C ${builddir}

cmake:
	$(ECHO) "Checking CMake…"
	mkdir -p ${builddir}
	test -e $(builddir)/Makefile || \
	       ( cd $(builddir) && cmake `cat ../.cmakeVars` .. )

#| Tag Targets

tags:
	git ls-files | xargs ctags

#| Installation Targets

install:
	$(ECHO) "Installing…"
	$(MAKE) -C ${builddir} install

#| Clean Targets

distclean:
	$(ECHO) -n "Cleaning up build directory…"
	$(RM) -r ${builddir} $(TARGETS)
	$(ECHO) " done"

cmakeclean: distclean
	$(ECHO) -n "Clearing variable list…"
	$(RM) .cmakeVars
	$(ECHO) " done"

clean:
	$(ECHO) "Cleaning…"
	$(MAKE) -C ${builddir} clean

#| CMake Flag Targets

Build%: cmakeclean
	$(ECHO) " -D$@=true" >> .cmakeVars
	$(ECHO) $#

cmakeflags:
	cat .cmakeVars

.PHONY: build install clean all

