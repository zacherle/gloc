
# NLLoc function test (NLLoc_func_test)
NLLoc_func_test_ : ${BINDIR}/NLLoc_func_test
${BINDIR}/NLLoc_func_test : NLLoc_func_test.o NLLoc${PVER}.o ${OBJS1}
	${CC} NLLoc_func_test.o NLLoc${PVER}.o ${OBJS1} ${CCFLAGS} -o ${BINDIR}/NLLoc_func_test -lm
NLLoc_func_test.o : NLLoc_func_test.c NLLocLib.h GridLib.h GridMemLib.h alomax_matrix/alomax_matrix.h alomax_matrix/alomax_matrix_svd.h matrix_statistics/matrix_statistics.h
	${CC} -c ${CCFLAGS} NLLoc_func_test.c  $(OPTIONS)
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# ttime_func_test
#
OBJS11=ttime_func_test.o ${GRID_LIB_OBJS}
ttime_func_test_ : ${BINDIR}/ttime_func_test
${BINDIR}/ttime_func_test : ${OBJS11}
	${CC} ${OBJS11} ${CCFLAGS} -o ${BINDIR}/ttime_func_test -lm
ttime_func_test.o : ttime_func_test.c GridLib.h
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# mag_func_test
#
OBJS12=mag_func_test.o NLLocLib.o ${GRID_LIB_OBJS} ${NLLOC_LIB_OBJS}
mag_func_test_ : ${BINDIR}/mag_func_test
${BINDIR}/mag_func_test : ${OBJS12}
	${CC} ${OBJS12} ${CCFLAGS} -o ${BINDIR}/mag_func_test -lm
mag_func_test.o : mag_func_test.c NLLocLib.h GridLib.h
# --------------------------------------------------------------------------

