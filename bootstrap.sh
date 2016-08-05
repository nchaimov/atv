#!/bin/bash
           
export BOOST_ROOT=$HOME/src/boost_1_56_0
export OTF2_ROOT=$HOME

SOURCE_DIR=$PWD
BUILD_DIR=$PWD/build
INST_DIR=$PWD/build

mkdir -p build
cd $BUILD_DIR
cmake $SOURCE_DIR -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$INST_DIR -DBOOST_ROOT=$BOOST_ROOT -DOTF2_ROOT=$OFT2_ROOT
make -j4 install
cd $SOURCE_DIR
