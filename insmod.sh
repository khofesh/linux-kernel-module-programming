#!/bin/bash

# Check if the user is root
if [[ $EUID -ne 0 ]]; then
  echo "You must be root to run this script."
  exit 1
fi

# Get the module name from the command line argument
module_name=$1

# Install the module
sudo insmod $module_name



