#!/bin/sh
################################################################################
# Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2009 Krell Institute All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; either version 2 of the License, or (at your option) any later
# version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA  02111-1307  USA
################################################################################

if [ "$OPENSS_PREFIX" = "" ]
then
  echo "OPENSS_PREFIX not set."
  echo "For oss developers that's usually .../GUI/plugin/lib/openspeedshop"
  echo "- or -"
  echo "export OPENSS_PREFIX=$OPENSS_PLUGIN_PATH/../.."
  if [ "$OPENSS_PLUGIN_PATH" != "" ]
  then
    export OPENSS_PREFIX=$OPENSS_PLUGIN_PATH/../..;
    echo "WARNING: Defaulting to developers location..."
  fi 
#  exit
fi
if test -d plugins/panels
then
  configure --prefix=$OPENSS_PREFIX;make uninstall;make install;make dist;
else
  echo NOTE: This must be run from the 'current' directory...
fi
