# Как собрать проект

*Команды запускаются не из-под root*
*Dbus должен быть установлен и сконфигурирован*
*Пользователь должен находиться в корневой директории проекта*

1. Дать права на исполнение скриптам:
```
sudo chmod +x install_reqs.sh kill_all.sh run_all.sh add_dbus_services.sh
```
2. Установка необходимых пакетов
```
./install_reqs.sh
```
3. Добавление конфигов dbus сервисов
*Тут перезапуск демона dbus, поэтому может произойти логаут, это нормально*
```
./add_dbus_services.sh
```
4. Сборка через cmake
```
mkdir build && cd build && cmake .. && make
```

# Как запустить проект

```
cd ..
./run_all.sh
./build/main_app/main_app
```

# Как использовать команды из задания

На версии dbus 0.9.10 нет команды **send**, она заменена на **call**:
*com.system.permissions*
```
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0
gdbus call -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission /usr/bin/com.example.example 0
```

*com.system.tim*
```
gdbus call -e -d com.system.time -o / -m com.system.time.GetSystemTime
```