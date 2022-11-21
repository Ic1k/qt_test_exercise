# Сокращения
- Номер пункта со звездочкой, например 1* или 2*,
воспринимать как обязательное требование

# Требование к сборке

1*. Фреймворк Qt5 ( Qt 5.9.X -> 5.9.8 ) & qmake \
2*. Стандарт языка С++11 / С++14 \
3*. Компиляторы: windows( msvc14 ), linux(g++)

Требование к написанию кода: \
1*. Придерживаться паттерну MVC \
2. Наименование переменных в стиле - camelCase \
3. Наименование членов класса в стиле - m_camelCase \
4. UI - построен внутри кода, использование файлов *.ui в проекте не допускается \
5*. Для виджетов, которые отображают данные \
реализовать кастомный делегат \
6*. На выходе ожидаем видеть исполняемый файл

# Задание

### Введение
Компания занимается разработкой различной электроники. \
У каждого устройства есть свой процесс изготовления ( тех. процесс ), \
например: пайка, проверка, упаковка и тд.

### Описание задачи
Необходимо реализовать графическое приложение, которое должно отображать форму, состоящая из двух логический(визуальных) частей. \
Первая часть (слева):
1. Наименование изделия [widget] \
2*. Список операций тех. процесса ( отсортирован по последовательности тех. процесса ) [view]

Вторая часть(остальное пространство) \
1*. Список файлов для выбранной операции, с разделением \
на вкладки (инструкции, прошивки) [view] \
2. выбор файла с локального пк (приветствуется фильтрация по расширениям для вкладки "прошивка")

### Данные
Реализовать необходимые структуры передаваемых данных в форму, например:
- структура описывающая устройство (например, уникальный номер, наименование и тд)
- структура описывающая список операций тех. процесса устройства
- структура описывающая файл ( с привязками к устройству и операции )

### Наполнение данными форму
Вариант 1. Статичный список структур созданных внутри программы \
Вариант 2. Реализовать наполнение через выбор файла \
Вариант 3. Развернуть базу данных (используя MySQL) \
Вариант 3. Свой вариант

[Подсказка] \
Данное задание, это часть реального функционала внутреннего ПО компании. \
Струкруты приведенные в примере, описывают поля таблицы в БД

# Проверка задания

Созданный проект необходимо выложить на свой публичный репозиторий в гите. \
Последний коммит должен содержать комментарий, по которому можно понять, что на этом этапе задание было выполнено, \
например "Задание выполнено", если аналогичного коммита не существует, задание считается не завершенным и \
обратной связи не будет. Последующие комиты(после финального) не будут учитываться. \
Проверяться задание будет на винде(32), по этому в репозиторие должен быть каталог "deploy". \
Под деплоем понимается portable версия приложения. \
Уведомить HR а, о том, что задание было выполнено и скинуть ссылку на репозиторий.
