docker build -t permission-service .
docker run -it --rm permission-service
docker exec -it <container_id> ./build/client
https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md

---
sudo cp com.system.permissions.conf /etc/dbus-1/system.d/
sudo cp com.system.permissions.service /etc/systemd/system 
FIX PATHES EVERYWHERE
--
not send but call
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission /usr/bin/com.example.example 0
CLARIFY SDBUS VERSION

sudo apt install  sqlite3 sqlite3-tools
create sqlite db permissions sqlite3 permissions.db