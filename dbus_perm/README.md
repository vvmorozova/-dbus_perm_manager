docker build -t permission-service .
docker run -it --rm permission-service
docker exec -it <container_id> ./build/client
https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md