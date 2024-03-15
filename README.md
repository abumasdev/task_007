# task_007
Задание 007 для образовательного канала Peer Education

###### Задача 1. Уровень easy. В директории data-samples находится файл с базой данных. Вам необходимо любыми подручными средствами прочитать строку №7 в таблице Students и написать программу для вывода на экран этой строки в формате id name age email. Вы можете пользоваться любыми инструментами для чтения строки из базы данных.

###### Задача 2. Уровень easy. Реализовать программу для замены пробелов между словами. На вход подается строка, далее через перенос строки новый разделитель. Например: mama papa\n# -> mama#papa. Если строка состоит из одного слова, разделитель не нужен. Сборка проекта должна осуществляться с помощью Makefile, стадия сборки change_separator.Бинарник должен компилироваться в папку bin и называться change_separator.

###### Задача 3. Уровень easy. Реализовать программу для бинарного уменьшения строк. На вход подается строка состоящая из одного слова. Необходимо вывести на экран: строку, половину строки, четверть строки и т.д., последний вывод должен содержать один символ. При уменьшении строки двигайтесь к началу строки. Например: abrakadabra -> abrakadbra\nabraka\nabr\nab\na. Если длина строки нечетная, то всегда используйте округление вверх. 11/2 = 6. Сборка проекта должна осуществляться с помощью Makefile, стадия сборки binary_div.Бинарник должен компилироваться в папку bin и называться binary_div. 

Ну что дождались по-настоящему интересной задачи?

###### Задача 4. Уровень medium. Необходимо реализовать api для подключения к базе данных, которая лежит в директории data-samples. На вход программе подаются команды: SHOW\n{id}, SHOWALL, ADD\n{name age email}, REMOVE\n{id}, EXIT. SHOW: вывести на экран в одну строку информацию из базы данных с определенным id. SHOWALL: вывести все записи, каждая с новой строки. ADD добавить новую строку в базу данных, id определяется автоматически. REMOVE: удаление записи из базы с определенным id. EXIT: выход из программы. Вывод каждой команды должен заканчиваться переносом строки. Обрабатывать ошибку если база данных пустая не требуется. Сборка проекта должна осуществляться с помощью Makefile, стадия сборки real_db.Бинарник должен компилироваться в папку bin и называться real_db. 

> Примечание. Sqlite [документация](https://www.sqlite.org/)