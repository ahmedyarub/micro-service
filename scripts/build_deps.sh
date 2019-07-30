#!/bin/sh
JOBS=${JOBS:-`cat /proc/cpuinfo | grep processor | wc -l`}

mkdir -p built_deps
mkdir -p deps

if [ ! -f "/usr/local/bin/flyway" ]
then
    cd built_deps
    wget -qO- https://repo1.maven.org/maven2/org/flywaydb/flyway-commandline/5.2.4/flyway-commandline-5.2.4-linux-x64.tar.gz | tar xvz
    sudo ln -s $(pwd)/flyway-5.2.4/flyway /usr/local/bin
    cd "${TRAVIS_BUILD_DIR}"
fi
flyway -locations=filesystem:./db/migrations/sql/ -url=jdbc:sqlite:/tmp/microservice.db -user= -password=  migrate

if [ ! -d "built_deps/vcpkg" ]
then
    cd built_deps
    git clone git://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    export VCPKG_TRIPLET=x64-linux && \
    echo '\nset(VCPKG_BUILD_TYPE release)' >> ./triplets/${VCPKG_TRIPLET}.cmake
    ./vcpkg install http-parser fmt restinio clara cpp-redis json-dto SQLite3 boost-lexical-cast boost-math
    cd "${TRAVIS_BUILD_DIR}"
fi

if [ ! -d "built_deps/soci" ]
then
    cd deps
    git clone git://github.com/SOCI/soci.git
    cd ../built_deps
    mkdir -p soci && cd soci
    cmake -DCMAKE_TOOLCHAIN_FILE=${TRAVIS_BUILD_DIR}/built_deps/vcpkg/scripts/buildsystems/vcpkg.cmake -DWITH_SQLITE3=ON -DWITH_MYSQL=OFF -DSOCI_TESTS=OFF -DCMAKE_INSTALL_PREFIX:PATH=/usr ../../deps/soci/
    make -j${JOBS}
else
    cd built_deps/soci/
fi
sudo make install
cd "${TRAVIS_BUILD_DIR}"