[![Build Status](https://travis-ci.com/ahmedyarub/micro-service.svg?branch=master)](https://travis-ci.com/ahmedyarub/micro-service)

Docker:
docker build . --tag=microservice:latest
docker run -it microservice:latest

Ex de URL de Teste:
http://127.0.0.1:8088/convert?from=USD&to=EUR&amount=123.45

Obs: o IP no Docker pode ser diferente!

Instalação (Ubuntu Bionic):

sudo apt install build-essential openssl libssl-dev pkg-config libboost-all-dev sqlite3 libsqlite3-dev -y

wget -qO- https://repo1.maven.org/maven2/org/flywaydb/flyway-commandline/5.2.4/flyway-commandline-5.2.4-linux-x64.tar.gz | tar xvz && sudo ln -s pwd/flyway-5.2.4/flyway /usr/local/bin

flyway -locations=filesystem:migrations/sql/ -url=jdbc:sqlite:/tmp/microservice.db -user= -password= migrate

cd /tmp
git clone git://github.com/SOCI/soci.git
cd soci/
mkdir build
cd build
cmake -DWITH_SQLITE3=ON -DWITH_MYSQL=OFF -DSOCI_TESTS=OFF ..
make
sudo make install

cd /tmp
git clone https://github.com/Cylix/cpp_redis.git
cd cpp_redis
git submodule init && git submodule update
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
make install

Em seguida build com cmake e make

Windows
vcpkg install restinio restinio:x64-windows clara cpp-redis cpp-redis:x64-windows json-dto json-dto:x64-windows

git clone https://github.com/SOCI/soci
cd soci
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=D:/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake -DWITH_SQLITE3=ON -DWITH_MYSQL=OFF -DSOCI_TESTS=OFF ..
MSBuild /p:Configuration=Release ALL_BUILD.vcxproj
MSBuild /p:Configuration=Release INSTALL.vcxproj