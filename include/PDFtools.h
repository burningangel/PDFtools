// PDFtools.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once

#include <PDFdeal.h>


// TODO: 在此处引用程序需要的其他标头。
using namespace std;
string pro_name = "PDFtools";
string version = "PDFtools version 1.0.0";
void usage(string com_type="all");
void extract_main(int argc, char** argv);
void merge_main(int argc, char** argv);
void toimg_main(int argc, char** argv);
void convert_main(int argc, char** argv);