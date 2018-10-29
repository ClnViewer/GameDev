# GameDev - Game Device
Библиотека для взаимодействия с окнами  сторонних приложений (`WINAPI`). 

- Изображения `Bitmap`:
   - захват изображения окна,
   - преобразование в `GreyScale`/`Black&White`,
   - операции сравнения изображений с возвращаемым `%` совпадений,
   - сохранение изображения на диск в формате `bmp`
- Ввод `клавиатуры`/`мыши`:
   - перемещение курсора, клик мыши,
   - ввод текста с эмуляцией клавиатуры в режиме реального человека (анти GameGuardion),
   - работа в режимах как в активном приложении, так и в приложении `на заднем плане`
- Поиск `идентификатора окна`:
   - поиск последнего активного окна по классу приложения,
   - поиск по дереву выбранного запущенного приложения


## API Врапперы:
API для использования библиотеки в различных языках [C++](https://github.com/ClnViewer/GameDev/blob/master/API/GameDevClass.hpp),  [C](https://github.com/ClnViewer/GameDev/blob/master/API/GameDev.h),  [C#](https://github.com/ClnViewer/GameDev/blob/master/API/GameDev.cs) .


## Сборка

Сборка расчитана на IDE `Code::Blocks`, но так-же может быть собрана `MinGW`в консольном режиме. Для этого исправьте пути к исполняемым файлам на вашей системе в [Makefile](https://github.com/ClnViewer/GameDev/blob/master/Makefile) и запустите `mingwXX-make.exe` в корневой директории проекта.

Библиотеку желательно собирать с подключенной библиотекой [`OpenMP`](http://www.math.ucla.edu/~wotaoyin/windows_coding.html), это ускоряет функции работы с изображениями.
Ключи сборки можно посмотреть в файле проекта: [GameDevDll.cbp](https://github.com/ClnViewer/GameDev/blob/master/GameDevDll.cbp) .


## License

_MIT_
