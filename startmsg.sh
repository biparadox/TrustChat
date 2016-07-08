#!/bin/sh
cd MsgServer
./MsgServer &
cd -
sleep 3
cd MsgHub
./MsgHub &
cd -
sleep 3
cd MsgHub1
./MsgHub &
cd -
sleep 3
cd MsgHub2
./MsgHub &
cd -
