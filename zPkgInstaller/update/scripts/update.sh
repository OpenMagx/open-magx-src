#!/bin/sh

cd /ezxlocal/download/mystuff/.system/zPkgInstaller

killall zPkgInstaller
rm zPkgInstaller
mv ./zPkgInstaller_up ./zPkgInstaller

showNotify "PEManager updated!"
