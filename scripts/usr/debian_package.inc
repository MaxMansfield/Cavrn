LIBFILE=$DEBLIB
	write_wrapper
	check_err sudo apt-get update -y &> /dev/null
	check_err sudo apt-get install "$need" -y
	check_err sudo apt-get -f install -y
	
	# The Debian package directory
	mkdir -p debian/DEBIAN

	# Where to store the executables symlink
	mkdir -p debian$SYMDIR

	# The modprobe directory to hold the config file for the driver
	mkdir -p debian$MODDIR
	cp $TOPDIR/$MODCONF debian$MODDIR

	# The installation directory of CorePack
	mkdir -p debian$INSTALLDIR
	cp -r bin/* debian$INSTALLDIR

	# The location of desktop entries
	mkdir -p debian$ENTRYDIR
	cp $ENTRYNAME debian$ENTRYDIR
	
	# Make control file
	echo 'Package:' $RUNSCRIPT'
Architecture: all
Section: electronics
Priority: extra
Version:'$VER'
Maintainer: '$MAINTAINER' <'$MAINTAINER_EMAIL'> 
Depends: '${DEB_DEPS[@]}'
Homepage: http://fabuloussilicon.com
Description: CorePack is an FPGA tool designed by Fabulous Silicon for use with their products.' > debian/DEBIAN/control
	
	#dpkg is pick about permissions
	sudo chmod -R 755 debian/

	# create the package
	check_err dpkg --build debian
	
	# move the package so apt can see it
	
	mv debian.deb $DPKG_