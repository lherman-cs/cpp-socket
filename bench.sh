#!/bin/bash

ROOT_DIR=$(dirname $(realpath $0))
CLIENT_PATH=${ROOT_DIR}/build/bin/client

# Server's configurations
SERVER_IP=130.127.49.44       # koala1.cs.clemson.edu
PORT=30000

# Common
REPEAT=10

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
  echo "transfer_size: ${transfer_size} chunk_size: ${CONST_CHUNK_SIZE}"
  for i in `seq ${REPEAT}`
  do
    ${CLIENT_PATH} ${SERVER_IP} ${PORT} ${CONST_CHUNK_SIZE} | awk '{print $6}'
  done

  echo ""  
  PORT=$(( ${PORT} + 1 ))
done

# Vary the chunk size and hold the transfer size
for (( chunk_size = ${LOW_CHUNK_SIZE}; chunk_size <= ${HIGH_CHUNK_SIZE}; chunk_size *= 10 ))
do
  echo "transfer_size: ${CONST_TRANSFER_SIZE} chunk_size: ${chunk_size}"
  for i in `seq ${REPEAT}`
  do
    ${CLIENT_PATH} ${SERVER_IP} ${PORT} ${chunk_size} | awk '{print $6}'
  done
  
  echo ""
  PORT=$(( ${PORT} + 1 ))
done