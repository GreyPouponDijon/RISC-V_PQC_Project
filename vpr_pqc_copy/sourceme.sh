#!/usr/bin/env bash
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export PATH=$SCRIPT_DIR/tools/riscv64-zephyr-elf/bin:$SCRIPT_DIR/tools/arm-zephyr-eabi/bin:$SCRIPT_DIR/tools/nrfutil/bin:$PATH
. tools/venv/bin/activate
