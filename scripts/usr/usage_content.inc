
printf "${blue}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${endcolor}\n"
printf "\t\t\t\t${Bblue}Usage${endcolor}\n"
printf "${blue}~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~${endcolor}\n\n"
printf "${magenta}Provide ${NAME^} with arguments as to where it should look for install files\n"
printf "or simply use the ${Bmagenta}--default ${magenta}command.${endcolor}\n"

printf "\n${magenta} %s [option] [value] ${endcolor}\n\n" $BASENAME
printf "\n${green}Parameters:${endcolor}\n\t"

#--example
printf "\n\t ${Bmagenta}-e${green},${Bmagenta}--example [directory]\n\t\t${blue}Takes the directory of the examples as an argument.${endcolor}\n"

#--source
printf "\n\t ${Bmagenta}-s${green},${Bmagenta}--source [filepaths] \n\t\t${blue}Takes the paths of the source files to be installed.${endcolor}\n" 

#--build
printf "\n\t ${Bmagenta}-b${green},${Bmagenta}--build [directory]\n\t\t${blue}Takes the directory of the examples as an argument.${endcolor}\n"

#--help
printf "\n\t ${Bmagenta}-h${green},${Bmagenta}--help\n\t\t${blue}Show this page${endcolor}\n" 


#--default
printf "\n\t ${Bmagenta}--default\n\t\t${blue}Uses the default hard-coded directory paths\n${endcolor}"

#--package-only
printf "\n\t ${Bmagenta}--package-only\n\t\t${blue}Only make a package, do not install.\n${endcolor}"

#--install-only
printf "\n\t ${Bmagenta}--install-only\n\t\t${blue}Install a previous or custom package.\n\t\tUseful after using ${magenta}--package-only ${blue}or${magenta} --build-all.\n${endcolor}"

#--build-all
printf "\n\t ${Bmagenta}--build-all\n\t\t${blue}Make packages for every distribution.\n${endcolor}"

#--spoof-distro
printf "\n\t ${Bmagenta}--spoof-distro [distro]\n\t\t${blue}Force a distribution to be built against.\n${endcolor}"

#--run-tests
printf "\n\t ${Bmagenta}--run-tests\n\t\t${blue}Do not confirm before using test suite.\n${endcolor}"

#--skip-tests
printf "\n\t ${Bmagenta}--skip-tests\n\t\t${blue}Do not run the test suite.\n${endcolor}"

#--noconfirm
printf "\n\t ${Bmagenta}--noconfirm\n\t\t${blue}Run default settings and skip promts. Fully automated.\n${endcolor}"

#--supported
printf "\n\t ${Bmagenta}--supported\n\t\t${blue}List the supported distribtuions.\n${endcolor}"

printf "${blue}\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n${endcolor}"
