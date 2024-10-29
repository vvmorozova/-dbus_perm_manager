
sudo cp com.system.time.conf /etc/dbus-1/system.d/ -- only this cfg is necessary
sudo cp com.system.permissions.service /etc/systemd/system 
FIX PATHES EVERYWHERE
--
not send but call
gdbus call -e -d com.system.time -o / -m com.system.time.GetSystemTime
CLARIFY SDBUS VERSION

sudo apt install  sqlite3 sqlite3-tools
create sqlite db permissions sqlite3 permissions.db