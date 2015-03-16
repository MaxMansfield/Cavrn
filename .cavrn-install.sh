#!/bin/bash
# The Cavrn Makefile
# Created By Max Mansfield 
# DOB: March 16th, 2015
# Last Modified: March 16th, 2015
# Contributors: Max Mansfield


    
MAINTAINER="Max Mansfield"
MAINTAINER_EMAIL="max.m.mansfield@gmail.com"

# Config
VER=0.1.5 
REL=1

# Error Codes
OKAY=0
EPERM=1      # Operation not permitted
ENOENT=2     # No such File or directory
ENXIO=6      # No such device or address
EBADF=9      # Bad file number
EINVAL=22    # Invalid argument 
ENETDOWN=100 # Network is down *thrown by apt when package is not found



# Text Colors
green='\e[0;32m'     # green - success
Bgreen='\e[1;32m'    # Bold green

red='\e[0;31m'       # red - errors
Bred='\e[1;31m'      # Bold red - error titles
bred='\e[5;31m'      # blinking red - errors

blue='\e[0;34m'      # blue - accents
Bblue='\e[1;34m'     # Bold blue - bolder accents?

magenta='\e[0;35m'   # magenta - accents
Bmagenta='\e[1;35m'  # Bold magenta

yellow='\e[0;33m'
endcolor='\e[0m'     # END - stop coloring text



show_usage(){
    printf "${blue}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${endcolor}\n"
    printf "\t\t\t\t${Bblue}Usage${endcolor}\n"
    printf "${blue}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${endcolor}\n\n"
    printf "${magenta}Provide Cavrn with arguments as to where it should look for install files\n"
    printf "or simply use the ${Bmagenta}--default ${magenta}command.${endcolor}\n"

    printf "\n${magenta} %s [option] [value] ${endcolor}\n\n"
    printf "\n${green}Parameters:${endcolor}\n\t"
    
    printf "\n\t ${Bmagenta}-e${green},${Bmagenta}--example \n\t\t${blue}Takes the directory of the examples as an argument.${endcolor}\n"
    

    printf "\n\t ${Bmagenta}-s${green},${Bmagenta}--source\n\t\t${blue}Takes the paths of the source files to be installed.${endcolor}\n" 

    printf "\n\t ${Bmagenta}-b${green},${Bmagenta}--build\n\t\t${blue}Takes the directory of the examples as an argument.${endcolor}\n" 
    
    printf "\n\t ${Bmagenta}--default\n\t\t${blue}Uses the default hard-coded directory paths\n${endcolor}"

    printf "${blue}\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${endcolor}"


}



#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Folder and File Info ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
NAME="cavrn"
BASENAME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"

TOPDIR=$(pwd)

INCLUDE_DIR="/usr/include/${NAME}"
DOC_DIR="/usr/share/man/man3/"

# Information for obtaining the distro
OSFILE="/etc/os-release"
if [[ -f "$OSFILE" ]];
then
    DISTRO="$(egrep '^ID=' $OSFILE | egrep -o  '[[:alpha:]]{3,}')"
    
fi

ERROR_LOG="${DISTRO}-$(uname -m)-($(date +%T)).log"

if [ ! -e $ERROR_LOG ];
then
    touch $ERROR_LOG
    echo `uname -a` > $ERROR_LOG
fi
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Distribution specific variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#### Arch Based distros
ARCH="arch"
MANJ="manjaro"
ANTE="antergos"

ARCH_DISTROS[0]=$ARCH
ARCH_DISTROS[1]=$MANJ
ARCH_DISTROS[2]=$ANTE


ARCH_MAKE_DEPS[0]="avr-gcc"
ARCH_MAKE_DEPS[1]="avr-libc"

ARCH_OPT_DEPS[0]="screen"

ARCH_DEPS[0]=${ARCH_MAKE_DEPS[0]}
ARCH_DEPS[1]=${ARCH_MAKE_DEPS[1]}
ARCH_DEPS[2]="avrdude"


	    
#### Debian Based Distros
DEBIAN="debian"
UBUNTU="ubuntu"
ELEMENT="elementary"

DEB_DISTROS[0]=$DEBIAN
DEB_DISTROS[1]=$UBUNTU
DEB_DISTROS[2]=$ELEMENT

DEB_DEPS[0]="qt5-default"

#### Red Hat based distros
FEDORA="fedora"
CENTOS="centos"

RED_DISTROS[0]=$FEDORA
RED_DISTROS[1]=$CENTOS

RED_MAKE_DEPS[0]="wget"
RED_MAKE_DEPS[1]="make"



distro_count=0
for distro in ${ARCH_DISTROS[@]}
do
    DISTROS[$distro_count]=$distro
    distro_count=$((distro_count + 1))
    
