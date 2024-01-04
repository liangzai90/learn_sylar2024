## 学习网上的sylar框架

记录我的学习笔记。

### 网站：
https://www.bilibili.com/video/av53602631/?from=www.sylar.top
http://www.sylar.top/blog/



mkdir build && cd build && cmake ../ && make 



## sylar 

## 开发环境

软件 | 软件要求
--------|-----------
linux内核版本:     |	2.6.18及以上版本
系统  | CentOs7 
gcc版本 | 9.1及以上
cmake版本 |  3.0及以上
yaml-cpp版本 | 0.6.0及以上
boost版本 | 1.5.3及以上

### sylar框架的环境准备
https://www.cnblogs.com/music-liang/p/17940148




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

```cpp
yaml 文件的加载和解析

YAML::Node node = YAML::LoadFile(filename);

node.IsMap()
for(auto it = node.begin(); it!= node.end(); ++it){
    it->first, it->second
}

node.IsSequence()
for(size_t i=0; i< node.size(); ++i){
}

node.IsScalar();
```

配置系统的原则，约定优于配置：

```shell
#同步系统时间
sudo ntpdate -u asia.pool.ntp.org
```

```cpp
template<T, FromStr, ToStr>
class ConfigVar;

template<F, T>
LexicalCast;

//容器偏特化 ，支持vector
// list, set,  unordered_set, map, unordered_map,
// map/unordered_map 支持 key = std::string
// Config::Lookup(key) ，key相同，类型不同，不会有报错。需要处理
```

自定义类型，需要实现sylar::LexicalCast,偏特化
实现后，就可以支持Config解析自定义类型.
自定义类型可以和常规stl容器一起使用


配置的事件机制
当一个配置项发生修改的时候，可以反向通知对应的代码，回调

## 日志系统整合配置系统
```yml
logs:
  - name: root
    level: (debug, info, warn, error,fatal)
    formatter: "%d%T%P%T%t%m%n"
    appender:
      - type: (StdoutLogAppender, FileLogAppender)
        level: (debug, info,...)
        file: /logs/xxx.log
```

```cpp
    sylar::Logger  g_logger = sylar::LoggerMgr::GetInstance()->getLogger(name);
    SYLAR_LOG_INFO(g_logger) << "xxxx  log";
```

```cpp
static Logger::ptr g_log = SYLAR_LOG_NAME("system");
// m_root, m_system->m_root
当logger 的appender为空，使用root写logger
```

```cpp
//定义LogDefine LogAppenderDefine 偏特化 LexicalCast,
// 实现日志配置解析
```

```cpp

```
遗留问题：
1. appender 定义的 formatter 读取yaml 的时候，没有被初始化
2. 去掉额外的调试日志
3. 文件名问题

## 线程库
Thread, Mutex
Pthread 

pthread  pthread_create

互斥量  mutex
信号量  semaphore

和log来整合

Spinlock,  替换Mutex，提高性能

写文件，周期性， reopen（解决删除旧文件之后，新写入的数据丢失问题（因为好不到文件名了））

Config, RMutex


遗留问题：
```txt
test_config里面，重新加载配置文件的时候，终端报错了
    YAML::Node root = YAML::LoadFile("/home/henry/workspace/bin/conf/test.yml");
    sylar::Config::LoadFromYaml(root);

因为这里的路径错误了。（我本地.yml文件路径有调整，这里LoadFile的时候，找不到文件，然后就抛出了异常。报错的地方是一个异常。当时没有在第一时间识别这是一个异常。
```    

    
## 协程库封装
定义协程接口
ucontext_t
macro

```
Thread->main_fiber <-------> sub_fiber
            ^
            |
            v
          sbu_fiber
```


## socket 函数库


## http协议开发


## 分布协议


## 推荐系统



## 其他    
直接在centos下面，通过man手册，查看C语言下面函数的定义

```shell
man assert

man  pthread_create
man makecontext
```

```cpp
cpp里面不熟悉的若干关键字

volatile

explicit

constexpr



```






