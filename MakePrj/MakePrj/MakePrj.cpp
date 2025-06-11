// MakePrj.cpp		创建控制台应用程序的工程文件（MinGW Developer Studio及Code::Blocks）
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <io.h>
#include <direct.h>
using namespace std;

int GetFiles(string path, string ext, vector<string> &filenames)
{
	long hFile = 0;					// 搜索文件用的句柄
	struct _finddata_t fileinfo;	// 存储文件信息的结构体变量
	string p;
	if(path[path.length()-1]=='\\' || path[path.length()-1]=='/')
		path.resize(path.length()-1);

	if((hFile=_findfirst(p.assign(path).append("\\*").append(ext).c_str(), &fileinfo)) != -1)
	{
		do
		{
			filenames.push_back(p.assign(path).append("\\").append(fileinfo.name));
		}while(_findnext(hFile, &fileinfo)==0);		// 查找下一个文件
		_findclose(hFile);
	}
	return filenames.size();		// 返回找到的文件个数
}

void GetCurDir(char *curdir)
{
	vector<string> filenames;
	char str[200], CURDIR[200];
	int i, n;

	_getdcwd(0, str, 200);
	for(i=strlen(str)-1; i>=0 && str[i]!='\\'; i--)
		;
	strcpy(curdir, str+i+1);       // 仅取出最后一级子目录的名称
	strcpy(CURDIR, curdir);
	strupr(CURDIR);

	cout << "当前文件夹：" << curdir << endl;

	n = GetFiles(".", ".c", filenames);
	n += GetFiles(".", ".cpp", filenames);
	n += GetFiles(".", ".h", filenames);
	if(n==0)
	{
		cout << "\n新建如下文件" << endl;
		strcpy(str, curdir);
		strcat(str, ".cpp");
		ofstream outfile(str);
		outfile << "// " << str << endl;
		outfile << "#include \"" << curdir << ".h\"\n" << endl;
		outfile.close();
		cout << str;

		strcpy(str, curdir);
		strcat(str, ".h");
		outfile.open(str);
		outfile << "// " << str << endl;
		outfile << "#ifndef MY_" << CURDIR << "_H" << endl;
		outfile << "#define MY_" << CURDIR << "_H" << endl;
		outfile << "\n\n#endif" << endl;
		outfile.close();
		cout << ", " << str;

		strcpy(str, curdir);
		strcat(str, "Main.cpp");
		outfile.open(str);
		outfile << "// " << str << endl;
		outfile << "#include <iostream>" << endl;
		outfile << "#include <iomanip>" << endl;
		outfile << "#include \"" << curdir << ".h\"" << endl;
		outfile << "using namespace std;\n" << endl;
		outfile << "int main()\n{" << endl;
		outfile << "\treturn 0;\n}" << endl;
		outfile.close();
		cout << ", " << str << endl;
	}
}

