### PDFtools 小工具
#### 一、介绍
当前工具基于mupdf实现了PDF文件的切分、合并、PDF转图片、图片转PDF等功能。
#### 安装
本工具提供了windows和linux（基于Ubuntu）的使用包，可以通过下方链接进行下载。

[windows](https://github.com/burningangel/PDFtools/releases/download/v1.0.0/PDFtools_win32_v1.0.0.zip)
[linux](https://github.com/burningangel/PDFtools/releases/download/v1.0.0/PDFtools_linux_v1.0.0.zip)

或者也可以通过源码进行编译安装
```
git clone https://github.com/burningangel/PDFtools.git
cd PDFtools
cmake CMakeLists.txt
make
```
#### 使用
使用比较简单，在软件目录下运行PDFtools会有功能提示。选择你想要的功能进行,其中结尾包含必须的参数不可缺少。
主要功能如下：
```
PDFtools version 1.0.0
用法：PDFtool <command> [options]
        extract         -- 提取PDF文件中的某几页
        merge           -- 合并多个PDF文件为一个
        toimg           -- 将PDF转换为图片
        convert         -- 各种格式间互转(主要是图片转PDF，其他格式可能会有问题)（cbz, html, pdf, pam,pbm, pgm, pkm, png, ppm, pnm, svg, text, xhtml）
```
#### 例子
##### 1、PDF文件提取
```
PDFtools.exe extract -i BWT.pdf -o 1.pdf -p 1-2,4-5
```
在该步骤需要注意的是，在输入需要提取的页码时，页码可以是纯数字，也可以是逗号分隔的几个数字，或者用-连接的连续几页。

##### 2、PDF文件合并
```
PDFtools.exe merge -o merge.pdf 1.pdf 2.pdf
```
该功能简单，仅需输入一个-o参数，表示合并后的文件路径，后面接着需要合并的多个文件即可。

##### 3、PDF转图片
```
PDFtools.exe toimg -i 1.pdf
```
该功能也比较简单，必须参数仅-i一个，即需要转换的PDF文件路径，输出文件路径不指定的话默认是程序当前路径下（需要注意的是，输出-o指定的是输出目录，而不是输出文件的路径），输出的文件按照页码进行命名。同时结合其他参数可以进行图片的缩放，旋转等。

##### 4、图片转PDF
```
PDFtools.exe convert -o tran.pdf -f pdf 1.png
```
该功能除了图片转PDF外，还支持cbz, html, pdf, pam,pbm, pgm, pkm, png, ppm, pnm, svg, text, xhtml等格式的互转，但是可能会有点小问题，我暂时没进行测试。

需要注意的是当前功能的-O选项，该参数可以对输出格式进行进一步的限制，见下方所示。（以下来源于mupdf官网）

```
Image output
CBZ (comic book zip) is a multi-page image format.

The following single page image formats are also supported: PNG, PNM, PAM, PBM, PKM. Each page is written to a separate file.

The output options (-O flag) for image formats are:

rotate=N
Rotate rendered pages N degrees counter-clockwise.
resolution=N
Set both X and Y resolution in pixels per inch.
x-resolution=N
Set X resolution in pixels per inch.
y-resolution=N
Set Y resolution in pixels per inch.
width=N
Render pages to fit N pixels wide (ignore resolution options).
height=N
Render pages to fit N pixels tall (ignore resolution options).
colorspace=gray/rgb/cmyk
Render using specified colorspace (if output format supports it).
alpha
Render pages with an alpha channel and transparent background (if output format supports it).
PDF output
With PDF output, we will create a new PDF file that matches the visual appearance. The PDF output is still a work in progress, so some features may not work.

If the input is PDF, the output will have nothing in common except the visual appearance. All bookmarks, annotations, forms, etc, will be thrown away. If you want to do a PDF to PDF conversion, 'mutool clean' is a better tool to use.

The PDF output options are:

decompress
Decompress all streams (except compress-fonts/images).
compress
Compress all streams.
compress-fonts
Compress embedded fonts.
compress-images
Compress images.
ascii
ASCII hex encode binary streams.
pretty
Pretty-print objects with indentation.
linearize
Optimize for web browsers.
sanitize
Clean up graphics commands in content streams.
garbage
Garbage collect unused objects.
garbage=compact
... and compact cross reference table.
garbage=deduplicate
... and remove duplicate objects.
SVG output
SVG output is a single page format, so we will write one SVG file for each input page.

The SVG output options are:

text=text
Emit text as elements (inaccurate fonts).
text=path
Emit text as elements (accurate fonts).
no-reuse-images
Do not reuse images using <symbol> definitions.
```
