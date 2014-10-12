# makefile of swooz-teleoperation project using Visual C++
# Guillaume Gibert / Florian Lance
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

FABRIC_LINK_OBJ=\
    $(LIBDIR)/particle.obj\
    $(LIBDIR)/tissu.obj\
    $(LIBDIR)/freeflycamera.obj\
    $(LIBDIR)/main.obj\

############################################################################## Makefile commands

!if "$(ARCH)" == "x86"
all: $(BINDIR)/Fabric.exe
!endif

!if "$(ARCH)" == "amd64"
all: $(BINDIR)/Fabric-x64.exe
!endif

############################################################################## exe files

WIN_CONFIG = $(SETARGV) $(BINMODE) $(WINLIBS)

# exec files to be generated
$(BINDIR)/Fabric.exe: $(FABRIC_LINK_OBJ) $(LIBS_FABRIC)
        $(LINK) /OUT:$(BINDIR)/Fabric.exe $(LFLAGS_FABRIC) $(FABRIC_LINK_OBJ) $(LIBS_FABRIC) $(WIN_CONFIG)


$(BINDIR)/Fabric-x64.exe: $(FABRIC_LINK_OBJ) $(LIBS_FABRIC)
        $(LINK) /OUT:$(BINDIR)/Fabric-x64.exe $(LFLAGS_FABRIC) $(FABRIC_LINK_OBJ) $(LIBS_FABRIC) $(WIN_CONFIG)

##################################################### devices

$(LIBDIR)/main.obj: ./src/main.cpp
        $(CC) -c ./src/main.cpp $(CFLAGS_DYN) $(FABRIC_INC) -Fo"$(LIBDIR)/main.obj"

$(LIBDIR)/particle.obj: ./src/particle.cpp
        $(CC) -c ./src/particle.cpp $(CFLAGS_DYN) $(FABRIC_INC) -Fo"$(LIBDIR)/particle.obj"

$(LIBDIR)/tissu.obj: ./src/tissu.cpp
        $(CC) -c ./src/tissu.cpp $(CFLAGS_DYN) $(FABRIC_INC) -Fo"$(LIBDIR)/tissu.obj"

$(LIBDIR)/freeflycamera.obj: ./src/freeflycamera.cpp
        $(CC) -c ./src/freeflycamera.cpp $(CFLAGS_DYN) $(FABRIC_INC) -Fo"$(LIBDIR)/freeflycamera.obj"
