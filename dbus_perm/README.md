docker build -t permission-service .
docker run -it --rm permission-service
docker exec -it <container_id> ./build/client
https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md

---
sudo cp com.system.permissions.conf /etc/dbus-1/system.d/
sudo systemctl restart dbus

sudo cp com.system.permissions.service /etc/systemd/system 
FIX PATHES EVERYWHERE
--
not send but call
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission /usr/bin/com.example.example 0
CLARIFY SDBUS VERSION

sudo apt install  sqlite3 sqlite3-tools
create sqlite db permissions sqlite3 permissions.db

----
sudo cp dbus_perm/com.system.permissions.service.old /usr/share/dbus-1/services/com.system.permissions.service
sudo systemctl restart dbus

G_MESSAGES_DEBUG=all gdbus call -e -d com.system.time -o / -m com.system.time.GetSystemTime