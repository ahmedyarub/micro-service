[![Build Status](https://travis-ci.com/ahmedyarub/micro-service.svg?branch=master)](https://travis-ci.com/ahmedyarub/micro-service)
[![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/ahmedyarub/micro-service)](https://ci.appveyor.com/project/ahmedyarub/micro-service)

Docker:
docker build . --tag=microservice:latest
docker run -it microservice:latest

Ex de URL de Teste:
http://127.0.0.1:8088/convert?from=USD&to=EUR&amount=123.45

Instalação (Ubuntu Bionic):
./vcpkg install http-parser fmt restinio clara cpp-redis json-dto SQLite3 boost-lexical-cast boost-math boost-di

apt sudo update && \
    sudo apt install software-properties-common -y && \
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y && \
    sudo apt update && \
    sudo apt install g++-9 gcc-9 curl unzip tar wget build-essential git openssl libssl-dev pkg-config -y

wget -qO- https://repo1.maven.org/maven2/org/flywaydb/flyway-commandline/5.2.4/flyway-commandline-5.2.4-linux-x64.tar.gz | tar xvz && sudo ln -s pwd/flyway-5.2.4/flyway /usr/local/bin

flyway -locations=filesystem:migrations/sql/ -url=jdbc:sqlite:/tmp/microservice.db -user= -password= migrate

cd /tmp
git clone git://github.com/SOCI/soci.git
cd soci/
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=~/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake -DWITH_SQLITE3=ON -DWITH_MYSQL=OFF -DSOCI_TESTS=OFF -DCMAKE_INSTALL_PREFIX:PATH=/usr .. && \
make
sudo make install

Em seguida build com cmake e make

Windows
vcpkg install restinio restinio:x64-windows clara cpp-redis cpp-redis:x64-windows json-dto json-dto:x64-windows SQLite3:x64-windows boost-lexical-cast:x64-windows boost-math:x64-windows boost-di:x64-windows

git clone https://github.com/SOCI/soci
cd soci
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=D:/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake -DWITH_SQLITE3=ON -DWITH_MYSQL=OFF -DSOCI_TESTS=OFF ..
MSBuild /p:Configuration=Release ALL_BUILD.vcxproj
MSBuild /p:Configuration=Release INSTALL.vcxproj