done

for distro in ${DEB_DISTROS[@]}
do
    DISTROS[$distro_count]=$distro
    distro_count=$((distro_count + 1))
done

for distro in ${RED_DISTROS[@]}
do
    DISTROS[$distro_count]=$distro
    distro_count=$((distro_count + 1))
done

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Handle command line args ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
if [ $#  == 0 ];
then
    show_usage
    printf "\n${bred}No arguments given.${endcolor}\n"
    exit $EINVAL 
fi

s_count=0
while [[ $# > 1 ]]
do
    token="$1"
    case $token in
	-e|--example)
	    if [ -d $2 ];
	    then
		EXMPL_DIR="$2"
		printf "\n\t${green}Example Directory :${blue} %s${endcolor}\n" $(pwd)/$EXMPL_DIR
	    else
		printf "\n${Bred}The example directory [${bred}%s${Bred}] does not exist.${endcolor}\n" $(pwd)/$2
		exit $ENOENT
	    fi
	    
	    shift
	    ;;
	-s|--source)
	    for path in $2
	    do
		if [ -e $path ];
		then
		    SRC[$s_count]="$path"
		    s_count=$((s_count + 1))
		    printf "\n\t${green}Source Path ${magenta}[${blue}%d${magenta}]${green}:${blue} %s${endcolr}\n" $s_count "$(pwd)/$path"
		fi
	    done	  
	    shift
	    ;;
	-b|--build)
	    if [ -d $2 ];
	    then
		BUILD_DIR="$2"
		printf "\n\t${green}Build Directory:${blue} %s${endcolor}\n" $(pwd)/$BUILD_DIR
	    else
		printf "\n${Bred}The build directory [${bred}%s${Bred}] does not exist.${endcolor}\n" $(pwd)/$2
		exit $ENOENT
	    fi
	    shift
	    ;;
	--default)
	    EXMPL_DIR="examples"
	    SRC="./main.c"
	    BUILD_DIR="build"
	    printf "${green}Default settings successfully applied.${endcolor}"
	    shift
	    ;;
	*)
	    show_usage
	    printf "\n${Bred}Invalid Argument:${endcolor} ${bred}%s${endcolor}\n" $2
	    exit $EINVAL
	    ;;
    esac
    shift
done



if [ -z "$SRC" ]
then
    printf "\n${red}You must provide a source directory to install.${endcolor}\n"
    MISSING=1
fi

if [ $MISSING ];
then
    exit $EBADF
fi


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Function Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# trap ctrl-c to exit when it's used
trap ctrl_c INT

function ctrl_c() {
    printf "${endcolor}"
    exit 0
}



####
# The main error function. To be invoked by itself or by check_err
####
err(){
    if [ $#  -gt 2 ];
    then

       
        printf "\n${Bred}${4^} %s error while running on ${Bblue} %s ${Bred} ====================${endcolor}\n" "$BASENAME" "${DISTRO^}" 1>&2
        printf "${magenta}-------------------------------------------------------------------------${endcolor}\n" 1>&2
	printf "${Bred}${4^} Error($1) during:${red} %s${endcolor}\n" "$LINE" 1>&2
	

	printf "\n${Bred}%s\n${yellow}%s\n" "$2" "$3" 1>&2
	printf "\n${Bblue}Please retry the installation.\nIf the problem persists contact the current maintainer with the log file below.\n\n" 1>&2
	printf "\tMaintainer: %s <%s>\n\n" "$MAINTAINER" "$MAINTAINER_EMAIL" 1>&2
	printf "${yellow}Log File:\n\t%s\n${endcolor}"  "$(pwd)/$ERROR_LOG"


        printf "${magenta}-------------------------------------------------------------------------${endcolor}\n" 1>&2
	printf "${Bred}=========================================================================${endcolor}\n" 1>&2
	
	
	if [ -n $4 ];
	then
	    printf "Exiting due to fatal error %d...\n" $1 1>&2
	    exit $1
	fi

	return $1
    fi
}

##
# check_err proceeds any command that is to be checked for failure and will handle
#+reporting to the user based on each command and its severity.
# Usage: check_err sudo pacman -S git
##
check_err(){
    # get args
    LINE="$@"
    # run args	
    $LINE
    # get code
    CODE=$?
    #do something about it.
    case $CODE in
	$OKAY )
        # DO NOTHING
	;;
	$EPERM )
	    MESSAGE="Make sure the same version isn't installed and you haven't changed the installation directory."
	    ERROR="Operation not permitted. "
	    FATAL="fatal"
	    ;;
	$ENETDOWN )
	    MESSAGE="Check your network connection and make sure you arent using you package manager."
	    ERROR="Network not found."
	    FATAL="fatal"
	    ;;
	$ENOENT )
	    MESSAGE="Ensure that the installation directory has not been altered."
	    	    ERROR="No such file or directory."
	    FATAL="fatal"
	    ;;
	$ENXIO )
	    MESSAGE="This usually means a group or user does not exist while using the usermod command.You may have trouble running corepack without root access."
	    ERROR="No Address."
	    ;;
	$EBADF )
	    MESSAGE="This usually means a group is already created and is not an issue."
	    ERROR="Bad File."
	    ;;
    esac

    if [ -n "$ERROR" ];
    then
	err $CODE $ERROR $MESSAGE $FATAL
    fi

    return $CODE
}


