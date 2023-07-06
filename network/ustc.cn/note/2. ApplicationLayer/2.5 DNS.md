## DNS
> DNS(Domain Name System)

为什么会有该系统？

IP地址标识主机，路由器，若想要对某一主机进行通信，则需要知道其IP地址，但是IPV4地址的点分十进制较难记忆，人们更习惯于记忆有意义的字符串，故需要该系统来实现字符串-IP地址的转换。

上面论述了域名系统的必要性和主要目的，除此之外，域名系统还可以用于实现`别名`+`负载均衡`。

三个问题：

1. 如何命名设备？（如何保证命名不冲突？）
2. 如何完成命名到IP地址的转换？
3. 如何维护？（增加或删除一个域，需要在域名系统中如何处理？）

### DNS命名空间
> 对于整个世界数一亿级的设备，保证不重复的命名也是一个具有挑战性的工作。

一个层次命名会有很多重名，因此DNS采用层次树状结构命名，Internet根被划分为几百个顶级域（通用的 e.g. .edu,.com,.gov / 国家的 e.g. .cn,.us,.jp...），每个域下面又被划分为若干子域，树叶就是具体的主机。

域名：从本域往上，直到树根，中间使用`.`间隔不同的级别。域的域名表示一个域，主机的域名表示一个域上的一个主机。

域名的管理：一个域被划分为几个子域，例如：`.cn`被划分为`yzh.cn`和`xxx.cn`两个子域，创建一个新的域需要征求其所属域的同意，且域是逻辑划分，并非物理划分，也即处于同一域下的两个主机可能不在同一网络。

### 域名解析
> 域名解析需要依赖于名字服务器，维护着它所管辖区域的权威信息

权威DNS服务器：组织机构的DNS服务器， 提供组织机构服务器（如Web和mail）可访问的主机和IP之间的映射。（DNS解析中大部分记录都在该服务器上）

顶级域(TLD)服务器：负责顶级域名（如 com, org, net,edu和gov）和所有国家级的顶级域名（如cn, fr, ca,jp ），存储有权威DNS服务器的域名。

根域名服务器：存储有顶级域服务器的域名。

DNS记录：RR（resource records）格式（NAME,VALUE,TYPE,TTL）

1. Type=A：Name为主机，Value为IP地址
2. Type=CNAME：NAME为规范命名的别名，VALUE为规范命名
    1. `www.ibm.com` 的规范名字为 `servereast.backup2.ibm.com`
3. Type=NS：NAME为域名，VALUE为该域名的权威服务器域名
4. Type=MX：VALUE为NAME对应的邮件服务器的别名

[解析过程可参考该文章中DNS查询部分](https://yzh2002.cn/2022/10/21/%E4%B8%80%E9%81%93%E7%BB%8F%E5%85%B8%E9%9D%A2%E8%AF%95%E9%A2%98/#more)

关键词：递归/迭代查询，缓存

### DNS报文
> DNS请求和响应的报文格式相同

1. 报文头部（Header）：包含以下字段：
    1. 16 位标识符（ID）：用于标识该请求的唯一标识符。
    2. 标志位（Flags）：包括操作码（Opcode）、查询类型（Query Type）、查询类（Query Class）等信息。
    3. 问题计数（Question Count）：指示查询的问题数目。
    4. 回答计数（Answer Count）：指示回答记录的数目。
    5. 权威记录计数（Authority Count）：指示权威记录的数目。
    6. 附加记录计数（Additional Count）：指示附加记录的数目。
2. 问题部分（Question Section）：包含一个或多个问题（Queries），每个问题包括以下字段：
    1. 域名（Domain Name）：要查询的域名。
    2. 查询类型（Type）：指定查询的资源记录类型，如 A、MX、CNAME 等。
    3. 查询类（Class）：指定查询的资源记录类别，通常为 IN（Internet）。
    4. 其他部分（Additional Section）：可选部分，包含附加的资源记录，如指向权威服务器的 NS 记录。

### 如何维护？新增一个域

1. 在上级域的名字服务器中增加两条记录，指向这个新增的子域的域名 和 域名服务器的地址
2. 在新增子域的名字服务器上运行名字服务器，负责本域的名字解析： 名字->IP地址

例子：在com域中建立一个“Network Utopia”

1. 到注册登记机构注册域名networkutopia.com
    1. 需要向该机构提供权威DNS服务器（基本的、和辅助的）的名字和IP地址
    2. 登记机构在com TLD服务器中插入两条RR记录:`(networkutopia.com, dns1.networkutopia.com, NS)`，`(dns1.networkutopia.com, 212.212.212.1, A)`
2. 在networkutopia.com的权威服务器中确保有
    1. 用于Web服务器的www.networkuptopia.com的类型为 A的记录
    2. 用于邮件服务器 mail.networkutopia.com的类型为MX的记录

