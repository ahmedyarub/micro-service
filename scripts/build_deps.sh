#!/bin/sh
cd /tmp
git clone https://github.com/Microsoft/cpprestsdk
cd cpprestsdk
git submodule update --init -- Release/libs/websocketpp
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_SAMPLES=OFF
make -j4
sudo make install
rm -Rf /tmp/cpprestsdk

cd /tmp
git clone git://github.com/SOCI/soci.git
mkdir soci/build
cd soci/build
cmake -DWITH_SQLITE3=ON -DSOCI_TESTS=OFF -DSOCI_CXX_C11=ON ..
make -j4
sudo make install
rm -Rf /tmp/soci

cd /tmp
git clone https://github.com/Cylix/cpp_redis.git
cd cpp_redis
git submodule init && git submodule update
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
sudo make install
rm -Rf /tmp/cpp_redis