####
# Notify if a distribution has successfully been determined
# Arg1 = distribution
####
detection_notify(){
    if [ $# -gt 0 ];
    then
	if [[ "$DISTROS[@]" == *"${1}"* ]];
	then
	    printf "\n\n${Bblue}The ${Bblue}${NAME^} ${Bblue}installer has detected an ${green}%s Linux ${Bblue}distribution.${endcolor}\n"  "${1^}"

	    printf "\n\t${yellow}Cavrn will now install with your package manager.\n\tTo only build the source run ${magenta}make build${yellow} or ${magenta}make examples.${endcolor}\n\n"
	    printf "${blue}Would you like to continue installing ${NAME^}?\n"
	    while true; do
		read -ep "Option: " yn
		printf "${endcolor}"
		case $yn in
		    [Yy]* ) break;;
		    [Nn]* ) exit;;
		    * ) echo "Please answer yes or no.";;
		esac
	    done
	fi
    fi
}




package_(){
    
    if [[ ${ARCH_DISTROS[@]} == *"$DISTRO"* ]];
    then	   
	echo '
#Maintainer:'$MAINTAINER' <'$MAINTAINER_EMAIL'>
_pkgname='$NAME'
pkgver='$VER'
pkgrel='$REL'
pkgname=$_pkgname
pkgdesc="Any easy to use AVR library, written in pure C."
arch=(any)
url="http://bytewise.io/'${NAME}'"
license=("GPLv2")
groups=()
depends=('${ARCH_DEPS[@]}')
makedepends=('${ARCH_MAKE_DEPS[@]}')
optdepends=('${ARCH_OPT_DEPS[@]}')
provides=()
conflicts=()
backup=()
source=()
md5sums=("SKIP")
prepare() {
cd '$TOPDIR'
tar -czf cavrn.3.gz -C doc/man/man3/ .
make build
}
package() {
cd '$TOPDIR'
mkdir -p $pkgdir'$INCLUDE_DIR'

mkdir -p $pkgdir'$DOC_DIR'

cp '${SRC[@]}' $pkgdir'$INCLUDE_DIR'
cp cavrn.3.gz $pkgdir'$DOC_DIR'

}' > PKGBUILD

    else
	exit
    fi
}



####
# install_ - Determine the Linux distro and therefore the likely packager manager.
#+ install accoring to distro.
####
install_() {

    # Notify if the distro is supported
    check_err detection_notify $DISTRO

    # Install the packages if they have been made
    if [[ ${ARCH_DISTROS[@]} == *"$DISTRO"* ]];
    then
	if [  -e PKGBUILD ];
	then
	    # Make package from the PKGBUILD
	    check_err makepkg -s -f  -c --skipinteg --skipchecksums --noconfirm --config makepkg.conf
	    rm PKGBUILD
	    
	    
	    arch_package="$(pwd)/${NAME}-$VER-$REL-any.pkg.tar.xz"

	    chmod 777 $arch_package
	    # Install package with pacman
	    check_err sudo pacman -U "$arch_package" --noconfirm
	    
	    if [ -n "$arch_package" ];
	    then
		rm "$arch_package"
	    fi

	else
	    # Flag a fatal error due to no PKGBUILD
	    err \
		1 \
		"Packaging Incomplete" \
		"The package_() function was not completed properly before calling install_()" \
		"fatal"
	fi
	
    else
	printf "\n${Bred}Unable to install on Operating System:${bred} %s\n\n" "${DISTRO^}"
	printf "${Bblue}Please contact the current maintainer to discuss supporting your distro.\n"
	printf "\t${blue}Maintainer: %s <%s>\n${endcolor}" "$MAINTAINER"  "$MAINTAINER_EMAIL"
	echo	
	exit 0;

    fi

    #Initialize docs
    check_err sudo mandb
    printf "\nThe ${NAME^} installer is done!\n"

}


#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Point of execution ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



{
    #create package for the package manager
    package_
    
    # Install via the package manager
    install_


 
} 2>&1 | tee -a $ERROR_LOG  # Capture the errors to a logfile

# Signify Success
exit 0
