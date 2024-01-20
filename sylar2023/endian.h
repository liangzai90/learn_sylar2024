#ifndef  __SYLAR_ENDIAN_H__
#define  __SYLAR_ENDIAN_H__

#define  SYLAR_LITTLE_ENDIAN  1
#define  SYLAR_BIG_ENDIAN     2

#include <byteswap.h>
#include <stdint.h>

namespace sylar{

//typename std::enable_if<sizeof(T) == sizeof(uint64_t), T>::type：
//这是一个使用 std::enable_if 的模板元编程技巧，
//它会在编译时对模板参数进行条件判断。
//这里的条件是 sizeof(T) == sizeof(uint64_t)，
//即参数 T 的大小是否等于 uint64_t 的大小。
//如果条件成立，enable_if 的 type 成员将被定义为 T 类型；
//否则，这个模板不会被实例化。
template<class T>
typename std::enable_if<sizeof(T) == sizeof(uint64_t), T>::type
byteswap(T value) {
    return (T)bswap_64((uint64_t)value);
}

template<class T>
typename std::enable_if<sizeof(T) == sizeof(uint32_t), T>::type
byteswap(T value) {
    return (T)bswap_32((uint64_t)value);
}

template<class T>
typename std::enable_if<sizeof(T) == sizeof(uint16_t), T>::type
byteswap(T value) {
    return (T)bswap_16((uint64_t)value);
}

#if  BYTE_ORDER == BIG_ENDIAN
#define  SYLAR_BYTE_ORDER  SYLAR_BIG_ENDIAN
#else 
#define  SYLAR_BYTE_ORDER  SYLAR_LITTLE_ENDIAN
#endif 

#if  SYLAR_BYTE_ORDER == SYLAR_BIG_ENDIAN

template<class T>
T byteswapOnLittleEndian(T t) {
    return t;
}

template<class T>
T byteswapOnBigEndian(T t) {
    return byteswap(t);
}
#else 

template<class T>
T byteswapOnLittleEndian(T t) {
    return byteswap(t);
}

template<class T>
T byteswapOnBigEndian(T t) {
    return t;
}
#endif 


}



#endif 