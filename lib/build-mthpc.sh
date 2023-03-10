#!/usr/bin/env bash

MTHPC_DIR="mthpc-$(date +"%Y-%m-%d")"

set -x
bash remove-mthpc.sh
rm -rf mthpc-*
git clone https://github.com/linD026/mthpc.git $MTHPC_DIR
make -C $MTHPC_DIR build
mv $MTHPC_DIR/mthpc/include/mthpc ../include/
mv $MTHPC_DIR/mthpc/libmthpc.so .
make -C $MTHPC_DIR cleanall
echo "$MTHPC_DIR-$(uname)-$(uname -m)" > current_mthpc_version
