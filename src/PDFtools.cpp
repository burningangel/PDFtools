// PDFtools.cpp: 定义应用程序的入口点。
//

#include <PDFtools.h>

int main(int argc, char** argv) {
	if (argc<2) {
		usage();
	}

	string this_type = *(++argv);
	argc -= 2;  // 去除前面两个数量
	if ("extract" == this_type) {
		
		if(argc<4){
			cout << "参数过少，请检查后重新输入！"<< endl;
			usage(this_type);
		}
		extract_main(argc, argv);
	}else if ("merge" == this_type) {
		if (argc < 3) {
			cout << "参数过少，请检查后重新输入！" << endl;
			usage(this_type);
		}
		merge_main(argc, argv);
	}else if ("toimg" == this_type) {
		if (argc < 2) {
			cout << "参数过少，请检查后重新输入！" << endl;
			usage(this_type);
		}
		toimg_main(argc, argv);
	}else if ("convert" == this_type) {
		if (argc < 3) {
			cout << "参数过少，请检查后重新输入！" << endl;
			usage(this_type);
		}
		convert_main(argc, argv);
	}else {
		cout << "不识别的命令 " << this_type << endl;
		usage();
	}
	return 0;
}


void usage(string com_type){
	string use_des="";
	if("extract" == com_type) {
		use_des = "用法：PDFtool extract [options]\n"
						 "\t-i\t\t--\t\t输入文件路径(必须)\n"
						 "\t-o\t\t--\t\t输出文件路径(必须)\n"
						 "\t-p\t\t--\t\t需要转换的页码（-1为全部转换）默认：-1\n"
						"\t-w\t\t--\t\t密码 默认：空\n";
	}else if("merge" == com_type) {
		use_des = "用法：PDFtool merge [options] file1 file2 ... fileN\n"
						 "\t-o\t\t--\t\t输出文件路径(必须)\n";
	}else if ("toimg" == com_type) {
		use_des = "用法：PDFtool toimg [options]\n"
						 "\t-i\t\t--\t\t输入文件路径(必须)\n"
						 "\t-o\t\t--\t\t输出目录路径，文件名以页码命名 默认：程序所在路径\n"
						 "\t-p\t\t--\t\t需要转换的页码（-1为全部转换）默认：-1\n"
						 "\t-x\t\t--\t\tX轴缩放比例 默认：1\n"
						 "\t-y\t\t--\t\tY轴缩放比例 默认：1\n"
						 "\t-r\t\t--\t\t旋转角度（0-360）默认：0\n";
	}else if ("convert" == com_type) {
		use_des = "用法：PDFtool convert [options] file1 file2 ... fileN\n"
						 "\t-o\t\t--\t\t输出文件路径(必须)\n"
						 "\t-f\t\t--\t\t输出文件的格式 默认：PDF\n"
						 "\t-O\t\t--\t\t逗号分隔的输出格式的参数 默认：空\n"
						 "\t-p\t\t--\t\t密码 默认：空\n";
	}else {
		use_des = "用法：PDFtool <command> [options]\n"
						  "\textract\t\t-- 提取PDF文件中的某几页\n"
						  "\tmerge\t\t-- 合并多个PDF文件为一个\n"
						  "\ttoimg\t\t-- 将PDF转换为图片\n"
						  "\tconvert\t\t-- 各种格式间互转(主要是图片转PDF，其他格式可能会有问题)（cbz, html, pdf, pam,pbm, pgm, pkm, png, ppm, pnm, svg, text, xhtml）\n";
	}
	cout << version << endl << use_des;
	exit(EXIT_SUCCESS);
}

void extract_main(int argc, char** argv){
	string this_type = *argv++;
	char *input_path = "";
	char *out_path = "";
	char *pages_num = "1-N";
	char *password = "";
	string command = pro_name + " " + this_type;

	for (int i = 0; i < argc; i++){
		string this_para = *argv;
		if ("-i"==this_para) {
			input_path = *(++argv);
			command += " -i "+string(input_path);
		}else if ("-o" == this_para) {
			out_path = *(++argv);
			command += " -o " + string(out_path);
		}else if ("-p" == this_para) {
			pages_num = *(++argv);
			command += " -p " + string(pages_num);
		}else if ("-w" == this_para) {
			password = *(++argv);
			command += " -w " + string(password);
		}else {
			cout << this_para  <<"不识别，请检查后再次输入！" << endl;
			usage(this_type);
		}
		argv++;
		argc -= 1; // 由于参数原因，每次需要跳过1个参数，因为i也在同时增长
	}
	if (strcmp(input_path,"")!=0 && strcmp(out_path,"")!=0) {
		cout << command << endl;
		int stat = extract_pdf(input_path,&pages_num,out_path,password);
		if (!stat) {
			cout << "提取成功！"<< endl;
		}
	}else {
		cout << command << endl;
		cout <<"必须参数缺少！"<<endl;
		usage(this_type);
	}
}

