if GNU_GAMA_LOCAL_TEST_SQLITE_READER
SQLITE_READER_PROG = check_xml_coordinates sqlite_init_db
endif

check_PROGRAMS = check_algorithms check_equivalents check_html check_version \
        check_externs check_xml_results check_xml_xml $(SQLITE_READER_PROG)

check_algorithms_SOURCES  = check_algorithms.cpp \
                            check_xyz.h check_xyz.cpp
check_algorithms_LDADD    = $(top_builddir)/lib/libgama.a
check_algorithms_CPPFLAGS = -I $(top_srcdir)/lib

check_equivalents_SOURCES  = check_equivalents.cpp \
                             check_xyz.h check_xyz.cpp
check_equivalents_LDADD    = $(top_builddir)/lib/libgama.a
check_equivalents_CPPFLAGS = -I $(top_srcdir)/lib

check_html_SOURCES  = check_html.cpp compare_xml_adjustment.h \
                      compare_xml_adjustment.cpp
check_html_LDADD    = $(top_builddir)/lib/libgama.a
check_html_CPPFLAGS = -I $(top_srcdir)/lib

check_version_SOURCES  = check_version.cpp
check_version_LDADD    = $(top_builddir)/lib/libgama.a
check_version_CPPFLAGS = -I $(top_srcdir)/lib

check_xml_results_SOURCES  = check_xml_results.cpp \
                             check_xyz.h check_xyz.cpp
check_xml_results_LDADD    = $(top_builddir)/lib/libgama.a
check_xml_results_CPPFLAGS = -I $(top_srcdir)/lib

check_xml_xml_SOURCES  = check_xml_xml.cpp compare_xml_adjustment.h \
                         compare_xml_adjustment.cpp
check_xml_xml_LDADD    = $(top_builddir)/lib/libgama.a
check_xml_xml_CPPFLAGS = -I $(top_srcdir)/lib

check_externs_SOURCES  = check_externs.cpp
check_externs_LDADD    = $(top_builddir)/lib/libgama.a
check_externs_CPPFLAGS = -I $(top_srcdir)/lib

if GNU_GAMA_LOCAL_TEST_SQLITE_READER
check_xml_coordinates_SOURCES  = check_xml_coordinates.cpp
check_xml_coordinates_LDADD    = $(top_builddir)/lib/libgama.a
check_xml_coordinates_CPPFLAGS = -I $(top_srcdir)/lib

sqlite_init_db_SOURCES  = sqlite_init_db.cpp
endif