int CreateMDSP(char *prjName)
{
	vector<string> cNames, cppNames, hNames;
	int cNum, cppNum, hNum, k;
	char str[200];
	ofstream outfile;

	strcpy(str, prjName);
	strcat(str, ".mdsp");
	outfile.open(str);

	cNum = GetFiles(".", ".c", cNames);
	cppNum = GetFiles(".", ".cpp", cppNames);
	hNum = GetFiles(".", ".h", hNames);

	outfile << "[Project]" << endl;
	outfile << "name=" << prjName << endl;
	outfile << "type=0" << endl;
	outfile << "defaultConfig=0\n" << endl;
	outfile << "[Debug]" << endl;
	outfile << "// compiler " << endl;
	outfile << "workingDirectory=" << endl;
	outfile << "arguments=" << endl;
	outfile << "intermediateFilesDirectory=Debug" << endl;
	outfile << "outputFilesDirectory=Debug" << endl;
	outfile << "compilerPreprocessor=" << endl;
	outfile << "extraCompilerOptions=" << endl;
	outfile << "compilerIncludeDirectory=" << endl;
	outfile << "noWarning=0" << endl;
	outfile << "defaultWarning=0" << endl;
	outfile << "allWarning=1" << endl;
	outfile << "extraWarning=0" << endl;
	outfile << "isoWarning=0" << endl;
	outfile << "warningsAsErrors=0" << endl;
	outfile << "debugType=1" << endl;
	outfile << "debugLevel=2" << endl;
	outfile << "exceptionEnabled=1" << endl;
	outfile << "runtimeTypeEnabled=1" << endl;
	outfile << "optimizeLevel=0\n" << endl;
	outfile << "// linker" << endl;
	outfile << "libraryPath=" << endl;
	outfile << "outputFilename=Debug\\" << prjName << ".exe" << endl;
	outfile << "libraries=" << endl;
	outfile << "extraLinkerOptions=" << endl;
	outfile << "ignoreStartupFile=0" << endl;
	outfile << "ignoreDefaultLibs=0" << endl;
	outfile << "stripExecutableFile=0\n" << endl;
	outfile << "// archive" << endl;
	outfile << "extraArchiveOptions=\n" << endl;
	outfile << "//resource" << endl;
	outfile << "resourcePreprocessor=" << endl;
	outfile << "resourceIncludeDirectory=" << endl;
	outfile << "extraResourceOptions=\n" << endl;
	outfile << "[Release]" << endl;
	outfile << "// compiler " << endl;
	outfile << "workingDirectory=" << endl;
	outfile << "arguments=" << endl;
	outfile << "intermediateFilesDirectory=Release" << endl;
	outfile << "outputFilesDirectory=Release" << endl;
	outfile << "compilerPreprocessor=" << endl;
	outfile << "extraCompilerOptions=" << endl;
	outfile << "compilerIncludeDirectory=" << endl;
	outfile << "noWarning=0" << endl;
	outfile << "defaultWarning=0" << endl;
	outfile << "allWarning=1" << endl;
	outfile << "extraWarning=0" << endl;
	outfile << "isoWarning=0" << endl;
	outfile << "warningsAsErrors=0" << endl;
	outfile << "debugType=0" << endl;
	outfile << "debugLevel=0" << endl;
	outfile << "exceptionEnabled=1" << endl;
	outfile << "runtimeTypeEnabled=1" << endl;
	outfile << "optimizeLevel=2\n" << endl;
	outfile << "// linker" << endl;
	outfile << "libraryPath=" << endl;
	outfile << "outputFilename=Release\\" << prjName << ".exe" << endl;
	outfile << "libraries=" << endl;
	outfile << "extraLinkerOptions=" << endl;
	outfile << "ignoreStartupFile=0" << endl;
	outfile << "ignoreDefaultLibs=0" << endl;
	outfile << "stripExecutableFile=1\n" << endl;
	outfile << "// archive" << endl;
	outfile << "extraArchiveOptions=\n" << endl;
	outfile << "//resource" << endl;
	outfile << "resourcePreprocessor=" << endl;
	outfile << "resourceIncludeDirectory=" << endl;
	outfile << "extraResourceOptions=\n" << endl;
	outfile << "[Source]" << endl;

	for(k=0; k<cNum; k++)
		outfile << k+1 << "=" << cNames[k] << endl;
	for(k=0; k<cppNum; k++)
		outfile << cNum+k+1 << "=" << cppNames[k] << endl;

	outfile << "[Header]" << endl;
	for(k=0; k<hNum; k++)
		outfile << k+1 << "=" << hNames[k] << endl;
	outfile << "[Resource]" << endl;
	outfile << "[Other]" << endl;
	outfile << "[History]" << endl;
	for(k=0; k<cNum; k++)
		outfile << cNames[k] << ", 0" << endl;
	for(k=0; k<cppNum; k++)
		outfile << cppNames[k] << ", 0" << endl;
	for(k=0; k<hNum; k++)
		outfile << hNames[k] << ", 0" << endl;
	outfile.close();
	cout << str << " -- Win32 Console Application工程文件(MinGW Developer Studio)" << endl;

	return 0;
}

