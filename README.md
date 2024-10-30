# Как собрать проект

*Предполагается, что команды запускаются не из-под root*
*Предполагается, dbus установлен и сконфигурирован*

1. Дать права на исполнение скриптам:
```
sudo chmod +x install_reqs.sh kill_all.sh run_all.sh add_dbus_services.sh
```
2. Установка необходимых пакетов
```
./install_reqs.sh
```
3. Добавление конфигов dbus сервисов
```
./add_dbus_services.sh
```
4. Сборка через cmake
```
mkdir build && cd build && cmake ..
```

# Как запустить проект
```
cd ..
./run_all.sh

```