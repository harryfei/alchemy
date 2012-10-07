# installation targets
prefix=/usr/local
includedir=${prefix}/include
exec_prefix=${prefix}
libdir=${exec_prefix}/lib
mandir=${prefix}/man
docdir=./html/unit++
#various compilers.
CXX=g++
CXXFLAGS=-g -O2
# for those that have doc++, otherwise get it
DOC=doc++
#Qt related stuff
QT_LIBDIR =
QT_INCDIR =
MOC =
GUI_OBJS =
GUI_DOCSRC =

# Below here should not need modification
TARGETLIB=libunit++.a
TARGETHEADERS=unit++.h optmap.h gui.h guitester.h main.h tester.h
# substituted into GUI_OBJS by autoconf, if GUI is enabled
gui_objs = gui.o guitester.o moc_gui.o moc_guitester.o
gui_docsrc = gui.h guitester.h
OBJS=unit++.o tester.o main.o optmap.o $(GUI_OBJS)
#the files with doc information
DOCSRC=$(TARGETHEADERS) main.h tester.h $(GUI_DOCSRC)
DOCOPTS=-d $(docdir)
TSTOBJS=Test_unit++.o Test_optmap.o Test_gui.o
TSTLIBS=-L. -lunit++

.SUFFIXES: .cc

.cc.o:
	$(CXX) -D__UNITPP -c $(CXXFLAGS) $(CPPFLAGS)  -DPACKAGE_NAME=\"FULL-PACKAGE-NAME\" -DPACKAGE_TARNAME=\"full-package-name\" -DPACKAGE_VERSION=\"VERSION\" -DPACKAGE_STRING=\"FULL-PACKAGE-NAME\ VERSION\" -DPACKAGE_BUGREPORT=\"BUG-REPORT-ADDRESS\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_SSTREAM=1  -o $@ $<

all: $(TARGETLIB) unit++

$(TARGETLIB): $(OBJS)
	ar r $@ $(OBJS)

install: $(TARGETLIB) $(TARGETHEADERS)
	[ -d $(libdir) ] || mkdir -p $(libdir)
	[ -d $(includedir)/unit++ ] || mkdir -p $(includedir)/unit++
	[ -d $(mandir)/man1 ] || mkdir -p $(mandir)/man1
	[ -d $(mandir)/man3 ] || mkdir -p $(mandir)/man3
	cp $(TARGETLIB) $(libdir)
	cp $(TARGETHEADERS) $(includedir)/unit++
	cp unit++-compat.h $(includedir)/unit++.h
	cp optmap-compat.h $(includedir)/optmap.h
	cp unit++.1 $(mandir)/man1
	cp unit++.3 $(mandir)/man3

doc: $(DOCSRC)
	[ -d $(docdir) ] || mkdir -p $(docdir)
	doc++ $(DOCOPTS) $(DOCSRC)

unit++: $(TSTOBJS) $(TARGETLIB)
	$(CXX) -o $@ $(TSTOBJS) $(TSTLIBS)

moc_gui.cc: gui.h
	$(MOC) $< -o $@
moc_guitester.cc: guitester.h
	$(MOC) $< -o $@
clean:
	rm -f $(OBJS) $(TSTOBJS)

clobber: clean
	rm -f $(TARGETLIB) unit++

Test_optmap.o: Test_optmap.cc unit++.h optmap.h
Test_unit++.o: Test_unit++.cc unit++.h optmap.h tester.h main.h
Test_gui.o: Test_gui.cc
gui.o: gui.cc gui.h unit++.h optmap.h
guitester.o: guitester.cc
main.o: main.cc main.h tester.h unit++.h optmap.h
optmap.o: optmap.cc optmap.h
tester.o: tester.cc tester.h unit++.h optmap.h
unit++.o: unit++.cc unit++.h optmap.h
