
# Florian Lance
# lyon sept 2013

!IF "$(CFG)" != "Release" &&  "$(CFG)" != "Debug"
!ERROR Invalid CFG "($CFG)
!ENDIF

!IF "$(ARCH)" != "x86" &&  "$(ARCH)" != "amd64"
!ERROR Invalid ARCH "($ARCH)
!ENDIF

CC=cl
LINK=link

!INCLUDE <./makefile-include>


############################################################################## OBJ LISTS

WATER_LINK_OBJ=\
    $(LIBDIR)/main.obj $(DIST_LIBDIR)/freeflycamera.obj\

############################################################################## Makefile commands

!if "$(ARCH)" == "x86"
all: $(BINDIR)/Water.exe
!endif

!if "$(ARCH)" == "amd64"
all: $(BINDIR)/Water-x64.exe
!endif

############################################################################## exe files

WIN_CONFIG = $(SETARGV) $(BINMODE) $(WINLIBS)

# exec files to be generated
$(BINDIR)/Water.exe: $(WATER_LINK_OBJ) $(LIBS_FABRIC)
        $(LINK) /OUT:$(BINDIR)/Water.exe $(LFLAGS_WATER) $(WATER_LINK_OBJ) $(LIBS_WATER) $(WIN_CONFIG)


$(BINDIR)/Water-x64.exe: $(WATER_LINK_OBJ) $(LIBS_FABRIC)
        $(LINK) /OUT:$(BINDIR)/Water-x64.exe $(LFLAGS_WATER) $(WATER_LINK_OBJ) $(LIBS_WATER) $(WIN_CONFIG)

##################################################### devices

$(LIBDIR)/main.obj: ./src/main.cpp
        $(CC) -c ./src/main.cpp $(CFLAGS_DYN) $(WATER_INC) -Fo"$(LIBDIR)/main.obj"
