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
