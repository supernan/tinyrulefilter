# tinyrulefilter
##项目介绍
* 本项目实现简单的规则过滤
* 输入要过滤的文档和规则，输出命中规则的文档下标
* 除关键词之外支持的逻辑运算包括：^ | 和~。分别代表“与” “或” “非”三种基本运算
* 规则示例：~([中国]^[美国]) 、([美国]|[中国])

##项目结构
* src 源代码目录
* include 头文件目录
* thirdparty 第三方库（AC自动机和glog）
* demo 示例代码

##运行方法
* clone代码到本地
* cd tinyrulefilter
* mkdir build
* mkdir lib
* cd build
* cmake ..
* make
* 运行以上步骤可完成项目编译，生成的库在lib下，示例在demo下
