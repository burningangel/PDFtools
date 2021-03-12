#include <PDFdeal.h>


int extract_pdf(char *pdf_path, char **pageslist, char *out_path,char *password){
	int count = 1;  //源代码中是为了获取后续的命令行参数，这里不用
	fz_context* ctx = NULL;
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx) {
		cerr << "程序异常，不能创建mupdf上下文" << endl;
		exit(EXIT_FAILURE);
	}
	
	pdf_write_options this_write = pdf_default_write_options;
	pdf_clean_file(ctx, pdf_path, out_path, password, &this_write,count,pageslist);  // 提取PDF
	fz_drop_context(ctx);
	return EXIT_SUCCESS;
}

int merge_pdf(vector<string> pdf_path, int merge_nums, string out_path) {
	pdf_write_options this_write = pdf_default_write_options;
	fz_context *dst_ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED); 
	fz_context *src_ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!dst_ctx||!src_ctx) {
		cerr << "程序异常，不能创建mupdf上下文" << endl;
		exit(EXIT_FAILURE);
	}
	
	pdf_document* out_pdf = pdf_create_document(dst_ctx);

	for (int i = 0;i< merge_nums;i++) {
		const char *this_path = pdf_path[i].c_str();  // 每个文件的路径
		pdf_document *input_pdf = pdf_open_document(src_ctx, this_path);
		pdf_graft_page(dst_ctx, out_pdf, -1, input_pdf, 0);
		//pdf_graft_mapped_page();
		pdf_drop_document(src_ctx, input_pdf);
		input_pdf = NULL;
	}
	
	pdf_save_document(dst_ctx, out_pdf, out_path.c_str(), &this_write);
	pdf_drop_document(dst_ctx, out_pdf);

	fz_flush_warnings(src_ctx);
	fz_drop_context(src_ctx);
	fz_drop_context(dst_ctx);
	return EXIT_SUCCESS;
}

int pdf2img(string pdf_path, string img_path, int page_num,float sx, float sy, int rotate){
	int page_count = 0;  //页数
	fz_context* ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	fz_document* pdf = NULL;
	fz_pixmap* pix = NULL;
	
	fz_matrix ctm = fz_scale(sx,sy);  // 缩放0-1  取0时会出错
	ctm = fz_pre_rotate(ctm, rotate);  // 旋转-360

	if (!ctx) {
		cerr << "程序异常，不能创建mupdf上下文" << endl;
		exit(EXIT_FAILURE);
	}

	/* Register the default file types to handle. */
	fz_register_document_handlers(ctx);
	pdf = fz_open_document(ctx, pdf_path.c_str());
	page_count = fz_count_pages(ctx, pdf);

	if (page_num == -1 || page_num-1 > page_count) {
		//打印所有页
		cout << "打印全页" << endl;
		for (int i = 0; i < page_count; i++) {  // pdf 从0开始计算页数
			cout << "开始打印第" << i+1 << "页"<< endl;
			string this_file_name = img_path + to_string(i+1) + ".png";
			pix = fz_new_pixmap_from_page_number(ctx, pdf, i, ctm, fz_device_rgb(ctx), 0);

			fz_save_pixmap_as_png(ctx, pix, this_file_name.c_str());
			fz_drop_pixmap(ctx, pix);
		}
	}
	else {
		//打印指定页
		cout << "打印指定页:" << page_num << endl;
		string this_file_name = img_path + to_string(page_num) + ".png";
		pix = fz_new_pixmap_from_page_number(ctx, pdf, page_num-1, ctm, fz_device_rgb(ctx), 0);
		
		fz_save_pixmap_as_png(ctx, pix, this_file_name.c_str());
		fz_drop_pixmap(ctx, pix);
		
	}

	fz_drop_document(ctx, pdf);
	fz_drop_context(ctx);
	return EXIT_SUCCESS;

}

int convert(vector<string> input_path, int input_num, const char* out_path, const char* format, const char* options, const char* password){
	fz_context* ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	fz_document_writer *out;
	fz_document *input_doc;
	
	//float layout_w = 21.1;
	//float layout_h = 30.0;
	//float layout_em = 14.0;
	fz_register_document_handlers(ctx);
	out = fz_new_document_writer(ctx, out_path, format, options);
	
	for (int i = 0; i < input_num; i++) {
		input_doc = fz_open_document(ctx, input_path[i].c_str());
		if (fz_needs_password(ctx, input_doc)) {
			if (!fz_authenticate_password(ctx, input_doc, password)){
				cout << "文件：" << input_path[i] << "需要密码" << endl;
				exit(EXIT_FAILURE);
			}
		}
		//fz_layout_document(ctx, input_doc, layout_w, layout_h, layout_em);  // 设置转出文件大小
		fz_write_document(ctx,out,input_doc);  // 写入文档
		fz_drop_document(ctx, input_doc);
		input_doc = NULL;
	}
	
	fz_close_document_writer(ctx, out);
	fz_drop_document_writer(ctx, out);
	fz_drop_context(ctx);
	return EXIT_SUCCESS;
}


