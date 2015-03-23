NAME="libnibl"

MAINTAINER="Max Mansfield"
MAINTAINER_EMAIL="max.m.mansfield@gmail.com"

# Config
VER=0.11 
REL=1


#Arch based distros
ARCH_MAKE_DEPS[0]="qt5-base"
ARCH_MAKE_DEPS[1]="make"

ARCH_DEPS[0]=${ARCH_MAKE_DEPS[0]}
ARCH_DEPS[1]=${ARCH_MAKE_DEPS[1]}


#### Debian Based Distros
DEB_DEPS[0]="qt5-default"

#### Red Hat based distros
RED_MAKE_DEPS[0]="qt5"
RED_MAKE_DEPS[1]="make"

RED_DEPS[0]="${RED_MAKE_DEPS[0]}"
