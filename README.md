# Краткое описание:

1) Проект не собран. Для сборки использовать make.
2) В проекте 3 файла с тестовыми данными. 
    - temperature_all_err.csv
    - temperature_big.csv
    - temperature_small.csv
	
	Лучше всего работу программы видно при открытии файла temperature_small.csv (я его отредактировал так, чтобы был использован (и виден) весь функционал приложения.
Файл temperature_all_err.csv содержит все данные с ошибками и создан для того, чтобы показать, как работает приложение при загрузке такого файла.

    Так как в файле temperature_big.csv данные в каждом месяце идентичны - статистика за год выглядит не очень (все месяцы теплые и нет холодных) Можно этот случай учесть при выводе статистики, но уже не стал так заморачиваться.

    При выводе статистики за год подсчитывается максимальная и минимальная температура за год, но если такая температура встречалась не один раз в год, то выводится список дат, когда эта температура зафиксирована в первый раз в месяце.
