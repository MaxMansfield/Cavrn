#!/bin/bash
USING_COLOR=false
if [ -t 1 ]; then

    # see if it supports colors...
    ncolors=$(tput colors)

    if test -n "$ncolors" && test $ncolors -ge 8; then
        bold="$(tput bold)"
        underline="$(tput smul)"
        standout="$(tput smso)"
        endcolor="$(tput sgr0)"
        black="$(tput setaf 0)"	
        red="$(tput setaf 1)"	
        green="$(tput setaf 2)"	
        yellow="$(tput setaf 3)"	
        blue="$(tput setaf 4)"
        magenta="$(tput setaf 5)"
        cyan="$(tput setaf 6)"
        white="$(tput setaf 7)"

	USING_COLOR=true
    fi
fi


####
# Checks if using a color prompt and then draws an ascii or colored line to fill the rest of the screen.
# Arg 1 - The character to draw when using ascii
# Arg 2 - The color to draw when using
horizontal_line() {
    argc_=2

    exec < /dev/tty
    oldstty=$(stty -g)
    stty raw -echo min 0
    # on my system, the following line can be replaced by the line below it
    echo -en "\033[6n" > /dev/tty
    # tput u7 > /dev/tty    # when TERM=xterm (and relatives)
    IFS=';' read -r -d R -a pos
    stty $oldstty
    # change from one-based to zero based so they work with: tput cup $row $col
    row=$((${pos[0]:2} - 1))    # strip off the esc-[
    col=$((${pos[1]} - 1))
    
    if [ $# == $argc_ ]; 
    then
	total_=`tput cols`
	amount_=$((total_-col))
	char_="$1"
	color_="$2"
	if [ ${#char_} -eq 1 ];
	then
	    if [ $USING_COLOR ];
	    then

		printf "${standout}`echo ${!color_}`%${amount_}s${endcolor}\n" | tr ' ' ' ' #${standout}$color${endcolor}
	    else
		printf "%`tput cols`s\n" | tr ' ' "$char_"
	    fi
	fi
    else
	return 1
    fi   
}

