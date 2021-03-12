#include <string>
#include <iostream>
#include <mupdf/pdf.h>
#include <mupdf/fitz.h>
#include <vector>
#include <cstring>

using namespace std;

int extract_pdf(char* pdf_path, char** pageslist, char* out_path = "extract_out.pdf", char* password = NULL);  // 提取PDF pageslist分隔符为逗号，或者使用-表示范围
int merge_pdf(vector<string> pdf_path, int merge_nums, string out_path);  // 合并pdf，传入需要合并的PDF路径和输出文件路径
int pdf2img(string pdf_path, string img_path, int page_num = -1, float sx = 1.0, float sy = 1.0, int rotate = 0);  //pdf转图片

/*支持各种格式见的互转cbz, html, pdf, pam,pbm, pgm, pkm, png, ppm, pnm, svg, text, xhtml*/
int convert(vector<string> input_path, int input_num, const char* out_path, const char* format, const char* options, const char* password);  // 图片转PDF
