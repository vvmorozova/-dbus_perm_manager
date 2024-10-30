# Как собрать проект

*Предполагается, что команды запускаются не из-под root*

1. Дать права на исполнение скриптам:
```
sudo chmod +x install_reqs.sh kill_all.sh run_all.sh add_dbus_services.sh
./install_reqs.sh

mkdir build && cd build && cmake ..
```

# Как запустить проект
```
cd ..
./run_all.sh

```