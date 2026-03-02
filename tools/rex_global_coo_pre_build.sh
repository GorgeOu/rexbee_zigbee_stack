#!/bin/bash
echo "******************** pre build *********************"
echo "coo pre build para (1)$1"
rm -rf "$1/boot.link"
cp -f "$1/app/include/board/8258/boot_coo.link" "$1/boot.link"
echo "**************** end of pre build ******************"