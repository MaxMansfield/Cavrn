	source "scripts/inc/definitions.inc"

	need=""
		printf "${yellow}Checking build dependencies with yum...${endcolor}\n"
		for dep in "${RED_MAKE_DEPS[@]} qt5-*"
		do		  
		    # quiet then check for errors
		    yum list installed "$dep" &> /dev/null
		    if [ "$?" != 0 ];
		    then
			need="$need$dep "
		    fi    
		done

if [ -n "$need" ];
then
	check_err sudo yum install "$need" -y
fi 
	# build dirs
	mkdir -p ${TOPDIR}/rpmbuild/{BUILD,SPECS,BUILDROOT,SRPMS,RPMS}
		
	
	# spec file
	echo '
%define name '${NAME}'
%define version '$VER'
%define release '$REL'

Name: %{name}
Version: %{version}
Release: %{release}
BuildRoot: %{_builddir}/%name-root
Summary: A library for making API calls and organizing bytewise I/O member data.
License: GPLv2
URL: http://bytewise.io
Packager: '$MAINTAINER_EMAIL'
BuildRequires: '${RED_MAKE_DEPS[@]}'
Requires:  '${RED_DEPS[@]}'
 
%description
Libnibl is the library backing to the Bytewise I/O task management software, Nibl; which mostly calls out to web APIs and organzes the data accordingly. This separation makes it easier to create different UX for different platforms as well as run autotests on the library.

%build
cd '$TOPDIR'
tar -czf cavrn.3.gz -C doc/man/man3/ .
make build

%install
cd '$TOPDIR'
mkdir -p $RPM_BUILD_ROOT'$INCLUDE_DIR'

mkdir -p $RPM_BUILD_ROOT'$DOC_DIR'

cd '$TOPDIR'
cp '${SRC[@]}' $RPM_BUILD_ROOT'$INCLUDE_DIR'
cp cavrn.3.gz $RPM_BUILD_ROOT'$DOC_DIR'


%files
%defattr(-,root,root)
'$DOC_DIR'
'$INCLUDE_DIR' 
' > "${TOPDIR}/rpmbuild/SPECS/${NAME}.spec"

	printf "\n${yellow}Building an RPM package...${endcolor}\n"
	
	cd rpmbuild
	# build the package
	printf "${blue}"
	# Don't check_err, reports a 1 at finish.
	rpmbuild --define "_topdir ${TOPDIR}/rpmbuild" -bb SPECS/${NAME}.spec
	printf "${endcolor}"
