# DBus Permission Manager

## Концепция

В популярных мобильных ОС присутствует динамическое управление разрешениями. 
Один из способов его реализации - централизованный сервис, у которого 
стороннее приложение может запросить какое-либо разрешение, а другой сервис 
может узнать, запрашивало ли приложение, которое к нему обращается, 
определенный вид разрешения.
## Необходимо
### Реализовать DBus сервис с именем com.system.permissions на сессионной шине с использованием языка C++, который имеет 2 метода:
#### void RequestPermission(permissionEnumCode: int)
Который получает путь до исполняемого файла, вызвавшего данный метод, 
по dbus имени клиента и сохраняет в базу данных информацию о том, 
что данный исполняемый файла запросил заданное разрешение. 
В случае ошибки метод должен возвращать DBus ошибку с человекочитаемым сообщением.
#### bool CheckApplicationHasPermission(applicationExecPath: String, permissionEnumCode: int)
Который проверяет имеется ли у приложение с заданным путем до исполняемого 
файла заданное разрешение. В случае ошибки метод должен возвращать DBus ошибку 
с человекочитаемым сообщением.
## Перечисление разрешений:
enum Permissions { SystemTime = 0 }
## Пример использования:
gdbus send -e -d com.system.permissions -o / -m com.system.permissions. 0RequestPermission
gdbus send -e -d com.system.permissions -o / -m com.system.permissions. CheckApplicationHasPermission /usr/bin/com.example.example 0
Реализовать DBus сервис com.system.time на сессионной шине с использованием языка C++, 
который имеет 1 метод:
### uint64 GetSystemTime()
Который возврашает текущего системного времени. Однако перед этим, он получает 
путь до исполняемого файла, вызвавшего данный метод, по dbus имени клиента 
и проверяет при помощи DBus сервиса, имеет ли данный исполняемый файл разрешение. 
В случае если исполняемый файл не имеет разрешения SystemTime UnauthorizedAccess, 
должна возвращаться ошибка с человекочитаемым сообщением. В случае любой другой 
ошибки должна возвращаться обычная ошибка с человекочитаемым сообщением.
#### Пример использования:
gdbus send -e -d com.system.time -o / -m com.system.time.GetSystemTime
### Реализовать приложение с использованием языка C++, которое:
Пробует запросить у сервиса текущее время и в случае ошибки запрашивает com.system.time
разрешение у сервиса, после чего пытается повторить запрос текущего времени.
После получения текущего времени, выводит его на экран в человекочитемом виде.timestamp'a
## Обязательные требования
Проект должен быть написан на C++ c использованием библиотек илиsdbus-c++ QtDBus
Проект должен быть размещен на GitHub с подробным README с инструкцией по сборке и использованию
В проекте должна быть осмысленная история коммитов
Проект должен компилироваться под Linux (например Ubuntu 20.04/22.04)
Проект должен компилироваться без предупреждений компилятора
Проект должен использовать систему сборки CMake, Meson или QMake
Проект должен быть отформатирован при помощи clang-format