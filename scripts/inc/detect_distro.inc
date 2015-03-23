#### Arch Based distros
ARCH="arch"
MANJ="manjaro"
ANTE="antergos"

ARCH_DISTROS[0]=$ARCH
ARCH_DISTROS[1]=$MANJ
ARCH_DISTROS[2]=$ANTE
APKG_="$(pwd)/${NAME}-$VER-$REL-any.pkg.tar.xz"

#### Debian Based Distros
DEBIAN="debian"
UBUNTU="ubuntu"
ELEMENT="elementary"
DPKG_="${NAME}_${VER}_all.deb"

DEB_DISTROS[0]=$DEBIAN
DEB_DISTROS[1]=$UBUNTU
DEB_DISTROS[2]=$ELEMENT

#### red Hat based distros
FEDORA="fedora"
CENTOS="centos"
RPKG_="rpmbuild/RPMS/$(uname -i)/${NAME}-$VER-$REL.$(uname -i).rpm"

RED_DISTROS[0]=$FEDORA
RED_DISTROS[1]=$CENTOS



# Information for obtaining the distro
OSFILE="/etc/os-release"
if [[ -f "$OSFILE" ]];
then
    DISTRO="$(egrep '^ID=' $OSFILE | egrep -o  '[[:alpha:]]{3,}')"
    
fi


DISTRO_COUNT=0
for distro in ${ARCH_DISTROS[@]}
do
    DISTROS[$DISTRO_COUNT]=$distro
    DISTRO_COUNT=$((DISTRO_COUNT + 1))
    
done

for distro in ${DEB_DISTROS[@]}
do
    DISTROS[$DISTRO_COUNT]=$distro
    DISTRO_COUNT=$((DISTRO_COUNT + 1))
done

for distro in ${RED_DISTROS[@]}
do
    DISTROS[$DISTRO_COUNT]=$distro
    DISTRO_COUNT=$((DISTRO_COUNT + 1))
done


if [[ ${ARCH_DISTROS[@]} == *"$DISTRO"* ]];
then	   
    FILE_NAME="arch"
    
elif [[ ${DEB_DISTROS[@]} == *"$DISTRO"* ]];
then
    FILE_NAME="debian"
elif [[ ${RED_DISTROS[@]} == *"$DISTRO"* ]];
then
    FILE_NAME="redhat"
fi

DISTRO_INSTALL="${FILE_NAME}_install.inc"
DISTRO_PACKAGE="${FILE_NAME}_package.inc"


####
# Warn that this program cannot be installed
####
incompatible_message()
{
    printf "\n${Bred}Unable to install on Operating System:${bred} %s\n\n" "${DISTRO^}"
    printf "${Bblue}Please contact the current maintainer to discuss supporting your distro.\n"
    printf "\t${blue}Maintainer: %s <%s>\n${endcolor}" "$MAINTAINER"  "$MAINTAINER_EMAIL"
    echo
}


####
# Notify if a distribution has successfully been determined
# Arg1 = distribution
####
detection_notify(){
    if [ $# -gt 0 ];
    then
	if [[ "${DISTROS[@]}" == *"${1}"* ]];
	then	    
	    printf "\n${blue}The ${yellow}%s Linux ${blue}distribution has been detected.${endcolor}\n"  "${1^}"

	    printf "\n\t${yellow}${NAME^} will now install with your package manager.\n\n"
	    printf "${blue}Would you like to continue installing ${NAME^}?\n"
	    while true; do		    
		read -ep "Option:${yellow} " yn
		printf "${endcolor}"
		case $yn in
		    [Yy]* ) break;;
		    [Nn]* ) exit;;
		    * ) echo "Please answer yes or no.";;
		esac
	    done
	else
	    return $EINVAL
	fi
    else
	return $EINVAL
    fi
}

list_distros(){
    color=30
    for distro in ${DISTROS[@]}
    do

	color=$((color + 1));
	# Alternate bold and normal
	weight=$(expr $color % 2 == 0)

	
	if [ $color -gt 35 ];
	then
	    color=30
	fi

	printf "\n\t\t\e[${weight};${color}m${distro}${endcolor}\n"
    done

}
