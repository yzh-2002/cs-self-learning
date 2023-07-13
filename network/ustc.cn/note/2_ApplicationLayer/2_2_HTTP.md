## HTTP
> 超文本传输协议（`HyperText Transfer Protocol`），Web应用层协议，采用CS模式，基于TCP服务

HTTP通信过程：

1. 客户端主动向服务端发起一个端口号为`80`的TCP连接
2. 服务端接受TCP连接
3. 交换HTTP报文
4. 断开TCP连接

HTTP1.0 采用非持久连接，也即每次建立连接仅传输一个对象即断开连接。
HTTP1.1 采用持久连接，每次建立连接可传输多个对象。

其中持久连接由分为流水线（HTTP1.1默认方式）和非流水线式，前者每遇到一个引用对象就立刻发送请求，后者只有上次请求返回之后才可以发送新的请求。

### HTTP报文
> HTTP报文分两种：请求+响应

请求报文
```
[method]\space[url]\space[version]\cr\if #请求行
[header field name]:[value]\cr\if #
                .                 #  
                .                 # 首部行
                .                 #  
[header field name]:[value]\cr\if #       
\cr\if
[body]         
```

响应报文：
```
[protocol/version]\space[status code]\space[status message]\r\n
[header field name]:[value]\cr\if #
                .                 #  
                .                 # 首部行
                .                 #  
[header field name]:[value]\cr\if #
\r\n
\r\n
[data]
```

### Cookies
> HTTP协议是无状态的，每次请求彼此无关，但是上层应用需要有状态，比如网站需要知道每次请求的用户是谁，以便于记录其请求内容进行定制化推送，亦或者在网站中根据用户信息保存用户状态（购物车等信息）

如何实现呢？--`cookie`

作为一名web开发人员，这块太熟了，不再赘述。

### Cache
> [之前博客里总结的十分详细](https://yzh2002.cn/2022/10/27/http%E5%92%8C%E6%B5%8F%E8%A7%88%E5%99%A8%E9%82%A3%E4%BA%9B%E4%BA%8B/#more)
