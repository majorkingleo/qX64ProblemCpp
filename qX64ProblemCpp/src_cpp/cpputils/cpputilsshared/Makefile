EXTENSION=
HOST=LINUX
HFILES=backtrace.h blockupdate.h cppdir.h cpp_util.h cpputils.h cpp_utils.h format.h iterator.h jvector.h leoini.h logtool2.h map_utils.h range.h ref.h report_exception.h string_utils.h vec_utils.h xml.h zvector.h
CFILES=backtrace.cc blockupdate.cc cppdir.cc cpp_util.cc format.cc leoini.cc logtool2.cc string_utils.cc vec_utils.cc xml.cc
OFILES= .libs/backtrace.o .libs/blockupdate.o .libs/cppdir.o .libs/cpp_util.o .libs/format.o .libs/leoini.o .libs/logtool2.o .libs/string_utils.o .libs/vec_utils.o .libs/xml.o
VERSION=0.1
CXX=g++
CXXDEPS=g++
CXXFLAGS= -fstack-protector  -pthread  -O3 -Wall -Woverloaded-virtual -Wshadow  -I/data2/home/martin/workspace/qX64Problem/qX64ProblemCpp/src_cpp/. -I/data2/home/martin/workspace/qX64Problem/qX64ProblemCpp/src_cpp/tools -I/data2/home/martin/workspace/qX64Problem/qX64ProblemCpp/src_cpp/cpputils/cpputilsshared -DLINUX -DVERSION='"0.1"' -DNOWAMAS
LDFLAGS=  -L. -Ltools -Lcpputils/cpputilsshared
RM=rm -f
SHELL=/usr/bin/env bash


EXE=libcpputilsshared.a

all: $(EXE)

libcpputilsshared.a: $(OFILES)
	ar r libcpputilsshared.a $(OFILES)




.libs/%.o: %.cc .libs/.objdir
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	$(RM) $(OFILES) $(EXE) core .dependencies
	if test -d .libs ; then rm -rf .libs ; fi


.libs/.objdir:
	if ! test -d .libs ; then mkdir .libs ; fi
	touch .libs/.objdir

.libs/%.d : %.cc .libs/.objdir
	@$(CXXDEPS) $(CXXFLAGS) -MF"$@" -MM -MP -MT"$@" -MT".libs/$(<:.cc=.o)" "$<"

include  .libs/backtrace.d .libs/blockupdate.d .libs/cppdir.d .libs/cpp_util.d .libs/format.d .libs/leoini.d .libs/logtool2.d .libs/string_utils.d .libs/vec_utils.d .libs/xml.d

