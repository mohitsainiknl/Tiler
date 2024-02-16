#!/bin/bash

set -e
set -x

BASEDIR=$(dirname "$0")
pushd "$BASEDIR"

# Check if Python is installed
if command -v python3 >/dev/null 2>&1; then
    sudo python3 Scripts/setup_tiler_project.py "$1"
else
    echo "python is also not available."
fi

