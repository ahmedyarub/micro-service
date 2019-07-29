FROM ubuntu:bionic

RUN apt update && \
    apt install software-properties-common -y && \
    add-apt-repository ppa:ubuntu-toolchain-r/test -y && \
    apt update && \
    apt install g++-9 gcc-9 curl unzip tar wget build-essential git openssl libssl-dev pkg-config -y

RUN cd /tmp && \
    wget https://cmake.org/files/v3.14/cmake-3.14.5-Linux-x86_64.sh && \
    wget -qO- https://repo1.maven.org/maven2/org/flywaydb/flyway-commandline/5.2.4/flyway-commandline-5.2.4-linux-x64.tar.gz | tar xvz && \
    ln -s `pwd`/flyway-5.2.4/flyway /usr/local/bin && \
    git clone git://github.com/microsoft/vcpkg.git && \
    git clone git://github.com/SOCI/soci.git

RUN rm /usr/bin/gcc && \
    ln -s /usr/bin/gcc-9 /usr/bin/gcc && \
    rm /usr/bin/g++ && \
    ln -s /usr/bin/g++-9 /usr/bin/g++

RUN cd /tmp && \
    mkdir /opt/cmake && \
    sh cmake-3.14.5-Linux-x86_64.sh --prefix=/opt/cmake --skip-license && \
    ln -s /opt/cmake/bin/cmake /usr/bin/cmake

RUN cd /tmp && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh

RUN cd /tmp/vcpkg && \
    export VCPKG_TRIPLET=x64-linux && \
    echo '\nset(VCPKG_BUILD_TYPE release)' >> ./triplets/${VCPKG_TRIPLET}.cmake && \
    ./vcpkg install http-parser fmt restinio clara cpp-redis json-dto SQLite3 boost-lexical-cast boost-math

RUN cd /tmp && \
    mkdir soci/build && \
    cd soci/build && \
    cmake -DCMAKE_TOOLCHAIN_FILE=/tmp/vcpkg/scripts/buildsystems/vcpkg.cmake -DWITH_SQLITE3=ON -DWITH_MYSQL=OFF -DSOCI_TESTS=OFF -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
    make -j4 && \
    make install && \
    rm -Rf /tmp/soci

COPY db /tmp/db
COPY src /tmp/src

RUN mkdir /tmp/src/build && \
    cd /tmp/src/build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DCMAKE_TOOLCHAIN_FILE=/tmp/vcpkg/scripts/buildsystems/vcpkg.cmake .. && \
    cd .. && \
    cmake --build ./build --target all

COPY docker/run.sh /tmp/

RUN ["chmod", "+x", "/tmp/run.sh"]

EXPOSE 8088

ENTRYPOINT ["/tmp/run.sh"]
#ENTRYPOINT ["tail", "-f", "/dev/null"]