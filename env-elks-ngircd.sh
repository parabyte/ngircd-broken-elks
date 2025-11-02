#!/usr/bin/env bash

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
	echo "Please source this script: . ./env-elks-ngircd.sh" >&2
	exit 1
fi

__NGIRCD_ELKS_OLD_OPTS=$(set +o)
set -e

if [[ -n "${NGIRCD_ELKS_ENV:-}" ]]; then
	eval "$__NGIRCD_ELKS_OLD_OPTS"
	unset __NGIRCD_ELKS_OLD_OPTS
	return
fi

SCRIPT_DIR=$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd)
TOPDIR=${TOPDIR:-$(cd "$SCRIPT_DIR/.." && pwd)}
export TOPDIR

if [[ -z "${WATCOM:-}" ]]; then
	if [[ -d /opt/openwatcom ]]; then
		export WATCOM=/opt/openwatcom
	else
		export WATCOM=/opt/watcom
	fi
fi

ngircd_add_path() {
	case ":$PATH:" in
		*":$1:"*) ;;
		*) PATH="$1:$PATH" ;;
	esac
}

if [[ -d "$WATCOM/binl64" ]]; then
	ngircd_add_path "$WATCOM/binl64"
fi
if [[ -d "$WATCOM/binl" ]]; then
	ngircd_add_path "$WATCOM/binl"
fi
export PATH

# shellcheck source=/dev/null
source "$TOPDIR/libc/watcom.model"
export MODEL=${MODEL:-l}
unset LIBC

if [[ -z "${INCLUDE:-}" ]]; then
	export INCLUDE="$TOPDIR/libc/include;$TOPDIR/include"
fi

export NGIRCD_ELKS_ENV=1

eval "$__NGIRCD_ELKS_OLD_OPTS"
unset __NGIRCD_ELKS_OLD_OPTS
