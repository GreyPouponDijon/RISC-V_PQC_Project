wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.4/toolchain_linux-x86_64_arm-zephyr-eabi.tar.xz
tar xvf toolchain_linux-x86_64_arm-zephyr-eabi.tar.xz
rm toolchain_linux-x86_64_arm-zephyr-eabi.tar.xz

wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.4/toolchain_linux-x86_64_riscv64-zephyr-elf.tar.xz
tar xvf toolchain_linux-x86_64_riscv64-zephyr-elf.tar.xz
rm toolchain_linux-x86_64_riscv64-zephyr-elf.tar.xz

./create_venv.sh

mkdir nrfutil
mkdir nrfutil/bin
curl https://files.nordicsemi.com/artifactory/swtools/external/nrfutil/executables/x86_64-unknown-linux-gnu/nrfutil -o nrfutil/bin/nrfutil
chmod 755 nrfutil/bin/nrfutil
./nrfutil/bin/nrfutil install device
./nrfutil/bin/nrfutil upgrade

echo "***********************************************************************"
echo ""
echo "Open in a browser:"
echo ""
echo "https://www.segger.com/downloads/jlink/JLink_Linux_V876_x86_64.deb, read the terms and start the download."
echo ""
echo "cp /mnt/c/Users/USERNAME/Downloads/JLink_Linux_V876_x86_64.deb ."
echo ""
echo "Install the following packages for JLink:"
echo ""
echo "sudo apt install libice6 libsm6 libxcb-icccm4 libxcb-image0 libxcb-keysyms1 libxcb-render-util0 libxcb-shape0 libxcb-util1 libxcb-xkb1 libxkbcommon-x11-0"
echo ""
echo "Now install JLink:"
echo ""
echo "sudo dpkg -i JLink_Linux_V876_x86_64.deb"
echo ""
