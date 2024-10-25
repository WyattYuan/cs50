# 关于Week4 problemset 的一些思考
## filters
* 定义二维数组不可缺分号,以下为错误实例
```c
int Gx[3][3] = {

        {-1,0,1},{-2,0,2},{-1,0,1}

    }

    int Gy[3][3] = {

        {-1,-2,-1},{0,0,0},{1,2,1}

    }
```
- 分配内存，一定要检查指针是否为空
```c
if (newimage == NULL) // 添加内存分配失败的检查
    {
        fprintf(stderr, "Memory allocation failed for new image\n");
        return; // 处理内存分配失败
    }
```
- 多次使用的常量，如255，可以设置为宏定义
- 结构体可以一整个进行赋值，达到复制的目的
- 若想要对二维数组中的每个点的包括本身的3x3区域进行遍历，可按下列操作来
	- 不可在循环单个点后就立马赋值更新数据，会污染后续3x3区域，因此要考虑另起temp，完成全部操作后再倒回来
	- 我在edge和blur中都犯了这个错误，后面是突然悟到的，确实很坑😅
```c
for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int neighbor_h = h + i;
			int neighbor_w = w + j;

			if (neighbor_h >= 0 && neighbor_h < height && neighbor_w >= 0
				 && neighbor_w < width) // 合并边界检查
			{
				...
			}
		}
	}
```
- 一点感悟
	- 读题干非常难受，理解源代码也非常难受，此后一定不在水课上写如此高难度的作业😣
	- 有几个关键错误还是问fitten code问出来的，实在有些头疼
	- 这次作业开始涉及多文件之间的配合了，有点意思
	- 文件流感觉是个比较不好理解的部分🤨🤨