int CreateCBP(char *prjName)
{
	vector<string> cNames, cppNames, hNames;
	int cNum, cppNum, hNum, k;
	char strCBP[200], strLayout[200];

	strcpy(strCBP, prjName);
	strcat(strCBP, ".cbp");
	strcpy(strLayout, prjName);
	strcat(strLayout, ".layout");

	ofstream cbpfile(strCBP), layoutfile(strLayout);

	cNum = GetFiles(".", ".c", cNames);
	cppNum = GetFiles(".", ".cpp", cppNames);
	hNum = GetFiles(".", ".h", hNames);

	cbpfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>" << endl;
	cbpfile << "<CodeBlocks_project_file>" << endl;
	cbpfile << "	<FileVersion major=\"1\" minor=\"6\" />" << endl;
	cbpfile << "	<Project>" << endl;
	cbpfile << "		<Option title=\"" << prjName << "\" />" << endl;
	cbpfile << "		<Option pch_mode=\"2\" />" << endl;
	cbpfile << "		<Option compiler=\"gcc\" />" << endl;
	cbpfile << "		<Build>" << endl;
	cbpfile << "			<Target title=\"Debug\">" << endl;
	cbpfile << "				<Option output=\"bin/Debug/" << prjName << "\" prefix_auto=\"1\" extension_auto=\"1\" />" << endl;
	cbpfile << "				<Option object_output=\"obj/Debug/\" />" << endl;
	cbpfile << "				<Option type=\"1\" />" << endl;
	cbpfile << "				<Option compiler=\"gcc\" />" << endl;
	cbpfile << "				<Compiler>" << endl;
	cbpfile << "					<Add option=\"-g\" />" << endl;
	cbpfile << "				</Compiler>" << endl;
	cbpfile << "			</Target>" << endl;
	cbpfile << "			<Target title=\"Release\">" << endl;
	cbpfile << "				<Option output=\"bin/Release/" << prjName << "\" prefix_auto=\"1\" extension_auto=\"1\" />" << endl;
	cbpfile << "				<Option object_output=\"obj/Release/\" />" << endl;
	cbpfile << "				<Option type=\"1\" />" << endl;
	cbpfile << "				<Option compiler=\"gcc\" />" << endl;
	cbpfile << "				<Compiler>" << endl;
	cbpfile << "					<Add option=\"-O2\" />" << endl;
	cbpfile << "				</Compiler>" << endl;
	cbpfile << "				<Linker>" << endl;
	cbpfile << "					<Add option=\"-s\" />" << endl;
	cbpfile << "				</Linker>" << endl;
	cbpfile << "			</Target>" << endl;
	cbpfile << "		</Build>" << endl;
	cbpfile << "		<Compiler>" << endl;
	cbpfile << "			<Add option=\"-Wall\" />" << endl;
	cbpfile << "			<Add option=\"-fexceptions\" />" << endl;
	cbpfile << "		</Compiler>" << endl;
	for(k=0; k<cNum; k++)
		cbpfile << "<Unit filename=\"" << cNames[k] << "\" />" << endl;
	for(k=0; k<cppNum; k++)
		cbpfile << "<Unit filename=\"" << cppNames[k] << "\" />" << endl;
	for(k=0; k<hNum; k++)
		cbpfile << "<Unit filename=\"" << hNames[k] << "\" />" << endl;
	cbpfile << "		<Extensions>" << endl;
	cbpfile << "			<code_completion />" << endl;
	cbpfile << "			<envvars />" << endl;
	cbpfile << "			<debugger />" << endl;
	cbpfile << "			<lib_finder disable_auto=\"1\" /> " << endl;
	cbpfile << "		</Extensions>" << endl;
	cbpfile << "	</Project>" << endl;
	cbpfile << "</CodeBlocks_project_file>" << endl;
	cbpfile.close();

	layoutfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>" << endl;
	layoutfile << "<CodeBlocks_layout_file>" << endl;
	layoutfile << "	<FileVersion major=\"1\" minor=\"0\" />" << endl;
	layoutfile << "	<ActiveTarget name=\"Debug\" />" << endl;

	int active=1;
	for(k=0; k<cNum; k++)
	{
		layoutfile << "	<File name=\"" << cNames[k] << "\" open=\"1\" top=\"";
		layoutfile << active;
		if(active==1) active=0;
		layoutfile << "\" tabpos=\"1\" split=\"0\" active=\"1\" splitpos=\"0\" zoom_1=\"0\" zoom_2=\"0\">" << endl;
		layoutfile << "		<Cursor>" << endl;
		layoutfile << "			<Cursor1 position=\"0\" topLine=\"0\" />" << endl;
		layoutfile << "		</Cursor>" << endl;
		layoutfile << "	</File>" << endl;
	}
	for(k=0; k<cppNum; k++)
	{
		layoutfile << "	<File name=\"" << cppNames[k] << "\" open=\"1\" top=\"";
		layoutfile << active;
		if(active==1) active=0;
		layoutfile << "\" tabpos=\"1\" split=\"0\" active=\"1\" splitpos=\"0\" zoom_1=\"0\" zoom_2=\"0\">" << endl;
		layoutfile << "		<Cursor>" << endl;
		layoutfile << "			<Cursor1 position=\"0\" topLine=\"0\" />" << endl;
		layoutfile << "		</Cursor>" << endl;
		layoutfile << "	</File>" << endl;
	}
	for(k=0; k<hNum; k++)
	{
		layoutfile << "	<File name=\"" << hNames[k] << "\" open=\"1\" top=\"";
		layoutfile << active;
		if(active==1) active=0;
		layoutfile << "\" tabpos=\"1\" split=\"0\" active=\"1\" splitpos=\"0\" zoom_1=\"0\" zoom_2=\"0\">" << endl;
		layoutfile << "		<Cursor>" << endl;
		layoutfile << "			<Cursor1 position=\"0\" topLine=\"0\" />" << endl;
		layoutfile << "		</Cursor>" << endl;
		layoutfile << "	</File>" << endl;
	}
	layoutfile << "</CodeBlocks_layout_file>" << endl;
	layoutfile.close();
	cout << strCBP << ", " << strLayout << " -- Console Application 工程文件(Code::Blocks)" << endl;

	return 0;
}

