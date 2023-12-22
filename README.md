## 学习网上的sylar框架

记录我的学习笔记。

### 网站：
https://www.bilibili.com/video/av53602631/?from=www.sylar.top
http://www.sylar.top/blog/



mkdir build && cd build && cmake ../ && make 



## sylar 

## 开发环境
CentOs7
gcc 9.1
cmake 

## 项目路径
bin     -- 二进制
build   -- 中间文件路径
cmake   -- cmake函数文件夹
CMakeLists.txt  -- cmake的定义文件
lib     -- 库的输出路径
Makefile
sylar   -- 源代码路径
tests   -- 测试代码


## 日志系统

1)Log4J
    
    Logger（定义日志类别）
    |
    |-------Formatter（日志格式） 
    |
    Appender（日志输出地方）


## 配置系统
  Config --> yaml
  yamp-cpp: github 搜
  mkdir build && cd build && cmake .. && make install 

```txt
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/lib64/libyaml-cpp.a
-- Up-to-date: /usr/local/include
-- Installing: /usr/local/include/yaml-cpp
-- Installing: /usr/local/include/yaml-cpp/anchor.h
-- Installing: /usr/local/include/yaml-cpp/binary.h
-- Installing: /usr/local/include/yaml-cpp/contrib

```

## 协程库封装

## socket 函数库

## http协议开发

## 分布协议

## 推荐系统









