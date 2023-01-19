PETSc.pc := $(PETSC_DIR)/$(PETSC_ARCH)/lib/pkgconfig/PETSc.pc
PACKAGES := $(PETSc.pc)

CXX = mpic++

CXXFLAGS = $(shell pkg-config --cflags $(PACKAGES))
LDFLAGS = $(shell pkg-config --libs-only-L $(PACKAGES)) 
LDFLAGS += -Wl,-rpath,$(shell pkg-config --variable=libdir $(PACKAGES)) 
LDLIBS = $(shell pkg-config --libs-only-l $(PACKAGES))

