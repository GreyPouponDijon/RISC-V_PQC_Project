#!/usr/bin/env bash
# Script: create_venv.sh
# Purpose: Create a Python virtual environment if it doesn't exist

# Name of the virtual environment directory
VENV_DIR="venv"

# Python executable to use (change if needed)
PYTHON_BIN="python3"

# Check if Python is installed
if ! command -v "$PYTHON_BIN" &>/dev/null; then
    echo "Error: $PYTHON_BIN is not installed or not in PATH."
    exit 1
fi

# Create venv if it doesn't exist
if [ ! -d "$VENV_DIR" ]; then
    echo "Creating virtual environment in '$VENV_DIR'..."
    if "$PYTHON_BIN" -m venv "$VENV_DIR"; then
        echo "Virtual environment created successfully."
    else
        echo "Failed to create virtual environment."
        exit 1
    fi
else
    echo "ℹ️ Virtual environment already exists in '$VENV_DIR'."
fi

# Activate the virtual environment
# (Uncomment if you want to auto-activate after creation)
source "$VENV_DIR/bin/activate"
pip install --upgrade setuptools
pip install IntelHex
cd pyocd
pip install .
cd -
deactivate
