# **Тестовое задание**


# **Как собрать проект**

#### 1. Перейдите в директорию ```src```.
#### 2. Выполните ```make```.
#### 3. Собранный проект находится в папке ```build```.
#### 4. В папке ```build``` отредактируйте файл ```config.ini```, введите необходимые данные для подключения к базе данных.
#### 5. Запустите файл ```Vega_absolut```

# **Документация**
- Приложение позволяет нам просмотреть весь список устройств производимых на предприятии.
- Также для выбранного из списка устройства можно просмотреть какие технические процессы необходимы для его производства. 
- Есть возможность промотреть необходимые документацию и програмное обеспечение для определенного этапа производства.
- Данное приложение разработанно в соответствии с требованиям технического задания.

#### **Materials**
 В папке ```materials``` расположены тестовые файлы и dockerfile mysql, со скриптом создания базы данных.


- Для запуска тестовой базы в контейнере докер необходимо из директории ```materials/mysql``` выполнить следущую команду:
```
docker build -t mysql_db .
docker run -d  mysql_db
```

#### **Deploy**
 В папке ```deploy``` расположен полный дамп базы данных и portable версия для windows


- Для запуска  необходимо перейти в директорию ```deploy/Vega_Absolut```
- Отредактировать файл ```config.ini```

```
[mysql]
database=
host=
password=
user=
port=
```
- Запустить файл ```Vega_absolut.exe```
