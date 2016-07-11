#!/bin/sh
cd TrustCA
./TrustCA &
cd -
sleep 3
cd TrustHub
./TrustHub &
cd -
sleep 3
cd TrustHub1
./TrustHub &
cd -
sleep 3
cd TrustHub2
./TrustHub &
cd -
