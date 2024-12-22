## 实现功能

- 路由表的增删节点/边
- 自动维护路由表并给出各节点的最短路径

## 编译

- 安装CMake(version >= 3.26)
- 使用CMake+ninja(或make)编译

```shell
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cd build
ninja
```

## 大概不会实现

- [ ] 路由器对象独立消息队列
- [ ] 路由器间同步存储路由表
- [ ] 消息收发

## 待实现

- [ ] Dijkstra 多线程任务队列
- [ ] data_structure线程安全

## 待完善

- [ ] PriorityQueue的resize功能
- [ ] data_structure的拷贝函数
- [ ] doxygen文档

## Credit

- [bs_thread_pool](https://github.com/bshoshany/thread-pool)
- [stduuid](https://github.com/mariusbancila/stduuid)