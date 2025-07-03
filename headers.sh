#!/bin/bash
set -e
. ./config.sh

mkdir -p "$SYSROOT"

echo $CC

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done
