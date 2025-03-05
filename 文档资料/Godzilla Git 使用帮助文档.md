#  Godzilla Git 使用帮助文档

## 安装

+ 注意一开始要选择`嵌入在系统的shell中`

+ 选择 在桌面创建快捷方式

## 使用

+ 在合适位置创建工程文件夹，在文件目录下右键打开shell
+ 输入：`git init` 创建仓库
+ 根据网络教程配置SSH密钥
+ 在工作文件夹下工作
	+ 再次打开在文件夹终端输入`git add .`
	+ `git commit -m "注释"`//注释可以任写
	+ `git push`

这样就将本地与GitHub同步了

具体细节可以参看：

https://blog.csdn.net/nuannuanwfm/article/details/104119932

## 多人协作模式
+ 本地创建文件夹，初始化仓库
+ 将线上仓库Pull到本地
+ 本地用自己所属的branch
