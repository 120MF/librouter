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

## 测试

- 确保Boost库已安装；
- 按照上文编译；
- 编译出`librouter_benchmark`可执行文件，运行即可进行性能测试；
- 可使用CTest测试Dijkstra算法实现的正确性。样例随机生成，使用Boost的Dijkstra算法进行检验。

```shell
cd build
./librouter_benchmark
# benchmark...
ctest -R TestDijkstraCorrectnes --extra-verbose
# correctness test...
```

## 大概不会实现

- [ ] 路由器对象独立消息队列
- [ ] 路由器间同步存储路由表
- [ ] 消息收发

## 待实现

- [x] Dijkstra 多线程任务队列
- [x] ConcurrentHashmap

## 待完善

- [ ] PriorityQueue的resize功能
- [ ] PriorityQueue确认优先级比较方式的Template
- [ ] HashCompute分离
- [x] doxygen文档

## Credit

- [bs_thread_pool](https://github.com/bshoshany/thread-pool)
- [stduuid](https://github.com/mariusbancila/stduuid)
- [Google Benchmark](https://github.com/google/benchmark)
- [Boost C++ Library](https://www.boost.org/)