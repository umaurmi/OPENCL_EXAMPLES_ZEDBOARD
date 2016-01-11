# OPENCL_EXAMPLES_ZEDBOARD
This repository contains a set of examples of opencl code that can run on the zedboard zynq all programmable soc.

The repository contains certain OpenCl Examples that can be run on the zedboard cpu as of now. The example codes are pretty generic and can run on linux targets as well in exactly the same way. Please read this README file completely in order to use this repository effectively.

## Table of Contents
+ [Pre-Requisites](#prereq) 
    + [Zedboard Pre-Requisites](#prereq-zb)
    + [linux x64 targets(intel only)](#prereq-x64)
    + [mac x64 targets](#prereq-x64)
+ [Installing PAPI and XLWT for timing and profiling](#instpapi)
    + [Installing PAPI(Performance API)](#papi)
    + [Installing XWLT package](#xlwt)


## <a name="prereq"></a> 1) Pre-Requisites
There are a set of pre-requisites that must be fulfilled in order for the code and profiling to work on the zedboard as well as linux targets, please follow the instructions given below

### <a name="prereq-zb"></a> 1.1: Zedboard Pre-Requisites

* **Booting Xilinux on zedboard:**
The following examples will run on POCL installed over the linux version for zedboard "xilinux" xilinux is an ubuntu 12.04 flavour that also can be used to integrate the linux running on the PS directly to the PL through /dev/.
In order to install the xilinux on zedboard with the base xillybus bitstream please follow the instructions given in the "Getting Started" guide provided in the <a href="http://xillybus.com/xillinux" target="_blank">xillybus website</a>

* **Installing POCL on zedboard**
    *    Before installing POCL, please make sure that all the required dependencies are installed.
         * Refer to wiki: <a href="https://github.com/umaurmi/OPENCL_EXAMPLES_ZEDBOARD/wiki/Installing-POCL-dependencies-on-zedboard-zynq-7000-all-programmable-SoC" target="_blank">Installing-POCL-dependencies-on-zedboard-zynq-7000-all-programmable-SoC</a>
    *    Refer to wiki: to install POCL **Only after all dependencies**
    *    An install script to automatically install all dependencies will be released soon.

##<a name="instpapi"></a> 2: Installing PAPI and XLWT for timing and profiling

###<a name="papi"></a> 2.1: Installing PAPI(Performance API)
The perforamnce api is an api that can be used for effective profiling in arm as well as intel targets. In both cases the api needs to be compiled from source to support the profiling used by us. Please follow the below steps for installing PAPI in x64 or Arm.

Download the latest stable tarball of PAPI from the <a href="http://icl.cs.utk.edu/papi/"target="_blank">PAPI website</a>

    $wget <link to the PAPI version you wish to download> (eg:- wget http://icl.cs.utk.edu/projects/papi/downloads/papi-5.4.1.tar.gz)

Extract the tarball by using the tar command as shown below:

    $tar -zxvf <name of tarball> (eg tar-zxvf papi-5.4.1.tar.gz)

Enter the folder and run the following commands to install the software:

    > ./configure
    > make
    > sudo make install


P.S. :- The makefiles are built assuming the papi libraries are installed in the folder :- /usr/local/lib/libpapi.a, if your papi library is installed in some other location, you might need to edit the makefiles to support papi, we are currently working on making the makefiles more generic.


###<a name="xlwt"></a> 2.2: Installing XWLT package
The profiling is done using a python code which generates a multisheet excel page with all the timing analyses. Please note the xlwt tool installed and the python code is for python-2.7. It will not work with python-3.0

In order to install XLWT python-pip needs to be installed. PIP can be installed in 2 ways. For x64 and other well supported targets it can be installed with apt-get:

    $apt-get install python-pip

For ubuntu on arm, you need to install PIP using curl, follow the steps below to compile and install pip from source.

    $mkdir python-pip
    $cd python-pip
    $curl "https://bootstrap.pypa.io/get-pip.py" -o "get-pip.py"
    $python get-pip.py

Once this is done you can verify whether pip is installed by using the following command:

    $pip --help


Once pip is successfully installed, use pip to install the XLWT package for python:

    $pip install xlwt
    

### <a name="prereq-x64"></a> 1.2: linux-x64 targets(intel only)

       **COMING SOON**

### <a name="prereq-x64"></a> 1.3: mac x64 targets

       **COMING SOON**
