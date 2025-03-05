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



## 初始化本地仓库详细教程

+ 新建本地文件夹，右键点开`在终端中显示`
+ `git init` 完成初始化代码
+ `git remote add origin git@github.com:LouXuezhi/GCC_Godzilla.git` \\\注意origin 是本地仓库的名字，这一步相当于将本地仓库与线上仓库链接起来
+ `git pull`拉取仓库文件，这时应该会有提示`Please specify which branch you want to merge with.`
+ `git pull origin master` 应该就行了
+ 如果出现`refusing to merge unrelated histories`报错，使用`git pull origin master --allow-unrelated-histories`再用`git push origin master:master`\\\这步相当与将线上线下的分支链接
+ 如果出现分支未选择的报错 则用它推荐的`git push --set-upstream origin master`即可
+ 配置好后别忘了 `git checkout <自己的分支>`转换工作区
+ 之后就可以用 add commit push 三步走来上传文档了
+ 也可以用`git pull`下载所在仓库分支的所有文档

