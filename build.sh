#!/bin/sh
set -e

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

for i in wswan/small wswan/medium wwitch; do
	build_library libc $i
done

for i in wswan/small wswan/medium wwitch; do
	build_library libws $i
done

for i in wwitch; do
	build_library libww $i
done

for i in wswan/small wswan/medium wwitch; do
	build_library libwsx $i
done
