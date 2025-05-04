#!/bin/sh
set -e

cp hardware-definitions/dist/c/wswan/ports.h libws/include/ws/

if [ -d build ]; then
	rm -r build
fi
mkdir build
cp -aRv target build/
cd crts
make
DESTDIR=../build make install
cd ..

build_library () {
	cd "$1"
	make -j1 clean WF_TARGET_DIR=../build/target/"$2" TARGET="$2"
	make WF_TARGET_DIR=../build/target/"$2" TARGET="$2"
	make -j1 install WF_TARGET_DIR=../build/target/"$2" TARGET="$2"
	cd ..
}

for i in wswan/bootfriend wswan/small wswan/medium wswan/small-sram wswan/medium-sram wwitch; do
	build_library libc $i
done

for i in wswan/bootfriend wswan/small wswan/medium wswan/small-sram wswan/medium-sram wwitch; do
	build_library libws $i
done

for i in wwitch; do
	cd libww/library/gcc
	make -j1 clean WF_TARGET_DIR=../../../build/target/wwitch TARGET=wwitch
	make WF_TARGET_DIR=../../../build/target/wwitch TARGET=wwitch
	make -j1 install WF_TARGET_DIR=../../../build/target/wwitch TARGET=wwitch
	cd ../../..
done

for i in wswan/bootfriend wswan/small wswan/medium; do
	build_library libwwcl $i
done

for i in wswan/bootfriend wswan/small wswan/medium wswan/small-sram wswan/medium-sram wwitch; do
	build_library libwsx $i
done
