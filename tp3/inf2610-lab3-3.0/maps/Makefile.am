bin_PROGRAMS = segfault thread
EXTRA_DIST = pagesaver.h pagesaver.c

segfault_SOURCES = segfault.c
thread_SOURCES = thread.c

nodist_segfault_SOURCES = pagesaver.h pagesaver.c
segfault.$(OBJEXT): pagesaver.h pagesaver.c

nodist_thread_SOURCES = pagesaver.h pagesaver.c
thread.$(OBJEXT): pagesaver.h pagesaver.c