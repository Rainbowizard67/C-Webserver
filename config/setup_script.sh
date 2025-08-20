#!/bin/bash

sudo apt update

sudo apt install valgrind gdb build-essential libyaml-dev libcyaml-dev -y

ENV_FILE=".env"

cat > "$ENV_FILE" <<EOL

EOL

