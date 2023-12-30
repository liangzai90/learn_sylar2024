## 学习网上的sylar框架

记录我的学习笔记。

### 网站：
https://www.bilibili.com/video/av53602631/?from=www.sylar.top
http://www.sylar.top/blog/



mkdir build && cd build && cmake ../ && make 



## sylar 

## 开发环境
CentOs7,
gcc 9.1,
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


## 协程库封装

## socket 函数库

## http协议开发

## 分布协议

## 推荐系统









