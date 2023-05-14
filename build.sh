#!/bin/bash

# Set BUILD_DIR to Keystone build directory
BUILD_DIR=$(pwd)/build
SDK_BUILD_DIR=$(pwd)/sdk/build 

read -r -p "Run QEMU? [Y/n] " response
response=${response,,}

set -e
cd $SDK_BUILD_DIR
make
make install
make examples
cd $BUILD_DIR/examples
make clean
cd ..
cmake ..
make 
make examples
find ./examples/ -name '*.ke' -exec cp \{\} ./overlay/root/ \;
cp sm.build/platform/generic/firmware/fw_payload.bin overlay/root/
make image
if [[ "$response" =~ ^(no|n)$ ]]
then
    exit 0
fi
./scripts/run-qemu.sh

# Then:
# buildroot login: root
# Password: sifive
# # insmod keystone-driver.ko
# # ./hello.ke
# ...
# # ./hello-native.ke