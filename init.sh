#!/bin/bash

CURRENT_DIR=$(cd $(dirname $0); pwd)

function get_toolchain()
{
  mkdir -p host-tools
  toolchain_url="https://sophon-file.sophon.cn/sophon-prod-s3/drive/23/03/07/16/host-tools.tar.gz"
  echo "toolchain_url: ${toolchain_url}"
  toolchain_file=${toolchain_url##*/}
  echo "toolchain_file: ${toolchain_file}"

  wget ${toolchain_url} -O ${toolchain_file}
  if [ $? -ne 0 ]; then
    echo  "Failed to download ${toolchain_url} !"
    exit 1
  fi

  if [ ! -f ${toolchain_file} ]; then
    print_err "${toolchain_file} not found!"
    exit 1
  fi

  echo "Extracting ${toolchain_file}..."
  tar -xf ${toolchain_file}

  if [ $? -ne 0 ]; then
    echo "Extract ${toolchain_file} failed!"
    exit 1
  fi

  [ -f ${toolchain_file} ] && rm -rf ${toolchain_file}
}

get_toolchain

git submodule update --init --recursive
