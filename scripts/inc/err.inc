# Error Codes
OKAY=0
EPERM=1      # Operation not permitted
ENOENT=2     # No such File or directory
ENXIO=6      # No such device or address
EBADF=9      # Bad file number
EINVAL=22    # Invalid argument 
ENETDOWN=100 # Network is down *thrown by apt when package is not found

ERROR_LOG="${TOPDIR}/${NAME^}-${DISTRO}-$(uname -m)-($(date +%T)).log"


####
# The main error function. To be invoked by itself or by check_err
# Arg 1 - Exit Code
# Arg 2 - Error String
# Arg 3 - Fix Message
# Arg 4 - Resulting Stderr
# Arg 5 - line executed
# Arg 6 - Fatal or not 
####
err(){
     # redirect to stderr
	if [ $#  -gt 4 ];
	then
	    if [ $# -lt 6 ];
	    then
		FATAL=""
	    else
		FATAL="$6"
	    fi
	    
	    if [ ! -e $ERROR_LOG ];
	    then
		touch $ERROR_LOG
		echo "${NAME^} Error Log v1" > "$ERROR_LOG"
		echo "`uname -a`" >> "$ERROR_LOG"
	    fi

	    horizontal_line " " "red"
            printf "${red}${bold}%s %s error while running on ${endcolor} ${bold}${blue}%s ${endcolor}" "${FATAL^}" "$BASENAME" "${DISTRO^}" 
            horizontal_line "=" "red" 
            horizontal_line "-" "red"

	    printf "\n${standout}${bold}${red}Encountered%s error (%d)" "${FATAL}"  "$1" 
	    printf "\n\t${endcolor}${yellow}%s\n\t${red}%s${endcolor}\n\n" "$2" "$4"
	    
	    printf "${red}${standout}${bold}During execution of${endcolor}\n\t${yellow}%s${endcolor}\n" "$5"
	    
	    printf "\n${standout}${bold}${blue}Maintainer:${endcolor}\n\t${blue}%s <%s>\n\n" "$MAINTAINER" "$MAINTAINER_EMAIL"
	    printf "${standout}${bold}Log File:${endcolor}${blue}\n\t%s\n${endcolor}\n"  "$ERROR_LOG"
	    
	    printf "\n${bold}${blue}%s then please retry the installation.\n\n${endcolor}" "$3"
	    
            horizontal_line "-" "red"
	    printf "${bold}${red}If the problem persists contact the maintainer with the listed log file. ${endcolor}"
            horizontal_line "=" "red"
	    horizontal_line " " "red"
	    
	    
	    if [ -n "$6" ];
	    then
		printf "Exiting due to fatal error %d...\n" "$1" 1>&2
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
    {
   # get args
    line="$@"

    # run args
    err_file="err.err"

    if [ ! -e  "$err_file" ];
    then
	touch "$err_file"
    fi
    $line #2> "$err_file"
    
    # get code
    code="$?"
    error="$(cat ${err_file})"

    #do something about it.
    case $code in
	$OKAY )
         return $code
	;;
	$EPERM )
	    MESSAGE="Make sure the same version isn't installed and you haven't changed the installation directory"
	    ERROR="Operation not permitted. "
	    FATAL="fatal"
	    ;;
	$ENETDOWN )
	    MESSAGE="Check your network connection and make sure you arent using you package manager"
	    ERROR="Network not found."
	    FATAL="fatal"
	    ;;
	$ENOENT )
	    MESSAGE="Ensure that the installation directory has not been altered"
	    ERROR="No such file or directory."
	    FATAL="fatal"
	    ;;
	$ENXIO )
	    MESSAGE="This usually means a group or user does not exist while using the usermod command.You may have trouble running corepack without root access"
	    ERROR="No Address."
	    ;;
	$EBADF )
	    MESSAGE="This usually means a group is already created and is not an issue"
	    ERROR="Bad File."
	    ;;
    esac

    
    if [ -n "$ERROR" ];
    then
	err "$code" "${ERROR} " "$MESSAGE" "$error"  "$line" "$FATAL" 
	
    fi

    if [ -e  "$err_file" ];
    then
	rm "$err_file"
    fi
    
    return $code
    } 1>&2
}
