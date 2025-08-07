# Makefile for C++ problems
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
TARGETS = $(basename $(wildcard *.cpp))

# 默认目标
all: $(TARGETS)

# 编译规则
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# 运行所有测试
run: all
	@echo "Running all tests..."
	@for target in $(TARGETS); do \
		echo "=== Running $$target ==="; \
		./$$target; \
		echo ""; \
	done

# 清理编译文件
clean:
	rm -f $(TARGETS)

.PHONY: all run clean 