## fs
> 实验基于`xv6`操作系统，和`unix`的结构有所不同，可见`kernel`下的结构体定义，下面介绍的均为`unix`中的结构体定义

```c
// fstat(int fd, struct stat * st);
struct stat { 
    dev_t st_dev; // 文件所在设备ID 
    ino_t st_ino; // 结点(inode)编号  
    mode_t st_mode; // 保护模式 
    nlink_t st_nlink; // 硬链接个数  
    uid_t st_uid; // 所有者用户ID  
    gid_t st_gid; // 所有者组ID  
    dev_t st_rdev; // 设备ID(如果是特殊文件) 
    off_t st_size; // 总体尺寸，以字节为单位 
    blksize_t st_blksize; // 文件系统 I/O 块大小
    blkcnt_t st_blocks; // 已分配 512B 块个数
    time_t st_atime; // 上次访问时间 
    time_t st_mtime; // 上次更新时间 
    time_t st_ctime; // 上次状态更改时间 
};
```

```c
struct dirent   
{   
　　long d_ino; /* inode number 索引节点号 */  
    off_t d_off; /* offset to this dirent 在目录文件中的偏移 */  
    unsigned short d_reclen; /* length of this d_name 文件名长 */  
    unsigned char d_type; /* the type of d_name 文件类型 */  
    char d_name [NAME_MAX+1]; /* file name (null-terminated) 文件名，最长255字符 */  
}  
```

```c
struct __dirstream   
   {   
    void *__fd;    
    char *__data;    
    int __entry_data;    
    char *__ptr;    
    int __entry_ptr;    
    size_t __allocation;    
    size_t __size;    
    __libc_lock_define (, __lock)    
   };   
  
typedef struct __dirstream DIR;  
```

Q: 如果要获取某目录下指定文件的详情信息，可以怎么操作？

A：
1. `DIR *opendir(const char *pathname)`
2. `struct dirent *readdir(DIR *dp); `
3. `int stat(const char *file_name, struct stat *buf);`

## dir/file

`read(int fd, void * buf, size_t count)`，当fd代表普通文件时，容易理解，将该普通文件的内容存储到buf中，如果fd代表目录时，buf里面的内容是`dirent`结构体