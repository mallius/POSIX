#!/bin/bash

#运行程序检查内存泄漏
valgrind --leak-check=full --show-reachable=yes $1
