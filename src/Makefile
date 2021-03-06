# Makefile for NonLinLoc software package
#
# Invocation:
#     Solaris: make all
#     Linux:   make -R all


#  IMPORTANT: change here to set the directory for binary executable files
ifdef MYBIN
BINDIR=${MYBIN}
else
# with the following, binary executables will be placed in bin subdirectory of your home directory
#BINDIR=~/bin/
# if in doubt, use the following - binary executables will be placed in the current directory
BINDIR=.
endif


#
GRID_FLOAT=
# double precision grid files (not yet supported fully for NonLinLoc)
#GRID_FLOAT=-D GRID_FLOAT_TYPE_DOUBLE


CC=gcc
#CC=clang
#


# Linux
#CCFLAGS_BASIC =  -Wall -std=gnu99 ${GRID_FLOAT} -Wno-unused-but-set-variable
#CCFLAGS_BASIC =  -Wall -std=gnu99 ${GRID_FLOAT} -O0 -ffunction-sections -Wl,--gc-sections
#CCFLAGS_BASIC =  -Wall -std=gnu99 ${GRID_FLOAT} -D NLL_DEAD_CODE
CCFLAGS_BASIC =  -Wall -std=gnu99 ${GRID_FLOAT}
#
#
# optimized
export CCFLAGS = -O3 $(CCFLAGS_BASIC)
#
# profile
#export CCFLAGS= -pg $(CCFLAGS_BASIC)
#
# debug - gdb, valgrind, ...
#export CCFLAGS = $(CCFLAGS_BASIC) -g
# gdb:
# gdb --args exe_name
# lldb -- exe_name
# valgrind --leak-check=yes --dsymutil=yes exe_name <args>
# valgrind --leak-check=full --show-reachable=yes exe_name <args>


# GNU
#GNU_SOURCE=-D _GNU_SOURCE
# IMPORTANT: use following if the compiler you are using does not support GNU extensions such as:
#   fmemopen, open_memstream -  open memory as stream (you will not be able to pass observations file lines as parameters to NLLoc()
GNU_SOURCE=
#

# Linux
TIME3D_CCFLAGS=


# --------------------------------------------------------------------------
# Top level variables and rules
#
GRID_LIB_OBJS=GridLib.o util.o geo.o octtree/octtree.o alomax_matrix/alomax_matrix.o alomax_matrix/alomax_matrix_svd.o matrix_statistics/matrix_statistics.o vector/vector.o ran1/ran1.o map_project.o
NLLOC_LIB_OBJS=velmod.o GridMemLib.o phaselist.o loclist.o otime_limit.o ioformat/hypfile.o

DISTRIB_SOURCES=NLLoc_ Vel2Grid_ Grid2Time_ Time2Angles_ Grid2GMT_ LocSum_ scat2latlon_ Time2EQ_ oct2grid_
all : ${DISTRIB_SOURCES}
distrib : ${DISTRIB_SOURCES}
dev : ${DISTRIB_SOURCES}


# --------------------------------------------------------------------------
# NLLoc
#
OBJS1=NLLocLib.o ${GRID_LIB_OBJS} ${NLLOC_LIB_OBJS}
OPTIONS= $(GNU_SOURCE)

PVER=1
# --------------------------------------------------------------------------
# NLLoc general
NLLoc${PVER}.o : NLLoc${PVER}.c NLLocLib.h GridLib.h GridMemLib.h alomax_matrix/alomax_matrix.h alomax_matrix/alomax_matrix_svd.h matrix_statistics/matrix_statistics.h
	${CC} -c ${CCFLAGS} NLLoc${PVER}.c  $(OPTIONS)
# --------------------------------------------------------------------------
# NLLoc program (NLLoc)
NLLoc_ : ${BINDIR}/NLLoc
${BINDIR}/NLLoc : NLLoc_main.o NLLoc${PVER}.o ${OBJS1}
	${CC} NLLoc_main.o NLLoc${PVER}.o ${OBJS1} ${CCFLAGS} -o ${BINDIR}/NLLoc -lm
NLLoc_main.o : NLLoc_main.c NLLocLib.h GridLib.h GridMemLib.h alomax_matrix/alomax_matrix.h alomax_matrix/alomax_matrix_svd.h matrix_statistics/matrix_statistics.h
	${CC} -c ${CCFLAGS} NLLoc_main.c  $(OPTIONS)
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# Vel2Grid
#
OBJS2=${GRID_LIB_OBJS} velmod.o
PVER=1
Vel2Grid_ : ${BINDIR}/Vel2Grid
${BINDIR}/Vel2Grid : Vel2Grid${PVER}.o ${OBJS2}
	${CC} Vel2Grid${PVER}.o  ${OBJS2} ${CCFLAGS} -o ${BINDIR}/Vel2Grid -lm
Vel2Grid${PVER}.o : Vel2Grid${PVER}.c GridLib.h
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# Grid2Time
#
OBJS3=${GRID_LIB_OBJS} Time_3d_NLL.o
PVER=1
Grid2Time_ : ${BINDIR}/Grid2Time
${BINDIR}/Grid2Time : Grid2Time${PVER}.o ${OBJS3}
	${CC} Grid2Time${PVER}.o ${OBJS3} ${CCFLAGS}  \
		-o ${BINDIR}/Grid2Time -lm
