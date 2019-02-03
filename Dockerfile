FROM ubuntu:xenial

RUN apt update && \
    apt install wget build-essential cmake git openssl libssl-dev pkg-config libboost-all-dev sqlite3 libsqlite3-dev -y


RUN cd /tmp && \
    wget -qO- https://repo1.maven.org/maven2/org/flywaydb/flyway-commandline/5.2.4/flyway-commandline-5.2.4-linux-x64.tar.gz | tar xvz && \
    ln -s `pwd`/flyway-5.2.4/flyway /usr/local/bin

RUN flyway -locations=filesystem:/tmp/db/migrations/sql/ -url=jdbc:sqlite:/tmp/microservice.db -user= -password=  migrate

RUN cd /tmp && \
    git clone https://github.com/Microsoft/cpprestsdk && \
    cd cpprestsdk && \
    git submodule update --init -- Release/libs/websocketpp && \
    mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_SAMPLES=OFF && \
    make -j4 && \
    make install && \
    rm -Rf /tmp/cpprestsdk

RUN cd /tmp && \
    git clone git://github.com/SOCI/soci.git && \
    mkdir soci/build && \
    cd soci/build && \
    cmake -DWITH_SQLITE3=ON -DSOCI_TESTS=OFF -DSOCI_CXX_C11=ON .. && \
    make -j4 && \
    make install && \
    rm -Rf /tmp/soci

RUN cd /tmp && \
    git clone https://github.com/Cylix/cpp_redis.git && \
    cd cpp_redis && \
    git submodule init && git submodule update && \
    mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make -j4 && \
    make install && \
    rm -Rf /tmp/cpp_redis

COPY db /tmp/db
COPY src /tmp/src

RUN mkdir /tmp/src/build && \
    cd /tmp/src/build && \
    cmake .. && \
    make -j4

COPY docker/run.sh /tmp/

EXPOSE 6502

ENTRYPOINT ["/tmp/run.sh"]
#ENTRYPOINT ["tail", "-f", "/dev/null"]