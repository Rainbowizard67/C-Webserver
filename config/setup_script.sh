#!/bin/bash

sudo printf "%b\n" "\e[0;34mDownloading and Installing dependencies...\e[0m"

sudo apt update
sudo apt install valgrind gdb build-essential libyaml-dev libcyaml-dev -y

sudo printf "%b\n" "\e[0;34mFinished dependency install\e[0m"

ENV_FILE="scurry.env"

cat > "$ENV_FILE" <<EOL
SCURRY_CONFIG_DIR

EOL

