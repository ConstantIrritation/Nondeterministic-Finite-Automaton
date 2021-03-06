# Условие задачи: 
Даны α и слово u. Найти длину самого длинного суффикса u, принадлежащего L. 

## Описание алгоритма: 

Построим НКА по регулярному выражению в обратной польской записи. Для проверки принадлежности подслова(суффикса, в частности), необходимо итерироваться по автомату. Затем переберем все суффиксы заданного слова, от большего к меньшему, и на моменте, когда какой-либо суффикс найден в языке, завершаем алгоритм, так как дальше возможная длина суффиксов будет только уменьшаться. 

При считывании регулярного выражения, задающего язык, строим автомат с помощью функций `Add()`, `Mult()`, `Kleene()`, `Letter(c)`, также есть воспомогательная функция `AddEdge(from, to, letter)`.
Теперь подробнее про эти функции.
 * `AddEdge(from, to, letter)`: добавляет ребро(переход) между вершинами(состояниями) по какой-то букве. Если перехода по букве нет, то просто добавляем в соответствующее полe состояния автомата единичный std::vector, в котором хранится информация о вершине, в которую есть переход по этой букве. Если состояние есть - обновляем.
 * `Add()`: Объединение автоматов. Снимаем со стека 2 ребра. Добавляем
новую пустую вершину в автомат и объявляем, что у неё есть пустые переходы с вершинами, из которых выходят ребра со стека. Далее добавляем в автомат ещё одну вершину, которую соединяем новыми рёбрами с вершинами, в которые идут рёбра со стека. Новую вершину делаем терминальной, а вершины, в которые идут рёбра со стека - нетерминальными. Добавляем на стек ребро, соединяющее две новые вершины.
 * `Mult()`: Конкатенация автоматов. Снимаем со стека 2 ребра. Вершину, в которую идёт первое ребро, демаем нетерминальной. Добавляем ребро по пустому слову, которое будет соединять вершину, в которую идёт первое ребро, с вершиной, из котороё идёт второе ребро. Добавляем на стек ребро, соединяющее начало первого ребра и конец второго.
 * `Kleene()`: замыкание Клини. Снимаем со стека ребро. Создаем новую вершину, которую объявляем терминальной (вершину, в которую идёт ребро со стека - нетерминальной), из конца ребра делаем ребро в новую вершину, а из неё - в начало ребра со стека. Добавляем на стек ребро из новой вершины в саму себя.
 * `Letter(c)`: переход по буквам. Создаем новую вершину, и объявляем, что у неё есть переход по букве `c` с последней вершиной в автомате. Создаем ещё одну вершину, объявляем её терминальной. Добавляем на стек ребро, соединяющее две новые вершины.

Непосредственно проверка принадлежности слова осуществляется при помощи функции `CheckIfContained()`, которая является по сути алгоритмом обхода в глубину. В очереди храним состояние и букву, по которой хотим из него перейти. Вытаскивая очередной элемент, смотрим все переходы по букве и кладем новые состояния со следующей буквой в очередь, если до этого эти состояния не лежали с этой буквой, затем пробуем пройти по пустому слову из нашего состояния в другие и кладем новые состояния с текущей буквой, если до этого эти состояния не лежали с этой буквой.

 ## Асимптотика:

 Пусть длина регулярного выражения - `n`, а длина слова - `k`. Обработка каждого символа занимает `O(1)`, поэтому построение автомата по регулярному выражениию - `O(n)`. Состояний в атомате тоже `O(n)`, так как каждый символ увеличивает количество состояний не больше, чем на 2. Если длина произвольного слова word - `l`, то функция `CheckIfContained(word)` будет работать за `O(nl)`, так как в каждое состояние мы войдем не более `l` раз(так как на это есть проверка). Тогда на обработку всех суффиксов нужно `O(knk) = O(k^2n)`, так как суффиксов `O(k).`