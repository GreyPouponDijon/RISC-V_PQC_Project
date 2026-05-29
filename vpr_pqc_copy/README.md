This framework creates a VPR executable for running in RAM. The embedded CM33 code, configures SPU for FLPR to secure, copies the code from NVM to RAM and starts the VPR CPU then the cortex goes to WFE+WFI.

Setup the repo:
```
git clone ssh://git@bitbucket.nordicsemi.no:7999/~glba/dayviper.git
cd dayviper
git submodule update --init --recursive
```

Prerequisites local PC :
- RISC-V (GCC) compiler
- ARM compiler (arm-none-eabi)
- Python3
- Python module - IntelHex
- NrfUtil
- Segger J-Link

Install RISC-V compiler:
https://embecosm.com/downloads/tool-chain-downloads/#core-v-top-of-tree-compilers

Install ARM compiler:
https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

Install NrfUtil and Segger J-Link:
https://docs.nordicsemi.com/bundle/nrfutil/page/guides/installing.html

Install Python3 v3.14:
https://www.python.org/downloads/

Install Python module - IntelHex:
pip install IntelHex

### WSL

cd tools
./install.sh
cd ..
. sourceme.sh

Update the Makefile's `CROSS_COMPILE` variable or set it compile time.
This must point to where you extracted the RISC-V compiler earlier.


## Prerequisites CAD Server

When building on CAD servers, it is not necessary to download any tools, except for nrfutil for flashing to DK.

For building on CAD servers, do the following:

module load misctools/anaconda/3-2021.11.d/sig

export CM33_CROSS_COMPILE=/cad/arm/GNU_EmbeddedToolchain/gcc-arm-none-eabi-10.3-2021.07/bin/arm-none-eabi-
export VPR_CROSS_COMPILE=/pro/sag_research/tools/riscv-gcc/corev-openhw-gcc-centos7-20240407/bin/riscv32-corev-elf-

The hex file to be flashed can be accessed through local windows PC, typically by using the \\workareas mount.


## Usage

Example:
```
make CROSS_COMPILE=/home/glenn/Downloads/corev-openhw-gcc-ubuntu2204-20240114/bin/riscv32-corev-elf-
```

Or:
```
export CROSS_COMPILE=/home/glenn/Downloads/corev-openhw-gcc-ubuntu2204-20240114/bin/riscv32-corev-elf-
```
Before performing any further `make` commands (must be done every time you open a new shell session).

Useful make targets:
```
make 
make clean
```

In case of nRF54LM20A DK, also:
```
make deploy
```

The default is to compile both the CM33 and VPR app using the top level Makefile. The APP's to use for each target can be specified by using the
```
CM33_APP=<folder_to_cm33_app> and VPR_APP=<folder_to_vpr_app>

Sample:

make CM33_APP=apps/cm33/vpr_launcher VPR_APP=apps/vpr/uarte
make deploy
```

In addition, it is also possible to deploy only the CM33 target app, using the sub-target `cm33_deploy`:

```
make -f makefile.cm33 CM33_APP=apps/cm33/uarte/ cm33_deploy
```



