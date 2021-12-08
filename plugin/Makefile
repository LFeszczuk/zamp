
CPPFLAGS=-Wall -fPIC -pedantic -std=c++17 -iquote inc -iquote ../inc
LDFLAGS=-Wall -shared
#OBJDIR=/tmp/${USER}/plugins/obj
OBJDIR=./obj




__start__: ${OBJDIR} __lines_for_space__ ../libs/libInterp4Move.so ../libs/libInterp4Rotate.so 
	@echo "  Tworzenie wtyczki zakonczone."
	@echo

${OBJDIR}:
	mkdir -p ${OBJDIR}

__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo

#-----------------------------------------------------------------------------
#
#  Wtyczka libInterp4Move.so
#

../libs/libInterp4Move.so: ${OBJDIR}/Interp4Move.o ${OBJDIR}/network_sending.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Move.so ${OBJDIR}/Interp4Move.o\
                          ${OBJDIR}/network_sending.o
	@echo
	@echo "  Wtyczka dla polecenia 'Move' zostala utworzona."
	@echo


${OBJDIR}/Interp4Move.o: src/Interp4Move.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Move.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/Interp4Move.o src/Interp4Move.cpp


#-----------------------------------------------------------------------------
#
#  Wtyczka libInterp4Rotate.so
#


../libs/libInterp4Rotate.so: ${OBJDIR}/Interp4Rotate.o ${OBJDIR}/network_sending.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Rotate.so ${OBJDIR}/Interp4Rotate.o\
                           ${OBJDIR}/network_sending.o
	@echo
	@echo "  Wtyczka dla polecenia 'Rotate' zostala utworzona."
	@echo


${OBJDIR}/Interp4Rotate.o: src/Interp4Rotate.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Rotate.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/Interp4Rotate.o src/Interp4Rotate.cpp


${OBJDIR}/network_sending.o: src/network_sending.cpp inc/network_sending.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/network_sending.o src/network_sending.cpp

#-----------------------------------------------------------------------------
#
#  Wtyczka libInterp4set.so
#


../libs/libInterp4Set.so: ${OBJDIR}/Interp4Set.o ${OBJDIR}/network_sending.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Set.so ${OBJDIR}/Interp4Set.o\
                           ${OBJDIR}/network_sending.o
	@echo
	@echo "  Wtyczka dla polecenia 'set' zostala utworzona."
	@echo


${OBJDIR}/Interp4Set.o: src/Interp4Set.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Set.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/Interp4Set.o src/Interp4Set.cpp


${OBJDIR}/network_sending.o: src/network_sending.cpp inc/network_sending.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/network_sending.o src/network_sending.cpp


	#-----------------------------------------------------------------------------
#
#  Wtyczka libInterp4Pause.so
#


../libs/libInterp4Pause.so: ${OBJDIR}/Interp4Pause.o ${OBJDIR}/network_sending.o
	g++ ${LDFLAGS} -o ../libs/libInterp4Pause.so ${OBJDIR}/Interp4Pause.o\
                           ${OBJDIR}/network_sending.o
	@echo
	@echo "  Wtyczka dla polecenia 'Pause' zostala utworzona."
	@echo


${OBJDIR}/Interp4Pause.o: src/Interp4Pause.cpp ../inc/Interp4Command.hh\
                        inc/Interp4Pause.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/Interp4Pause.o src/Interp4Pause.cpp


${OBJDIR}/network_sending.o: src/network_sending.cpp inc/network_sending.hh 
	g++ -c ${CPPFLAGS} -o ${OBJDIR}/network_sending.o src/network_sending.cpp


clean:
	rm -f ${OBJDIR}/*

cleanall: clean
	find . -name \*~ -print -exec rm {} \;
