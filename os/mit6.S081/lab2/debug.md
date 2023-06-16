## debug

> lab2主要内容是调试xv6内核文件，理解其启动过程，遇到一些问题，特此记录

### riscv64-linux-gnu-gdb?

mit6.s081的实验我是在wsl（Ubuntu 20.04）上进行的，xv6的实验环境部署之后并没有标题中的gdb。故需要自己安装riscv交叉编译工具

1. `$ wget https://static.dev.sifive.com/dev-tools/riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14.tar.gz`
2. `$ sudo tar -xvf riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14.tar.gz -C /opt/`
3. 在`~/.bashrc`中添加`export PATH=$PATH:/opt/riscv64-unknown-elf-gcc-8.3.0-2020.04.1-x86_64-linux-ubuntu14/bin`
4. `source ~/.bashrc`

调试内核文件：

1. `sudo make qemu-gdb`:启动qemu，并打开其内部的gdb-server
2. `riscv64-unknown-elf-gdb kernel/kernel`
3. gdb中执行`target remote localhost:<port>`与第一步打开的gdb-server建立连接，之后即可开始调试

### how to debug?
