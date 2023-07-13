## EMAIL
### 电子邮件

主要组成部分：
1. 用户代理：邮件阅读器，攥写，编辑和阅读邮件，例如：`Outlook,Foxmail`
2. 邮件服务器：管理和维护发送给用户的邮件，邮件服务器之间用`SMTP`通信
3. 简单邮件传输协议（SMTP）

### SMTP
> 简单邮件传输协议，基于TCP实现，端口号：25

1. 建立TCP连接
2. 通信：SMTP客户端与邮件服务器之间通过一系列的命令和响应进行交互。常见的命令包括HELO（建立连接）、MAIL FROM（指定发件人）、RCPT TO（指定收件人）、DATA（开始邮件内容）、QUIT（结束会话）...

报文格式：

1. 请求报文（命令）
```
[command] <parameter1> ...\r\n
```
2. 响应报文
```
[status code] [response message] \r\n
```

示例：
```shell
C: HELO example.com\r\n
S: 250 Hello example.com, pleased to meet you\r\n

C: MAIL FROM:<sender@example.com>\r\n
S: 250 OK\r\n

C: RCPT TO:<recipient@example.com>\r\n
S: 250 OK\r\n

C: DATA\r\n
S: 354 Enter mail, end with "." on a line by itself\r\n

C: From: sender@example.com\r\n
C: To: recipient@example.com\r\n
C: Subject: Example Subject\r\n
C:\r\n
C: This is the body of the email.\r\n
C: It can have multiple lines.\r\n
C: .\r\n
S: 250 OK\r\n

C: QUIT\r\n
S: 221 Bye\r\n
```

**多媒体扩展（`MIME`）**：在报文首部用额外的行申明MIME内容类型

### 邮件访问协议

前文中SMTP协议用于将邮件传输到对方的邮件服务器，但是对方的用户代理想要从邮件服务器中获取邮件，则需要使用到邮件访问协议。目前有三种协议可使用：

1. POP3（Post Office Proyocol）
2. IMAP（Internetional Mail Access Protocol）
3. HTTP

POP3分为`用户确认阶段`+`事物处理阶段`两阶段。且其采用`下载并删除`的方式处理，即一旦邮件被下载到本地，服务器上就会删除该邮件，也正因为该特性，其只能下载邮件并将其标注为已读，已删除等。

IMAP协议在邮件服务器上保留有邮件的副本，并提供了更丰富的邮件管理功能。用户可以创建、重命名、删除邮件夹，标记邮件、设置标签、归档等。这些更高级的功能将**在服务器上进行操作**，并在所有连接到该服务器的设备上**同步**。