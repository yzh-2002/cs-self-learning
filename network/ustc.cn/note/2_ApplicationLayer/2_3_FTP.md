## FTP
> 文件传输协议（File Transfer Protocol），采用CS模式，基于TCP服务，FTP应用端口号：`21`

重点：控制连接与数据连接分离

FTP传输文件过程：

1. 客户端主动向服务端建立TCP（控制）连接（端口：21）
2. 客户端通过控制连接验证身份
3. 客户端通过控制连接发送命令浏览远程目录
    1. 客户端通过控制连接发送传输文件命令
4. 服务端向客户端建立TCP（数据）连接（端口：不确定）
5. 传输文件，结束后数据连接自动断开

这里需要注意的是：数据连接的建立可能有服务端发起，也可能由客户端发起（对应主动与被动两种模式）