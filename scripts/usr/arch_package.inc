echo '
#Maintainer:'$MAINTAINER' <'$MAINTAINER_EMAIL'>
_pkgname='${NAME}'
pkgver='${VER}'
pkgrel='${REL}'
pkgname=$_pkgname
pkgdesc="Any easy to use AVR library, written in pure C."
arch=(any)
url="http://bytewise.io/'${NAME}'"
license=("GPLv2")
groups=()
depends=('${ARCH_DEPS[@]}')
makedepends=('${ARCH_MAKE_DEPS[@]}')
optdepends=('${ARCH_OPT_DEPS[@]}')
provides=()
conflicts=()
backup=()
source=()
md5sums=("SKIP")
prepare() {
cd '$TOPDIR'
tar -czf cavrn.3.gz -C doc/man/man3/ .
make build
}
package() {
cd '$TOPDIR'
mkdir -p $pkgdir'$INCLUDE_DIR'

mkdir -p $pkgdir'$DOC_DIR'

cp '${SRC[@]}' $pkgdir'$INCLUDE_DIR'
cp cavrn.3.gz $pkgdir'$DOC_DIR'

}' > PKGBUILD
