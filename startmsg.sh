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
./MsgHub1 &
cd -
sleep 3
