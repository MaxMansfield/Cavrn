#!/bin/bash

# ignore hidden files when finding

GREP="grep --silent"
SUPPORTED="supported_mcus.list"
SETTINGS="../settings.inc"
EXAMPLES="../examples"


### check_examples ##
# This function should be called at first with no argument, it will then call itself to build the examples.
###
check_examples()
{

    # if this is the first run otherwise go recursive
    if [ "$1" == "" ];
    then
	WORKDIR=$EXAMPLES
    else 
	WORKDIR="$1"
    fi
    for dir in `find $WORKDIR -not -path '*/\.*'  -type d`
    do
	if [ -d $dir ];
	then
	    echo [Checking $dir for complete examples]
	    if [ -e $dir/Makefile ] && [ -L $dir/main.c ];
	    then
		echo [building $dir example]
		make -C $dir
	    else
		echo [No Makefile or main.c found in $dir recusrsing]
		echo; echo;
		check_examples $dir/*
	    fi
	fi
    done

}

build_for_all()
{
    make -C ../ clean

    # Read all the supported MCUs from the list
    while read mcu
    do

	echo;echo;
	echo  :~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~:
	echo  :~[Now building Cavrn for the $mcu microcontroller]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~:
	echo  :~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~:
	echo;

	#Replace the current MCU in the settings with one on the list
	sed -i 's/^DEVICE  :=.*/DEVICE  := '$mcu/g $SETTINGS

	#Make with this MCU
	make -C ../ examples && check_examples  && make -C ../ clean

	RET=$?

    done < "$SUPPORTED"

    # exit last returned code
    exit $RET
}

#Test build the library for all supported GPUS
build_for_all


# exit without an argument will do the same but lets be explicit
exit $?
