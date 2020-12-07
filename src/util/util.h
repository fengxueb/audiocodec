
namespace cppBase 
{
	struct fileContent 
	{
		const char* pFile;
		unsigned int uFileLen;
	};

	int readFileResource(const char* resPath, fileContent &content);
}
