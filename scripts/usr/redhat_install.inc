
check_err sudo yum update -y

need=""
for dep in "${RED_DEPS[@]}"
do
    sudo yum list installed $dep 2>&1 /dev/null
    if [ $? != 0 ];
    then
        need="$need $dep"
    fi

done

if [ -n "$need" ];
then
    check_err sudo yum install "$need" -y	
fi
sudo ln -sf /usr/bin/qmake-qt5 /usr/bin/qmake

cd $TOPDIR
check_err sudo rpm -i $RPKG_ 

cd $TOPDIR && rm -r rpmbuild

