## DNA 写了超久，here are some 小总结

* `sys.argv`
* `.DictReader`
* `with open() as a file`

  * 如果要把`open()`的东西存起来，必须在open之前新建一个变量，with open as 会自己管理内存，不存起来就销毁了
  * `as`后的东西相当于文件名，相当于`FILE* ptr = fopen("example.txt", "r");`
* `is_subset = all(int(row.get(key)) == value for key, value in match_dict.items())`

  * all迭代，用于检查元素的对应情况
  * items返回一个集合类型
  * int非常重要，我在walkthrough看到，当时不懂在哪要用str转int，直到copilot跟我说，`row.get(key)`是一个文本类型，这才恍然大悟
* dict对象
* list对象

## debug需要命令行咋办？

这节课我使用vscode 的 debug 有很大收获，在其帮助下我才查清楚了问题在哪一行

这节课的程序需要命令行，但是debug默认情况下不接受命令行，要使用“launch.json”，加一行即可

```json
  "args": ["databases/large.csv", "sequences/9.txt"],
```
