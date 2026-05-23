# Linux_Study

这是一个面向 Linux 嵌入式学习的实验仓库，内容覆盖：

- Linux 下 C 程序基础编译（`make` / `cmake`）
- 本地与交叉编译流程实践
- Shell 构建脚本编写
- GPIO LED 字符设备驱动开发（内核模块）
- 配套学习文档（`.docx` / `.pdf`）

## 项目结构概览

- `Linux&Makefile/`  
  C 语言与构建系统基础实验：单文件编译、多源文件、头文件与静态库组织。

- `Shell/`  
  使用 Shell 脚本驱动 CMake/Make 的本地构建与交叉编译流程示例。

- `gpio_led_driver/`  
  一个简单的 Linux 字符设备驱动示例：通过 `/dev/gpioled` 写入 `1/0` 控制 LED 亮灭。

- 根目录学习资料（`.docx` / `.pdf`）  
  记录 Linux 开发板连接、buildroot、工具链与调试等学习过程。

## 关键实验说明

### 1) Linux&Makefile
- `hello.c` + `Makefile`：使用交叉编译前缀构建基础可执行程序。
- `CMakeLists.txt`：CMake 版本的最小 Hello 示例。
- `多源文件实验/`：多文件工程组织与编译。
- `添加头文件目录并制作使用静态库/`：静态库构建、链接与头文件目录管理。

### 2) Shell
- `本地/`：本机工具链构建并运行 `myapp`。
- `交叉编译/`：通过 `toolchain.cmake` 指定 ARM 工具链，验证输出为 ARM 可执行文件。

### 3) gpio_led_driver
- `gpioled.c`：GPIO 申请、字符设备注册、`write` 接口控制 LED。
- `Makefile`：外部内核模块编译方式（`obj-m`）。
- `build.sh`：在 `build/` 目录中集中生成构建产物。
- `push.sh`：示例部署脚本（`scp` 到开发板）。

## 快速上手

> 以下命令建议在对应目录内执行。

### Linux&Makefile（Make）
```bash
cd "Linux&Makefile"
make
```

### Shell 本地构建
```bash
cd "Shell/本地"
bash build_and_run.sh
```

### Shell 交叉编译
```bash
cd "Shell/交叉编译"
bash build_and_run.sh
```

### GPIO 驱动构建
```bash
cd gpio_led_driver
bash build.sh
```

## 使用与环境注意事项

- 本仓库部分实验目录包含历史 `build/` 缓存，迁移到新机器后可能出现 CMake cache 路径不一致报错；可删除对应 `build/` 后重新配置。
- 交叉编译与内核模块构建依赖本地工具链与内核源码路径，需根据自己的开发环境修改：
  - `Shell/交叉编译/toolchain.cmake`
  - `gpio_led_driver/Makefile` 中 `KDIR`、`CROSS_COMPILE`
- `push.sh` 中目标板 IP 与登录信息为示例值，请按实际环境替换。

## 适用人群

适合正在学习以下主题的同学：

- Linux 应用层 C 工程构建
- CMake/Make 基础与工程组织
- ARM 交叉编译入门
- Linux 字符设备驱动入门（GPIO 控制）

