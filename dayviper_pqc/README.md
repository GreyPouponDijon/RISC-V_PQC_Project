This framework creates a VPR executable for running in RAM. The embedded CM33 code, configures SPU for FLPR to secure, copies the code from NVM to RAM and starts the VPR CPU then the cortex goes to WFE+WFI.

Setup the repo:
```
git clone ssh://git@bitbucket.nordicsemi.no:7999/~glba/dayviper.git
cd dayviper
git submodule update --init --recursive
```

Prerequisites:
- RISC-V (GCC) compiler
- mergehex (nrf-command-line-tools) 
- nrfjprog (nrf-command-line-tools) (nRF54L15 PDK) 

Install RISC-V compiler:
https://www.embecosm.com/resources/tool-chain-downloads/#corev

nrfjprog/mergehex:
https://www.nordicsemi.com/Products/Development-tools/nRF-Command-Line-Tools/Download?lang=en#infotabs

Update the Makefile's `CROSS_COMPILE` variable or set it compile time.
This must point to where you extracted the RISC-V compiler earlier.

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



