
rtems_tests_PROGRAMS = blink
blink_SOURCES = init.c

# dist_rtems_tests_DATA = hello.scn
# dist_rtems_tests_DATA += hello.doc

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am


LINK_OBJS = $(blink_OBJECTS)
LINK_LIBS = $(blink_LDLIBS)

blink$(EXEEXT): $(blink_OBJECTS) $(blink_DEPENDENCIES)
	@rm -f blink$(EXEEXT)
	@rm -f blink.bin
	$(make-exe)

include $(top_srcdir)/../automake/local.am
