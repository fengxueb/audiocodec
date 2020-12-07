#include "util/util.h"
#include <stdio.h>
#include <stdlib.h>

namespace cppBase
{
	int readFileResource(const char* resPath, fileContent &content)
	{
		int ret = 0;
		FILE* fpRes = nullptr;
		char* pFileBuf = nullptr;
		unsigned int uFileLen = 0;

		do
		{
			if (resPath == nullptr)
			{
				ret = -1;
				break;
			}

			fpRes = fopen(resPath, "rb");
			if (fpRes == nullptr)
			{
				ret = -1;
				break;
			}

			fseek(fpRes, 0, SEEK_END);
			long fSize = ftell(fpRes);
			if (fSize <= 0)
			{
				ret = -1;
				break;
			}
			fseek(fpRes, 0, SEEK_SET);
			pFileBuf = new char[fSize];
			fread(pFileBuf, 1, fSize, fpRes);

			uFileLen = (unsigned int)fSize;
			content.pFile = pFileBuf;
			content.uFileLen = uFileLen;
		} while (0);

		if (ret != 0)
		{
			if (pFileBuf != nullptr)
				delete[] pFileBuf;
		}

		if (fpRes != nullptr)
		{
			fclose(fpRes);
		}

		return ret;
	}
}