Grid2Time${PVER}.o : Grid2Time${PVER}.c GridLib.h
	${CC}  ${CCFLAGS} -c Grid2Time${PVER}.c
Time_3d_NLL.o : Time_3d_NLL.c
	${CC}  ${CCFLAGS} ${TIME3D_CCFLAGS} -c -DNO_IEEE_PROTOCOL Time_3d_NLL.c
#	${CC} -c -DNO_IEEE_PROTOCOL Time_3d_NLL.c
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# Time2Angles
#
OBJS3A=${GRID_LIB_OBJS}
PVER=1
Time2Angles_ : ${BINDIR}/Time2Angles
${BINDIR}/Time2Angles : Time2Angles${PVER}.o ${OBJS3A}
	${CC} Time2Angles${PVER}.o ${OBJS3A} ${CCFLAGS}  \
		-o ${BINDIR}/Time2Angles -lm
Time2Angles${PVER}.o : Time2Angles${PVER}.c GridLib.h
	${CC}  ${CCFLAGS} -c Time2Angles${PVER}.c
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# Grid2GMT
#
OBJS44=Grid2GMT4.o ${GRID_LIB_OBJS} GridGraphLib.o
OBJS45=Grid2GMT5.o ${GRID_LIB_OBJS} GridGraphLib.o
#
Grid2GMT_ : ${BINDIR}/Grid2GMT4 ${BINDIR}/Grid2GMT5
#
${BINDIR}/Grid2GMT4 : ${OBJS44}
	${CC} ${OBJS44} ${CCFLAGS} -o ${BINDIR}/Grid2GMT4 -lm
Grid2GMT4.o : Grid2GMT4.c GridLib.h GridGraphLib.h
#
${BINDIR}/Grid2GMT5 : ${OBJS45}
	${CC} ${OBJS45} ${CCFLAGS} -o ${BINDIR}/Grid2GMT5 -lm
Grid2GMT5.o : Grid2GMT5.c GridLib.h GridGraphLib.h
#
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# LocSum
#
OBJS5=LocSum.o ${GRID_LIB_OBJS}
LocSum_ : ${BINDIR}/LocSum
${BINDIR}/LocSum : ${OBJS5}
	${CC} ${OBJS5} ${CCFLAGS} -o ${BINDIR}/LocSum -lm
LocSum.o : LocSum.c GridLib.h
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# Time2EQ
#
OBJS6=${GRID_LIB_OBJS}
PVER=1
Time2EQ_ : ${BINDIR}/Time2EQ
${BINDIR}/Time2EQ : Time2EQ${PVER}.o ${OBJS6}
	${CC} Time2EQ${PVER}.o ${OBJS6} ${CCFLAGS} -o ${BINDIR}/Time2EQ -lm
Time2EQ${PVER}.o : Time2EQ${PVER}.c GridLib.h ran1/ran1.h
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# oct2grid
#
OBJS10=oct2grid.o ${GRID_LIB_OBJS}
oct2grid_ : ${BINDIR}/oct2grid
${BINDIR}/oct2grid : ${OBJS10}
	${CC} ${OBJS10} ${CCFLAGS} -o ${BINDIR}/oct2grid -lm
oct2grid.o : oct2grid.c GridLib.h
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# scat2latlon
#
OBJS16=scat2latlon.o ${GRID_LIB_OBJS}
scat2latlon_ : ${BINDIR}/scat2latlon
${BINDIR}/scat2latlon : ${OBJS16}
	${CC} ${OBJS16} ${CCFLAGS} -o ${BINDIR}/scat2latlon -lm
scat2latlon.o : scat2latlon.c GridLib.h
# --------------------------------------------------------------------------


# --------------------------------------------------------------------------
# General compile rule
#

%.o : %.c
	$(CC) -c $(CCFLAGS)   $(OPTIONS) $< -o $@

#
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# NLL special compile rule
#

NLLocLib.o : NLLocLib.c NLLocLib.h GridLib.h velmod.h ioformat/hypfile.h

GridLib.o : GridLib.c GridLib.h  geometry/geometry.h util.h geo.h octtree/octtree.h alomax_matrix/alomax_matrix.h alomax_matrix/alomax_matrix_svd.h matrix_statistics/matrix_statistics.h ran1/ran1.h map_project.h

GridMemLib.o : GridMemLib.c GridMemLib.h  GridLib.h

GridGraphLib.o : GridGraphLib.c GridLib.h GridGraphLib.h

phaselist.o : phaselist.c phaselist.h  location.h GridLib.h

loclist.o : loclist.c loclist.h  location.h GridLib.h

#otime_limit.o : otime_limit.c otime_limit.h

#
# --------------------------------------------------------------------------



# --------------------------------------------------------------------------
# Misc
#

clean :
	rm -f *.o alomax_matrix/*.o matrix_statistics/*.o ./octtree/octtree.o \
          ./ran1/ran1.o ./vector/vector.o ./ioformat/hypfile.o

clean_bin :
	rm -f ${BINDIR}/Vel2Grid ${BINDIR}/oct2grid ${BINDIR}/NLLoc \
	${BINDIR}/LocSum ${BINDIR}/Grid2Time ${BINDIR}/Time2Angles  \
	${BINDIR}/Grid2GMT4 ${BINDIR}/Grid2GMT5  \
	${BINDIR}/Time2EQ \
	${BINDIR}/scat2latlon

#
# --------------------------------------------------------------------------
