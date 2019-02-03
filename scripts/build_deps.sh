#!/bin/sh
JOBS=${JOBS:-`cat /proc/cpuinfo | grep processor | wc -l`}

mkdir -p built_deps
mkdir -p deps

if [ ! -d "built_deps/cpprestsdk" ]; then
    cd deps
    git clone https://github.com/Microsoft/cpprestsdk
    cd cpprestsdk
    git submodule update --init -- Release/libs/websocketpp
    cd ../../built_deps
    mkdir -p cpprestsdk && cd cpprestsdk
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_SAMPLES=OFF ../../deps/cpprestsdk
    make -j${JOBS}
else
    cd built_deps/cpprestsdk/
fi
sudo make install
cd ../../

if [ ! -d "built_deps/soci" ]; then
    cd deps
    git clone git://github.com/SOCI/soci.git
    cd ../built_deps
    mkdir -p soci && cd soci
    cmake -DWITH_SQLITE3=ON -DSOCI_TESTS=OFF -DSOCI_CXX_C11=ON ../../deps/soci
    make -j${JOBS}
else
    cd built_deps/soci/
fi
sudo make install
cd ../../

if [ ! -d "built_deps/cpp_redis" ]; then
    cd deps
    git clone https://github.com/Cylix/cpp_redis.git
    cd cpp_redis
    git submodule init && git submodule update
    cd ../../built_deps
    mkdir -p cpp_redis && cd cpp_redis
    cmake -DCMAKE_BUILD_TYPE=Release ../../deps/cpp_redis
else
    cd built_deps/cpp_redis/
fi
make -j${JOBS}
sudo make install
cd ../../