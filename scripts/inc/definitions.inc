TOPDIR="$(pwd)"

SCR_DIR="${TOPDIR}/scripts"
SCR_INC="${SCR_DIR}/inc"
SCR_USR="${SCR_DIR}/usr"

BASENAME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"


INCLUDE_DIR="/usr/include/${NAME}"
LIB_DIR="/usr/lib"
BIN_DIR="/usr/bin"
MOD_DIR="/lib/modules/$(uname -r)"
MODCONF_DIR="/etc/modprobe.d/"
DOC_DIR="/usr/share/man/${MAN_SEC}"



function ctrl_c() {
    printf "${endcolor}\n\n"
    exit 0
}


show_usage(){
   source "${SCR_USR}/usage_content.inc"
}
