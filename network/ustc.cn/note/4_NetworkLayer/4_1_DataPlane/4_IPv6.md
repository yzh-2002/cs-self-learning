## IPv6

### SR
> 基于源节点的路由机制（源节点负责确定数据包的完整路径，而路径中的每个中间节点都根据源节点提供的路由信息进行数据包转发。相对的是基于目的节点的路由机制）

IPv6的段路由机制（`Segment Router`），指在IPv6数据包头和`payload`之间添加一个路由扩展头SRH。

该扩展头的结构如下：
```
header srv6h_t {
    bit<8>   next_hdr;
    bit<8>   hdr_ext_len;
    bit<8>   routing_type;
    bit<8>   segment_left; //指示数据包下一跳
    bit<8>   last_entry;
    bit<8>   flags;
    bit<16>  tag;
    srv6_list_t[] sl; //显示指定ipv6路径
    bit<128> option_tlv;
}
header srv6_list_t {
    bit<128>  segment_id;
}


```

### 主机&链路发现

IPv6中主机发现协议为：`NDP（邻居发现协议）`，作用有：
1. 邻居发现（`NS+NA`）
2. 地址解析（类似于`ARP`）
3. 邻居状态检测（周期性发包）

`LLDP`是链路层的发现协议，不是网络层协议，这一点需要注意。
`BDDP`是