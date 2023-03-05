#!/bin/bash -e

ROOT_DIR=$PWD
PYTHON_ENV=$ROOT_DIR/.env
PYBIN=$PYTHON_ENV/bin
PRE_COMMIT=$PYBIN/pre-commit
PYTHON=$PYBIN/python
FILE=gcc-arm-none-eabi-9-2020-q2-update

oops() {
  echo -e "\033[1;41mError:\033[0m \033[1;31m${*}\033[0m" >&2
  exit 1
}

if [ "$1" == "build" ]
then
  source $PYTHON_ENV/bin/activate
  OUT=$ROOT_DIR/cmake_build/NUCLEO_F767ZI/develop/GCC_ARM
  mbed-tools configure -m NUCLEO_F767ZI -t gcc_arm
  cmake -S . -B $OUT -GNinja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
  cmake --build $OUT
  ln -sf $OUT/compile_commands.json $ROOT_DIR
  deactivate
elif [ "$1" == "setup" ]
then
  python3 -m venv $PYTHON_ENV
  source $PYTHON_ENV/bin/activate
  pip install mbed-tools
  mbed-tools deploy
  pip install -r mbed-os/requirements.txt
  pip install ninja
  deactivate

  UNAME=$(uname)
  ARCH=$(arch)
  if [ ! -d $PYTHON_ENV/$FILE ]
  then
    if [ "$UNAME" == "Darwin" ]
    then
      TYPE=-mac
    elif [ "$UNAME" == "Linux" ]
    then
      if [ "$ARCH" == "aarch64" ]
      then
        TYPE=-aarch64-linux
      else
        TYPE=-x86_64-linux
      fi
    else
      oops "uHHHHHhhhhHHh..."
    fi
    curl -LO https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/$FILE$TYPE.tar.bz2
    tar xf $ROOT_DIR/$FILE$TYPE.tar.bz2 -C $PYTHON_ENV
    rm -f $ROOT_DIR/$FILE$TYPE.tar.bz2
    ln -sf $PYTHON_ENV/$FILE/bin/* $PYTHON_ENV/bin
  fi
else
  oops "uHHHHHhhhhHHh..."
fi
