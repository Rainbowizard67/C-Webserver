#!/bin/bash

###Start Function declaration###

find_config() {
    local env_file="$1"
    export SCURRY_CONFIG_DIR="$(pwd)"
    echo
}

###End Function Declaration###

sudo printf "%b\n" "\e[0;34mDownloading and Installing dependencies...\e[0m"

sudo apt update
sudo apt install valgrind gdb build-essential libyaml-dev libcyaml-dev -y

sudo printf "%b\n" "\e[0;34mFinished dependency install\e[0m"

sudo printf "%b\n" "\e[0;34mStarting env file initialization...\e[0m"

ENV_FILE="scurry.env"

cat > "$ENV_FILE" <<EOL
###Scurry Env###

EOL

find_config "$ENV_FILE"

sudo printf "%b\n" "\e[0;34mFinished env file initialization\e[0m"

