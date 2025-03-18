# CXX = g++
# TARGET = main
# SRC = $(wildcard *.cpp)
# BUILD_DIR = build
# OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))  # 关键修改：添加 build/ 前缀

# CXXFLAGS = -c -Wall -pthread

# # 默认目标：先创建 build 目录，再编译主程序
# $(TARGET): $(BUILD_DIR) $(OBJ)
# 	$(CXX) -o $@ $(OBJ) 

# # 编译 .cpp 到 build/*.o
# $(BUILD_DIR)/%.o: %.cpp
# 	$(CXX) $(CXXFLAGS) $< -o $@ 

# # 创建 build 目录（如果不存在）
# $(BUILD_DIR):
# 	mkdir -p $@

# # 清理：删除 build 目录和可执行文件
# .PHONY: clean
# clean:
# 	rm -rf $(BUILD_DIR) $(TARGET)


# -------------------------

TARGET = main
SRC = $(wildcard *.cpp)
BUILD_DIR = build
OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC))

# 编译选项：-pthread 确保多线程头文件和宏定义正确
CXXFLAGS = -c -Wall -pthread
# 链接选项：-pthread 确保链接多线程库
LDFLAGS = -pthread

# 默认目标：先创建 build 目录，再编译主程序
$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ)

# 编译 .cpp 到 build/*.o
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# 创建 build 目录（如果不存在）
$(BUILD_DIR):
	mkdir -p $@

# 清理：删除 build 目录和可执行文件
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)