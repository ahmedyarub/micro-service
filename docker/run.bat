flyway -locations=filesystem:/tmp/db/migrations/sql/ -url=jdbc:sqlite:/tmp/microservice.db -user= -password=  migrate

export LD_LIBRARY_PATH=/usr/lib64
ldconfig

c:\src\build\micro-service.exe