# Как добавить задачу

Задачи добавляются в ветку `master`. Для задачи нужны два файла с одинаковым
путём: `exercises/00_basics/07_example.c` и `tests/00_basics/07_example.c`.
Номера тем и задач — две цифры, после `_` идёт название.
Алгоритмические задачи кладутся в трек без номера: `exercises/algo/`.

1. Создай задачу в `exercises/`: условие в комментарии, функция с TODO
   и `main`, который показывает её работу.

   ```c
   /*
   # Task 7 — Example

   Вернуть число, умноженное на два.
   */

   #include <assert.h>
   #include <stdio.h>

   int example(int value)
   {
       /* TODO: реализуйте example. */
       (void)value;
       assert(!"TODO: example");
       return 0;
   }

   int main(void)
   {
       printf("%d\n", example(2));
       return 0;
   }
   ```

   `(void)value` убирает предупреждение о неиспользуемом параметре,
   а `assert(!"TODO: ...")` роняет тесты, пока задача не решена.

2. Создай тесты в `tests/`. Файл подключает задачу через `#include`
   и переименовывает её `main`, чтобы объявить свой:

   ```c
   #include <assert.h>
   #include <stdio.h>

   #define main demo_main
   #include "../../exercises/00_basics/07_example.c"
   #undef main

   static void test_two(void)
   {
       assert(example(2) == 4);
   }

   int main(void)
   {
       test_two();

       puts("All tests passed");
       return 0;
   }
   ```

3. Проверь, что заготовка собирается и тесты падают на TODO:

   ```sh
   make test 0 7
   ```

4. Закоммить оба файла в `master`. Если тема новая, добавь её
   в `docs/topics.md`.
5. Перейди в свою ветку, сделай `git merge master` и реши задачу.
   Если при решении нашлась ошибка в тестах, исправь её в `master`.

## Задача из нескольких файлов

Если задача — каталог (`exercises/05_modules/02_example/`), условие лежит
в его `main.c`, а тест по-прежнему один: `tests/05_modules/02_example.c`.
Тест подключает заголовки модулей и собирается со всеми `.c` из каталога,
кроме `main.c`. Перед этим каталог собирается своим `Makefile`: он должен
уметь `make` (создаёт `app`) и `make clean`.

## Что делает задачу хорошей

Хорошая задача тренирует одну конкретную возможность C, а тесты проверяют
граничные случаи и то, что функция не зависит от начальных значений
выходных параметров.