void merge_main(int argc, char** argv){
	string this_type = *argv++;
	vector <string> input_path;
	string out_path = "";
	string command = pro_name + " " + this_type;

	for (int i = 0; i < argc; i++) {
		string this_para = *argv;
		if ("-o" == this_para) {
			out_path = *(++argv);
			command += " -o " + out_path;
			argc -= 1;
		}else {
			command += " " + this_para;
			input_path.push_back(this_para);
		}
		argv++;
	}
	if (out_path!="") {
		cout << command << endl;
		int stat = merge_pdf(input_path, input_path.size(), out_path);
		if (!stat) {
			cout << "合并成功！" << endl;
		}
	}else {
		cout << command << endl;
		cout << "必须参数缺少！" << endl;
		usage(this_type);
	}
}

void toimg_main(int argc, char** argv){
	string this_type = *argv++;
	string input_path = "";
	string out_path = "";
	int pages_num = -1;
	float sx = 1;
	float sy = 1;
	int rotate = 0;
	string command = pro_name + " " + this_type;

	for (int i = 0; i < argc; i++) {
		string this_para = *argv;
		if ("-i" == this_para) {
			input_path = *(++argv);
			command += " -i " + input_path;
		}
		else if ("-o" == this_para) {
			out_path = *(++argv);
			out_path += "/";
			command += " -o " + out_path;
		}
		else if ("-p" == this_para) {
			pages_num = atoi(*(++argv));
			command += " -p " + to_string(pages_num);
		}
		else if ("-x" == this_para) {
			sx = atof(*(++argv));
			command += " -w " + to_string(sx);
		}
		else if ("-y" == this_para) {
			sy = atof(*(++argv));
			command += " -w " + to_string(sy);
		}
		else if ("-r" == this_para) {
			rotate = atoi(*(++argv));
			command += " -w " + to_string(rotate);
		}else {
			cout << this_para << "不识别，请检查后再次输入！" << endl;
			usage(this_type);
		}
		argv++;
		argc -= 1; // 由于参数原因，每次需要跳过1个参数，因为i也在同时增长
	}
	if (input_path!="") {
		cout << command << endl;

		int stat = pdf2img(input_path, out_path, pages_num, sx,sy,rotate);
		if (!stat) {
			cout << "转换图片成功！" << endl;
		}
	}else {
		cout << command << endl;
		cout << "必须参数缺少！" << endl;
		usage(this_type);
	}
}

void convert_main(int argc, char** argv){
	string this_type = *argv++;
	vector<string> input_path;
	char* out_path = NULL;
	string out_format = "pdf";
	char *out_option = NULL;
	string password = "";
	string command = pro_name + " " + this_type;

	for (int i = 0; i < argc; i++) {
		string this_para = *argv;
		if ("-o" == this_para) {
			out_path = *(++argv);
			command += " -o " + string(out_path);
		}else if ("-f" == this_para) {
			out_format = *(++argv);
			command += " -f " + out_format;
		}else if ("-O" == this_para) {
			out_option = *(++argv);
			command += " -O " + string(out_option);
		}else if ("-p" == this_para) {
			password = *(++argv);
			command += " -p " + password;
		}else {
			command += " " + this_para;
			input_path.push_back(this_para);
			argc++;
		}
		argv++;
		argc --; // 由于参数原因，每次需要跳过1个参数，因为i也在同时增长
	}
	if (out_path!="") {
		cout << command << endl;
		int stat = convert(input_path, input_path.size(), out_path, out_format.c_str(), out_option,password.c_str());
		if (!stat) {
			cout << "转换成功！" << endl;
		}
	}else {
		cout << command << endl;
		cout << "必须参数缺少！" << endl;
		usage(this_type);
	}
}
