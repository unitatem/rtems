
rtems_tests_PROGRAMS = blink
blink_SOURCES = init.c

include $(RTEMS_ROOT)/make/custom/@RTEMS_BSP@.cfg
include $(top_srcdir)/../automake/compile.am
include $(top_srcdir)/../automake/leaf.am


LINK_OBJS = $(blink_OBJECTS)
LINK_LIBS = $(blink_LDLIBS)

blink$(EXEEXT): $(blink_OBJECTS) $(blink_DEPENDENCIES)
	@rm -f blink$(EXEEXT)
	$(make-exe)

include $(top_srcdir)/../automake/local.am

all: blink$(EXEEXT)
	@rm -f blink.bin
	arm-rtems4.11-objcopy -O binary blink.exe blink.bin

install:
	st-flash write blink.bin 0x8000000
