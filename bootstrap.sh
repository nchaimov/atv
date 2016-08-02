#!/bin/bash
           
export BOOST_ROOT=$HOME/hpx/boost_1_57_0
export OTF2_ROOT=$HOME/hpx/otf2-2.0-inst

SOURCE_DIR=$PWD
BUILD_DIR=$PWD/build
INST_DIR=$PWD/build

mkdir -p build
cd $BUILD_DIR
cmake $SOURCE_DIR -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=$INST_DIR -DBOOST_ROOT=$BOOST_ROOT -DOTF2_ROOT=$OFT2_ROOT
make -j16 install
cd $SOURCE_DIR