int CreateDEV(char *prjName)
{
	vector<string> cNames, cppNames, hNames;
	int cNum, cppNum, hNum, k;
	char str[200];
	ofstream devfile;

	strcpy(str, prjName);
	strcat(str, ".dev");
	devfile.open(str);

	cNum = GetFiles(".", ".c", cNames);
	cppNum = GetFiles(".", ".cpp", cppNames);
	hNum = GetFiles(".", ".h", hNames);

	devfile << "[Project]" << endl;
	devfile << "FileName=" << str << endl;
	devfile << "Name=" << prjName << endl;
	devfile << "UnitCount=" << cNum + cppNum + hNum << endl;
	devfile << "Type=1" << endl;
	devfile << "Ver=1" << endl;
	devfile << "ObjFiles=" << endl;
	devfile << "Includes=" << endl;
	devfile << "Libs=" << endl;
	devfile << "PrivateResource=" << endl;
	devfile << "ResourceIncludes=" << endl;
	devfile << "MakeIncludes=" << endl;
	devfile << "Compiler=" << endl;
	devfile << "CppCompiler=" << endl;
	devfile << "Linker=" << endl;
	devfile << "IsCpp=1" << endl;
	devfile << "Icon=" << endl;
	devfile << "ExeOutput=.\\Dev_Debug\\" << endl;
	devfile << "ObjectOutput=.\\Dev_Debug\\" << endl;
	devfile << "OverrideOutput=0" << endl;
	devfile << "OverrideOutputName=" << endl;
	devfile << "HostApplication=" << endl;
	devfile << "Folders=" << endl;
	devfile << "CommandLine=" << endl;
	devfile << "UseCustomMakefile=0" << endl;
	devfile << "CustomMakefile=" << endl;
	devfile << "IncludeVersionInfo=0" << endl;
	devfile << "SupportXPThemes=0" << endl;
	devfile << "CompilerSet=0" << endl;
	devfile << "CompilerSettings=0000000000000000000000" << endl;
	devfile << endl;
	devfile << "[VersionInfo]" << endl;
	devfile << "Major=0" << endl;
	devfile << "Minor=1" << endl;
	devfile << "Release=1" << endl;
	devfile << "Build=1" << endl;
	devfile << "LanguageID=1033" << endl;
	devfile << "CharsetID=1252" << endl;
	devfile << "CompanyName=" << endl;
	devfile << "FileVersion=" << endl;
	devfile << "FileDescription=Developed using the Dev-C++ IDE" << endl;
	devfile << "InternalName=" << endl;
	devfile << "LegalCopyright=" << endl;
	devfile << "LegalTrademarks=" << endl;
	devfile << "OriginalFilename=" << endl;
	devfile << "ProductName=" << endl;
	devfile << "ProductVersion=" << endl;
	devfile << "AutoIncBuildNr=0\n" << endl;

	for(k=0; k<cNum; k++)
	{
		devfile << "[Unit" << k+1 << "]" << endl;
		devfile << "FileName=" << cNames[k] << endl;
		devfile << "CompileCpp=1" << endl;
		devfile << "Folder=" << endl;
		devfile << "Compile=1" << endl;
		devfile << "Link=1" << endl;
		devfile << "Priority=1000" << endl;
		devfile << "OverrideBuildCmd=0" << endl;
		devfile << "BuildCmd=\n" << endl;
	}
	for(k=0; k<cppNum; k++)
	{
		devfile << "[Unit" << cNum+k+1 << "]" << endl;
		devfile << "FileName=" << cppNames[k] << endl;
		devfile << "CompileCpp=1" << endl;
		devfile << "Folder=" << endl;
		devfile << "Compile=1" << endl;
		devfile << "Link=1" << endl;
		devfile << "Priority=1000" << endl;
		devfile << "OverrideBuildCmd=0" << endl;
		devfile << "BuildCmd=\n" << endl;
	}
	for(k=0; k<hNum; k++)
	{
		devfile << "[Unit" << cNum+cppNum+k+1 << "]" << endl;
		devfile << "FileName=" << hNames[k] << endl;
		devfile << "CompileCpp=1" << endl;
		devfile << "Folder=" << endl;
		devfile << "Compile=1" << endl;
		devfile << "Link=1" << endl;
		devfile << "Priority=1000" << endl;
		devfile << "OverrideBuildCmd=0" << endl;
		devfile << "BuildCmd=\n" << endl;
	}
	devfile.close();
	cout << str << " -- Dev-C++ Win32 Console Application工程文件(Dev-C++)" << endl;
	return 0;
}
