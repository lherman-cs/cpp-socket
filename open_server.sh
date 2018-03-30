#!/bin/bash

# This script is to run the server with multiple ports. This is because there is a delay after the 
# program ends to close the port. So, instead of waiting the OS to close it, I'll open multiple
# ports at the same time.

ROOT_DIR=$(dirname $(realpath $0))
SERVER_PATH=${ROOT_DIR}/build/bin/server

# Server port configuration
PORT=30000

# Part 1 variables
CONST_CHUNK_SIZE=1000000      # 1 Mbytes
LOW_TRANSFER_SIZE=10000       # 10 Kbytes
HIGH_TRANSFER_SIZE=1000000000 # 1 Gbytes

# Part 2 variables
CONST_TRANSFER_SIZE=1000000000 # 1 Gbytes
LOW_CHUNK_SIZE=1000            # 1 Kbytes
HIGH_CHUNK_SIZE=10000000       # 10 Mbytes


# Vary the transfer size and hold the chunk size
for (( transfer_size = ${LOW_TRANSFER_SIZE}; transfer_size <= ${HIGH_TRANSFER_SIZE}; transfer_size *= 10 ))
do
  echo "open at port ${PORT} with transfer_size: ${transfer_size} chunk_size: ${CONST_CHUNK_SIZE}"
  ${SERVER_PATH} ${PORT} ${transfer_size} ${CONST_CHUNK_SIZE} 2>&1 >> log.txt &
  PORT=$(( ${PORT} + 1 ))
done

# Vary the chunk size and hold the transfer size
for (( chunk_size = ${LOW_CHUNK_SIZE}; chunk_size <= ${HIGH_CHUNK_SIZE}; chunk_size *= 10 ))
do
  echo "open at port ${PORT} with transfer_size: ${transfer_size} chunk_size: ${chunk_size}"
  ${SERVER_PATH} ${PORT} ${CONST_TRANSFER_SIZE} ${chunk_size} 2>&1 >> log.txt &
  PORT=$(( ${PORT} + 1 ))
done