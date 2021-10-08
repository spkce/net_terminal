
#include "OrderMedia.h"
#include "Adapter.h"

namespace Screen
{

int COrderMedia::recordStart(Json::Value &request, Json::Value &response)
{
	//	AE_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::recordStop(Json::Value &request, Json::Value &response)
{
	//	AE_RECORD_STOP
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}

	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::eventRecordStart(Json::Value &request, Json::Value &response)
{
	//	AE_EVENT_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::audioRecordStart(Json::Value &request, Json::Value &response)
{
	//	AE_AUDIO_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::audioRecordStop(Json::Value &request, Json::Value &response)
{
	//	AE_AUDIO_RECORD_STOP
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::takePhoto(Json::Value &request, Json::Value &response)
{
	//AE_TAKE_PHOTO
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt()
		|| !request.isMember("type") || !request["type"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (CAdapter::instance()->takePhoto(request["chanNo"].asInt(), request["type"].asInt()))
	{
		return AE_SYS_NOERROR;
	}
	return AE_SYS_UNKNOWN_ERROR;
}

int COrderMedia::getVideoFileList(Json::Value &request, Json::Value &response)
{
	//AE_GET_VIDEO_FILE_LIST
	if (!request.isMember("index") || !request["index"].isUInt()
		|| !request.isMember("type") || !request["type"].isInt()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("pageSize") || !request["pageSize"].isUInt()
		|| !request.isMember("order") || !request["order"].isInt()
		|| !request.isMember("startTime") || !request["startTime"].isString()
		|| !request.isMember("stopTime") || !request["stopTime"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	FileCriteria_t fileCriteria = {0};
	fileCriteria.type = request["type"].asInt();
	fileCriteria.channel = request["chanNo"].asInt();
	strncpy(fileCriteria.startTime, request["startTime"].asCString(), sizeof(fileCriteria.startTime));
	strncpy(fileCriteria.stopTime, request["stopTime"].asCString(), sizeof(fileCriteria.stopTime));
	unsigned int fileNume = 0;

	void* pHandle = CAdapter::instance()->getFileList(0, &fileCriteria, &fileNume);
	if (pHandle == NULL)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	const size_t index = request["index"].asUInt();
	const size_t pageSize = request["pageSize"].asUInt();
	const int reverse =  request["order"].asInt();

	response["index"] = index;
	response["totalFileNum"] = fileNume;
	
	int ret = AE_SYS_NOERROR;
	
	for (size_t i = 0; i < fileNume; i++)
	{
		if (i < index)
		{
			FileInfo_t fileInfo = {0};
			if (!CAdapter::instance()->searchFileNext(reverse, pHandle, &fileInfo))
			{
				ret = AE_SYS_UNKNOWN_ERROR;
				break;
			}
		}
		else if (i < index + pageSize)
		{
			Json::Value info = Json::nullValue;
			FileInfo_t fileInfo = {0};
			if (!CAdapter::instance()->searchFileNext(reverse, pHandle, &fileInfo))
			{
				ret = AE_SYS_UNKNOWN_ERROR;
				break;
			}
			
			std::string fileName(fileInfo.name);
			//std::string thumbnail = fileName;
			//std::string gps = fileName;
			//thumbnail.replace(thumbnail.find_last_of('.') + 1, thumbnail.length() - thumbnail.find_last_of('.'), "thm");
			//gps.replace(gps.find_last_of('.') + 1, gps.length() - gps.find_last_of('.'), "txt");

			info["type"] = fileCriteria.type;
			info["chanNo"] = fileCriteria.channel;
			info["lock"] = fileInfo.lockState;
			info["fileSize"] = fileInfo.size;
			info["duration"] = fileInfo.duration;
			info["startTime"] = std::string(fileInfo.startTime);
			info["name"] = fileName;
			info["startLon"] = 0;
			info["startLat"] = 0;
		
			//info["thumbnail"] = thumbnail;
			//info["gps"] = gps;
			response["listing"].append(info);
		}
		else
		{
			break;
		}
	}

	CAdapter::instance()->searchHandleRelease(pHandle);
	return ret;
}

int COrderMedia::getImageFileList(Json::Value &request, Json::Value &response)
{
	//AE_GET_IMAGE_FILE_LIST
	if (!request.isMember("index") || !request["index"].isUInt()
		|| !request.isMember("type") || !request["type"].isInt()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("pageSize") || !request["pageSize"].isUInt()
		|| !request.isMember("order") || !request["order"].isInt()
		|| !request.isMember("startTime") || !request["startTime"].isString() || request["startTime"].asCString() == NULL
		|| !request.isMember("stopTime") || !request["stopTime"].isString() || request["stopTime"].asCString() == NULL)  
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	FileCriteria_t fileCriteria = {0};
	fileCriteria.type = request["type"].asInt();
	fileCriteria.channel = request["chanNo"].asInt();
	strncpy(fileCriteria.startTime, request["startTime"].asCString(), sizeof(fileCriteria.startTime) - 1);
	strncpy(fileCriteria.stopTime, request["stopTime"].asCString(), sizeof(fileCriteria.stopTime) - 1);
	unsigned int fileNume = 0;

	void* pHandle = CAdapter::instance()->getFileList(1, &fileCriteria, &fileNume);
	if (pHandle == NULL)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	const size_t index = request["index"].asUInt();
	const size_t pageSize = request["pageSize"].asUInt();
	const int reverse =  request["order"].asInt();

	response["index"] = index;
	response["totalFileNum"] = fileNume;

	int ret = AE_SYS_NOERROR;
	
	for (size_t i = 0; i < fileNume; i++)
	{
		if (i < index)
		{
			FileInfo_t fileInfo = {0};
			if (!CAdapter::instance()->searchFileNext(reverse, pHandle, &fileInfo))
			{
				ret = AE_SYS_UNKNOWN_ERROR;
				break;
			}
		}
		else if (i < index + pageSize)
		{
			Json::Value info = Json::nullValue;
			FileInfo_t fileInfo = {0};
			if (!CAdapter::instance()->searchFileNext(reverse, pHandle, &fileInfo))
			{
				ret = AE_SYS_UNKNOWN_ERROR;
				break;
			}
			
			std::string fileName(fileInfo.name);

			info["type"] = fileCriteria.type;
			info["chanNo"] = fileCriteria.channel;
			info["lock"] = fileInfo.lockState;
			info["fileSize"] = fileInfo.size;
			info["startTime"] = std::string(fileInfo.startTime);
			info["name"] = fileName;
			info["startLon"] = 0;
			info["startLat"] = 0;

			response["listing"].append(info);
		}
		else
		{
			break;
		}
	}

	CAdapter::instance()->searchHandleRelease(pHandle);
	return ret;
}

int COrderMedia::getStringFile(Json::Value &request, Json::Value &response)
{
	//AE_GET_STRING_MAP
	const char * path = CAdapter::instance()->getStringFile();
	if (path == NULL)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["path"] = std::string(path);
	return AE_SYS_NOERROR;
}

}//Screen
