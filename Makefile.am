# Makefile.am for Spoinkstore

# Source files
AM_CPPFLAGS = $(GTK_CFLAGS) $(JSON_CFLAGS)
bin_PROGRAMS = spoinkstore
spoinkstore_SOURCES = main.cpp  # Add your source files here

# Linking flags
spoinkstore_LDADD = $(GTK_LIBS) $(JSON_LIBS)

# Install and uninstall targets
install:
    install -D -m 755 spoinkstore $(DESTDIR)/usr/local/bin/spoinkstore

uninstall:
    rm -f $(DESTDIR)/usr/local/bin/spoinkstore

# Clean target
clean:
    rm -f spoinkstore
