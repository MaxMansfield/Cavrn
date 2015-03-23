#!/bin/bash
# The cavrn Installer
# Created By Max Mansfield 
# DOB: March 16th, 2015
# Last Modified: March 22nd, 2015
# Contributors: Max Mansfield

NAME="cavrn"


MAINTAINER="Max Mansfield"
MAINTAINER_EMAIL="max.m.mansfield@gmail.com"

# Config
VER=0.2.3 
REL=1


#Arch based distros
ARCH_MAKE_DEPS[0]="qt5"
ARCH_MAKE_DEPS[1]="make"

ARCH_DEPS[0]=${ARCH_MAKE_DEPS[0]}
ARCH_DEPS[1]=${ARCH_MAKE_DEPS[1]}


#### Debian Based Distros
DEB_DEPS[0]="qt5-default"

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



source "scripts/usr/handle_args.inc"

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Point of execution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Notify if the distro is supported
source "scripts/install.sh"  

# Signify Success
exit 0
