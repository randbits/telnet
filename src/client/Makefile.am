
AM_CPPFLAGS = \
	$(NULL)

AM_CFLAGS = \
	$(NULL)


bin_PROGRAMS = telnet

telnet_SOURCES = \
	main.c\
	$(NULL)

telnet_CPPFLAGS = \
	-I$(top_srcdir)/include
	$(NULL)

telnet_LDADD= \
	$(top_builddir)/lib/libtelnet.la \
	$(NULL)

