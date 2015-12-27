# OS Name (Linux or Darwin)
OSUPPER = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
OSLOWER = $(shell uname -s 2>/dev/null | tr [:upper:] [:lower:])

# Flags to detect 32-bit or 64-bit OS platform
OS_SIZE = $(shell uname -m | sed -e "s/i.86/32/" -e "s/x86_64/64/")
OS_ARCH = $(shell uname -m | sed -e "s/i386/i686/")

# These flags will override any settings
ifeq ($(i386),1)
	OS_SIZE = 32
	OS_ARCH = i686
endif

ifeq ($(x86_64),1)
	OS_SIZE = 64
	OS_ARCH = x86_64
endif

# Flags to detect either a Linux system (linux) or Mac OSX (darwin)
DARWIN = $(strip $(findstring DARWIN, $(OSUPPER)))

# Location of the CUDA Toolkit binaries and libraries
CUDA_PATH       ?= /usr/local/cuda
CUDA_INC_PATH   ?= $(CUDA_PATH)/include
CUDA_BIN_PATH   ?= $(CUDA_PATH)/bin
ifneq ($(DARWIN),)
  CUDA_LIB_PATH  ?= $(CUDA_PATH)/lib
else
  ifeq ($(OS_SIZE),32)
    CUDA_LIB_PATH  ?= $(CUDA_PATH)/lib
  else
    CUDA_LIB_PATH  ?= $(CUDA_PATH)/lib64
  endif
endif


# Common binaries
NVCC            ?= $(CUDA_BIN_PATH)/nvcc
CC 				=  g++

# Extra user flags
EXTRA_NVCCFLAGS ?=
EXTRA_LDFLAGS   ?=
#CFLAGS = -O3 -Wall std=gnu99
CFLAGS=-O3 -Wall

# CUDA code generation flags
#GENCODE_SM10    := -gencode arch=compute_10,code=sm_10
#GENCODE_SM20    := -gencode arch=compute_20,code=sm_20
GENCODE_SM30    := -gencode arch=compute_30,code=sm_30 -gencode arch=compute_35,code=sm_35
GENCODE_FLAGS   := $(GENCODE_SM30)


# OS-specific build flags
ifneq ($(DARWIN),) 
      LDFLAGS   := -Xlinker -rpath $(CUDA_LIB_PATH) -L$(CUDA_LIB_PATH) -lcudart
      CCFLAGS   := -arch $(OS_ARCH) 
else
  ifeq ($(OS_SIZE),32)
      LDFLAGS   := -L$(CUDA_LIB_PATH) -lcudart
      CCFLAGS   := -m32
  else
      LDFLAGS   := -L$(CUDA_LIB_PATH) -lcudart
      CCFLAGS   := -m64 
  endif
endif

# OS-architecture specific flags
ifeq ($(OS_SIZE),32)
      NVCCFLAGS := -m32
else
      NVCCFLAGS := -m64
endif

# Common includes and paths for CUDA
INCLUDES      := -I$(CUDA_INC_PATH) -I. -I.. -I../../common/inc

#openCL libs
CL_LIBS=OpenCL


SRCS=$(wildcard *.c)
CPP_SRCS=$(wildcard *.cpp)
CU_SRCS=$(wildcard *.cu)
OBJS=$(SRCS:.c=.o) $(CPP_SRCS:.cpp=.o)  $(CU_SRCS:.cu=.o)
EXE=matrixmul

#Target Rules

$(EXE):$(OBJS)
	$(CC) $(INCLUDES) $(OBJS) -L $(CUDA_LIB_PATH) -l$(CL_LIBS) $(LDFLAGS) $(EXTRA_LDFLAGS) -o $(EXE)

%.o:%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

%.o:%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

%.o:%.cu
	$(NVCC) $(NVCCFLAGS) $(EXTRA_NVCCFLAGS) $(GENCODE_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJS) $(CU_OBJS) $(EXE)
