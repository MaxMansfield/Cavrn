#!/bin/bash
# The cavrn Installer
# Created By Max Mansfield 
# DOB: March 16th, 2015
# Contributors: Max Mansfield

NAME="cavrn"

MAINTAINER="Max Mansfield"
MAINTAINER_EMAIL="max.m.mansfield@gmail.com"

# Config
VER=0.2.3 
REL=1

#Arch based distros
ARCH_MAKE_DEPS[0]="avr-gcc"
ARCH_MAKE_DEPS[1]="avr-libc"
ARCH_MAKE_DEPS[2]="avrdude"
ARCH_MAKE_DEPS[3]="make"

ARCH_DEPS[0]=${ARCH_MAKE_DEPS[0]}
ARCH_DEPS[1]=${ARCH_MAKE_DEPS[1]}
ARCH_DEPS[2]=${ARCH_MAKE_DEPS[2]}
ARCH_DEPS[3]=${ARCH_MAKE_DEPS[3]}

#### Debian Based Distros
DEB_DEPS[0]="avr-gcc"
DEB_DEPS[0]="avr-libc"

#### Red Hat based distros
RED_MAKE_DEPS[0]="avr-gcc"
RED_MAKE_DEPS[1]="avr-libc"

RED_DEPS[0]="${RED_MAKE_DEPS[0]}"
RED_DEPS[0]="${RED_MAKE_DEPS[1]}"
RED_DEPS[1]="screen"
RED_DEPS[2]="avrdude"

SRC_DIR="src"
BUILD_DIR="build"
LIB_NAME="${NAME}.so"
MAN_SEC="man3"

INST_INCL="install_includes.tar.gz"

which curl > /dev/null

if [ $? != 0 ];
then
    echo "You must have curl installed to continue."
    exit 1
fi

if [ ! -d "scripts/" ];
then
    echo "The scripts/ directory does not exist."
    exit 1
fi
curl "http://bytewise.io/download/${INST_INCL}" > "${INST_INCL}"
tar -xzf "${INST_INCL}" -C "scripts/"

source "scripts/inc/installer.inc"
# Signify Success
exit 0
