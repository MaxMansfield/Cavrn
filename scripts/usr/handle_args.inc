INSTALL_ONLY=false
PACKAGE_ONLY=false
NO_CONFIRM__=false
s_count=0
while [[ $# -gt 0 ]]
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
	-d|--doc)
	    if [ -d $2 ];
	    then
		DOC_DIR="$2"
		printf "\n\t${green}Doc Directory:${blue} %s${endcolor}\n" $(pwd)/$BUILD_DIR
	    else
		printf "\n${Bred}The Documentation directory [${bred}%s${Bred}] does not exist.${endcolor}\n" $(pwd)/$2
		exit $ENOENT
	    fi
	    shift
	    ;;
	-h|--help)
            show_usage
	    exit 0
	    shift
	    ;;
	--default)
	    EXMPL_DIR="examples"
	    SRC[0]="./main.c"
	    BUILD_DIR="build"
	    DOC_DIR="doc"
	    printf "${green}Default settings successfully applied.\n${endcolor}"
	    ;;
	*)
	    show_usage
	    echo $1 | egrep -q "^--*"
	    
	    if [ $? == 0 ];
	    then
		ARG="$1"
	    else
		echo $2 | egrep -q "^-*"
		if [ $? == 1 ];
		then
		   ARG="$2"
		fi
	    fi
	    
	    printf "\n${Bred}Invalid Argument:${endcolor} ${bred}%s ${endcolor}\n" $ARG
	    exit $EINVAL
	    ;;
    esac
    shift
done



