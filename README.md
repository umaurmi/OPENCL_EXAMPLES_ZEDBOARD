# OPENCL_EXAMPLES_ZEDBOARD
This repository contains a set of examples of opencl code that can run on the zedboard zynq all programmable soc.

The repository contains certain OpenCl Examples that can be run on the zedboard cpu as of now. The example codes are pretty generic and can run on linux targets as well in exactly the same way. Please read this README file completely in order to use this repository effectively.

## Table of Contents
+ [Pre-Requisites](#prereq) 
    + [Zedboard](#prereq-zb)
    + [linux x64 targets(intel only)](#prereq-x64)
    + [mac x64 targets](#prereq-x64)


## <a name="prereq"></a> 1) Pre-Requisites
There are a set of pre-requisites that must be fulfilled in order for the code and profiling to work on the zedboard as well as linux targets, please follow the instructions given below

### <a name="prereq-zb"></a> 1.1: Zedboard

* **Booting Xilinux on zedboard:**
The following examples will run on POCL installed over the linux version for zedboard "xilinux" xilinux is an ubuntu 12.04 flavour that also can be used to integrate the linux running on the PS directly to the PL through /dev/.
In order to install the xilinux on zedboard with the base xillybus bitstream please follow the instructions given in the "Getting Started" guide provided in the <a href="http://xillybus.com/xillinux" target="_blank">xillybus website</a>



* **Installing POCL on zedboard**
    *    Before installing POCL, please make sure that all the required dependencies are installed.
         * Refer to wiki: <a href="https://github.com/umaurmi/OPENCL_EXAMPLES_ZEDBOARD/wiki/Installing-POCL-dependencies-on-zedboard-zynq-7000-all-programmable-SoC" target="_blank">Installing-POCL-dependencies-on-zedboard-zynq-7000-all-programmable-SoC</a>
    *    Refer to wiki: to install POCL **Only after all dependencies**
    *    An install script to automatically install all dependencies will be released soon.

### <a name="prereq-x64"></a> 1.2: linux-x64 targets(intel only)

### <a name="prereq-x64"></a> 1.3: mac x64 targets

       **COMING SOON**
