## fs

文件系统包含文件和目录：
1. 文件就是一个简单的字节数组
2. 目录（特殊的文件）包含指向文件和其他目录的引用

最直观的理解就是当我们使用`read`函数读取一个普通文件时，可以使用一个字符数组接受读取内容，当读取目录文件时，读取的内容是包含`dirent`结构体的数组，对应于该目录下的所有文件。

文件名和文件本身有很大区别，文件本质上对应于磁盘上的一个Inode，但在文件系统上，可能有多个文件名对应于磁盘上的同一个Inode，我们称这些文件名为`links`。

### 相关函数

1. `fstat`：获取一个文件描述符指向的文件的信息（填充一个`stat`的结构体，见下文）
2. ``


```c++
#define T_DIR 1
#define T_FILE 2
#define T_DEV 3
// Directory
// File
// Device
struct stat {
    short type; // Type of file
    int dev; // File system’s disk device
    uint ino; // Inode number
    short nlink; // Number of links to file
    uint size; // Size of file in bytes
};
```