#!/usr/bin/env bash
set -euo pipefail
chmod +x build.sh
    ./build.sh
scp build/gpioled.ko root@192.168.1.2:/userdata
