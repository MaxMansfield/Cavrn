
    if [[ ${DISTROS[@]} == *"$DISTRO"* ]];
    then	   
	source "${SCR_USR}/${DISTRO_PACKAGE}"
    else
	exit
    fi

    if [ ! -e $APKG__ ] && {[ ! -e $DPKG_ ] && [ ! -e $RPKG__ ]};
    then
	# Flag a fatal error 
	err \
	    1 \
	    "Packaging Incomplete" \
	    "The package_() function was not completed properly before calling install_()" \
	    "${NAME^}-Install->install(): package_() not called before install_(). No packages found." \
	    "install_()" \
	    "fatal"
    else


	# Install the packages if they have been made
	if [[ ${DISTROS[@]} == *"$DISTRO"* ]];
	then
	    source "${SCR_USR}/${DISTRO_INSTALL}"
	    printf "\n${green}${NAME^} has finished installing.\n${endcolor}"
	else
	    incompatible_message
	    exit 0;
	fi
    fi

    source "${SCR_USR}/test.inc"








