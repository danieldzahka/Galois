#!/bin/bash
#
# Small test cases for each benchmark

set -e

BASE="$(cd $(dirname $0); cd ..; pwd)"

if [[ ! -e Makefile ]]; then
  echo "Execute this script from your build directory" 1>&2
  exit 1
fi

run() {
  cmd="$@"
  echo -en '\033[1;31m'
  echo -n "$cmd"
  echo -e '\033[0m'
  $cmd
}

run apps/delaunaytriangulation/delaunaytriangulation -t 2 ${BASE}/inputs/meshes/r10k.node
run apps/delaunayrefinement/delaunayrefinement -t 2 ${BASE}/inputs/meshes/r10k.1
run apps/barneshut/barneshut -t 2 gen 1000 1 0

echo -en '\033[1;32m'
echo -n ALL OK
echo -e '\033[0m'
