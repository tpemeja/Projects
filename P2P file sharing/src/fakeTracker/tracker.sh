#!/bin/bash

coproc nc -l localhost 8090

while read -r cmd; do
  case $cmd in
    d) date ;;
    q) break ;;
    *) echo 'What?'
  esac
done <&"${COPROC[0]}" >&"${COPROC[1]}"

kill "$COPROC_PID"
