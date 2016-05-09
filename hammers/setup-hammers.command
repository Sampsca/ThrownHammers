#!/bin/sh

command_path=${0%/*}
cd "$command_path"
./setup-hammers
exit 0
