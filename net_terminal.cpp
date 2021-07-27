
#include "stdio.h"
#include "net_terminal.h"
#include "Log.h"
#include "terminal.h"
#include "Adapter.h"
 #include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


Terminal::ITerminal * g_pScreen = NULL;

/**
 * @brief 初始化安卓屏
 */
void net_termianl_init()
{
	//初始化日志功能
	CLog* p = CLogManager::instance()->getLog("NetTerminal");
	p->setLogType(CLog::type_modMsg);
	p->setLogLevel(CLog::logLevel_5);
	
	Debug("NetTerminal", "screen init\n");
	//安卓屏创建
	g_pScreen = Terminal::ITerminal::createTerminal(Terminal::ITerminal::emTerminalScree);
	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "create screen fail\n");
		return ;
	}

	if (!g_pScreen->init())
	{
		Error("NetTerminal", "screen init fail\n");
		return ;
	}
}

/**
 * @brief 获取适配器指针
 * @return 适配器指针
 */
PADAPTER_T net_terminal_adapter_get()
{
	return CAdapter::instance()->getAdapter();
}

/**
 * @brief 获取安卓屏连接状态
 * @return 在线：true；离线：false
 */
int net_termianl_is_inline()
{
	if (g_pScreen == NULL)
	{
		return false;
	}

	if (g_pScreen->getState() == Terminal::ITerminal::emInline)
	{
		return true;
	}

	return false;
}

/**
 * @brief 获取适配器指针
 * @param mod 模块名字
 * @param level 等级 4:关闭，3:所有等级 2:trace及以上 1:warning及以上 0:error
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_debug_set(const char* mod, int level)
{
	CLog* p = CLogManager::instance()->findLog(mod);
	if (p == NULL)
	{
		return (int)false;
	}
	
	switch (level)
	{
	case 4:
		p->setLogLevel(CLog::logLevel_0);
		break;
	case 3:
		p->setLogLevel(CLog::logLevel_5);
		break;
	case 2:
		p->setLogLevel(CLog::logLevel_3);
		break;
	case 1:
		p->setLogLevel(CLog::logLevel_2);
		break;
	case 0:
		p->setLogLevel(CLog::logLevel_1);
		break;
	default:
		return (int)false;
	}
	return (int)true;
}
/**
 * @brief 获取版本信息
 * @param buf 缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_get_version(char* buf, unsigned int len)
{
	if (buf == NULL || len == 0)
	{
		return (int)false;
	}

	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return (int)false;
	}
	std::string ver;
	int ret = g_pScreen->getVersion(ver);
	if (ret)
	{
		strncpy(buf, ver.c_str(), (size_t)len);
	}
	
	return ret;
}

/**
 * @brief 升级包是否合法
 * @param url 升级包路径 
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_upgrade_check(const char* url)
{
	if (url == NULL)
	{
		return (int)false;
	}

	std::string urlStr(url);
	std::string filename = urlStr.substr(urlStr.find_last_of('/') + 1);
	Trace("NetTerminal", "filename = %s\n", filename.c_str());

	if (filename.find("update") != filename.npos)
	{
		return (int)true;
	}

	return (int)false;
}

/**
 * @brief 消息推送
 * @param buf 消息缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_notify(char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		return (int)false;
	}

	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return (int)false;
	}
	
	return (int)g_pScreen->notify(buf, len);
}

/**
 * @brief GPS数据推送
 * @param buf GPS数据缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_pushGPS(char* buf, int len)
{
	if (buf == NULL || len <= 0)
	{
		return (int)false;
	}

	if (g_pScreen == NULL)
	{
		Error("NetTerminal", "screen no initialization\n");
		return (int)false;
	}

	return (int)g_pScreen->pushGps(buf, len);
}

/**
 * @brief 人脸对比结果发送
 * @param result 对比结果
 * @param similarity 相似度
 * @return 成功：返回true；失败：返回false
 */
void net_terminal_face_contrast_result(int result, unsigned int similarity)
{
	char msg[sizeof(MSG_HDR_T) + sizeof(Notification_t)] = {0};
	PtrMsgHdr_t phdr = (PtrMsgHdr_t)msg;
	phdr->msgID = 601;
	PtrNotification_t pNotify = (PtrNotification_t)(msg + sizeof(MsgHdr_t));
	strncpy(pNotify->type, "faceResult", sizeof(pNotify->type));
	pNotify->faceResult.result = result;
	pNotify->faceResult.similarity = similarity;
	g_pScreen->notify(msg, sizeof(MsgHdr_t) + sizeof(Notification_t));
}

/**
 * @brief 设置圆形电子围栏
 * @param operate :操作
 * @param p :电子围栏信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_circle_area_set(int operate, void* p)
{
	/*圆形区域属性结构体*/
	typedef struct
	{
		unsigned int uAreaId;		   /*区域ID*/
		unsigned short usAreaProperty; /*区域属性*/
		unsigned char ucIsUsed;		   /*是否被使用0-未使用,1-已使用*/
		unsigned char ucIsInArea;	   /*是否在区域内,0-不在,1-在*/

		unsigned int uCenterLatitude;	/*中心点纬度*/
		unsigned int uCenterLongtitude; /*中心点经度*/

		unsigned int uRadius;			 /*半径*/
		unsigned char szBCDStartTime[6]; /*起始时间*/
		unsigned char szBCDEndTime[6];	 /*结束时间*/

		unsigned short usMaxSpeed;		   /*最高速度*/
		unsigned char ucOverSpeedDuration; /*超速持续时间*/
		unsigned char ucRes;
	} CIRCLE_AREA_ITEM_T; /*size:40*/

	/*0x8600-设置圆形区域消息*/
	typedef struct
	{
		unsigned char ucSettingProperty;			   /*设置属性*/
		unsigned char ucTotalAreaNum;				   /*区域总数*/
		CIRCLE_AREA_ITEM_T stCircleArea[MAX_AREA_NUM]; /*区域项*/
	} CIRCLE_AREA_ALARM_MSG_T;

	CIRCLE_AREA_ALARM_MSG_T* pCircle = (CIRCLE_AREA_ALARM_MSG_T*)p;
	if (pCircle == NULL)
	{
		return false;
	}
	
	char msg[sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2804;

	PAREA_INFO_T pArea = (PAREA_INFO_T)(msg + sizeof(MSG_HDR_T));
	pArea->areaNum = pCircle->ucTotalAreaNum;
	pArea->operate = operate;
	unsigned int i;
	for (i = 0; i < pArea->areaNum; i++)
	{
		pArea->area[i].type = 0;
		pArea->area[i].id = pCircle->stCircleArea[i].uAreaId;
		pArea->area[i].property = pCircle->stCircleArea[i].usAreaProperty;
		pArea->area[i].radius = pCircle->stCircleArea[i].uRadius;
		pArea->area[i].center.latitude = pCircle->stCircleArea[i].uCenterLatitude;
		pArea->area[i].center.longtitude = pCircle->stCircleArea[i].uCenterLongtitude;
		unsigned char *pStartBCDTime = pCircle->stCircleArea[i].szBCDStartTime;
		unsigned char *pEndBCDTime = pCircle->stCircleArea[i].szBCDEndTime;
		snprintf(pArea->area[i].startTime, sizeof(pArea->area[i].startTime), "%4d-%02d-%02d %02d:%02d:%02d",
			pStartBCDTime[0] + 2000, pStartBCDTime[1], pStartBCDTime[2], pStartBCDTime[3], pStartBCDTime[4], pStartBCDTime[5]);
		snprintf(pArea->area[i].endTime, sizeof(pArea->area[i].endTime), "%4d-%02d-%02d %02d:%02d:%02d",
			pEndBCDTime[0] + 2000, pEndBCDTime[1], pEndBCDTime[2], pEndBCDTime[3], pEndBCDTime[4], pEndBCDTime[5]);
	}

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)))
	{
		Trace("NetTerminal", "send circle success\n");
		return true;
	}
	else
	{
		Error("NetTerminal", "send circle fail\n");
		return false;
	}
}


/**
 * @brief 设置矩形电子围栏
 * @param operate :操作
 * @param p :电子围栏信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_rect_area_set(int operate, void* p)
{
	/*矩形区域属性结构体*/
	typedef struct
	{
		unsigned int    uAreaId;			   /*区域ID*/
		unsigned short   usAreaProperty;		   /**区域属性*/
		unsigned char    ucIsUsed;			   /*是否被使用0-未使用,1-已使用*/
		unsigned char    ucIsInArea;			   /*是否在区域内,0-不在,1-在*/

		unsigned int    uLeftUpperLatitude;	   /*左上点纬度*/
		unsigned int    uLeftUpperLongtitude;  /*左上点经度*/
		unsigned int    uRightLowerLatitude;   /*右下点纬度*/
		unsigned int    uRightLowerLongtitude; /*右下点经度*/

		unsigned char   szBCDStartTime[6];		/*起始时间*/
		unsigned char   szBCDEndTime[6];		/*结束时间*/

		unsigned short  usMaxSpeed;			    /*最高速度*/
		unsigned char   ucOverSpeedDuration;	/*超速持续时间*/
		unsigned char   ucRes;
	}RECTANGLE_AREA_ITEM_T;/*size:44*/

	/*0x8602-设置矩形区域消息*/
	typedef struct
	{
		unsigned char ucSettingProperty;		/*设置属性*/
		unsigned char ucTotalAreaNum;			/*区域总数*/
		RECTANGLE_AREA_ITEM_T stRectangleArea[MAX_AREA_NUM];/*区域项*/
	}RECTANGLE_AREA_ALARM_MSG_T;

	RECTANGLE_AREA_ALARM_MSG_T* pRect = (RECTANGLE_AREA_ALARM_MSG_T*)p;

	if (pRect == NULL)
	{
		return false;
	}
	
	char msg[sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2804;

	PAREA_INFO_T pArea = (PAREA_INFO_T)(msg + sizeof(MSG_HDR_T));
	pArea->areaNum = pRect->ucTotalAreaNum;
	pArea->operate = operate;
	unsigned int i;
	for (i = 0; i < pArea->areaNum; i++)
	{
		pArea->area[i].type = 1;
		pArea->area[i].id = pRect->stRectangleArea[i].uAreaId;
		pArea->area[i].property = pRect->stRectangleArea[i].usAreaProperty;
		pArea->area[i].leftPoint.latitude = pRect->stRectangleArea[i].uLeftUpperLatitude;
		pArea->area[i].leftPoint.longtitude = pRect->stRectangleArea[i].uLeftUpperLongtitude;
		pArea->area[i].rightPoint.latitude = pRect->stRectangleArea[i].uRightLowerLatitude;
		pArea->area[i].rightPoint.longtitude = pRect->stRectangleArea[i].uRightLowerLongtitude;
		unsigned char *pStartBCDTime = pRect->stRectangleArea[i].szBCDStartTime;
		unsigned char *pEndBCDTime = pRect->stRectangleArea[i].szBCDEndTime;
		snprintf(pArea->area[i].startTime, sizeof(pArea->area[i].startTime), "%4d-%02d-%02d %02d:%02d:%02d",
			pStartBCDTime[0] + 2000, pStartBCDTime[1], pStartBCDTime[2], pStartBCDTime[3], pStartBCDTime[4], pStartBCDTime[5]);
		snprintf(pArea->area[i].endTime, sizeof(pArea->area[i].endTime), "%4d-%02d-%02d %02d:%02d:%02d",
			pEndBCDTime[0] + 2000, pEndBCDTime[1], pEndBCDTime[2], pEndBCDTime[3], pEndBCDTime[4], pEndBCDTime[5]);
	}

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)))
	{
		Trace("NetTerminal", "send rectangle success\n");
		return true;
	}
	else
	{
		Error("NetTerminal", "send rectangle fail\n");
		return false;
	}
}

/**
 * @brief 设置多边形电子围栏
 * @param operate :操作
 * @param p :电子围栏信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_polygon_area_set(int operate, void* p)
{

	/*多边形区域顶点项属性结构体*/
	typedef struct
	{
		unsigned int uVertexLatitude; 		/* 顶点纬度*/
		unsigned int uVertexLongtitude;		/*顶点经度*/
	}POLYGON_AREA_VERTEX_ITEM_T;/*size:8*/

	/*0x8604-设置多边形区域消息*/
	typedef struct
	{
		unsigned int   uAreaId;				    /*区域ID*/
		unsigned short usAreaProperty;		    /**区域属性*/
		unsigned short usTotalVertexNum;		/*区域总顶点数*/

		unsigned char  szBCDStartTime[6];		/*起始时间*/
		unsigned char  szBCDEndTime[6];		    /*结束时间*/
		
		unsigned short usMaxSpeed;			    /*最高速度*/
		unsigned char  ucOverSpeedDuration;	    /*超速持续时间*/
		unsigned char  ucIsUsed;				/*是否被使用0-未使用,1-已使用*/

		unsigned char  ucIsInArea;				/*是否在区域内,0-不在,1-在*/
		unsigned char  szRes[3];
		
		POLYGON_AREA_VERTEX_ITEM_T stPolygonAreaVertex[MAX_POLYGON_VERTEX_NUM];/*顶点项*/
	}POLYGON_AREA_ALARM_MSG_T;

	POLYGON_AREA_ALARM_MSG_T* pPolygon = (POLYGON_AREA_ALARM_MSG_T*)p;
	if (pPolygon == NULL)
	{
		return false;
	}
	
	char msg[sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2804;

	PAREA_INFO_T pArea = (PAREA_INFO_T)(msg + sizeof(MSG_HDR_T));
	pArea->areaNum = 1;
	pArea->operate = operate;
	
	pArea->area[0].type = 2;
	pArea->area[0].id = pPolygon->uAreaId;
	pArea->area[0].property = pPolygon->usAreaProperty;
	pArea->area[0].vertexNum = pPolygon->usTotalVertexNum;
	
	GPS_POINT* pPoint = pArea->area[0].vertex;
	unsigned int i;
	for (i = 0; i < pPolygon->usTotalVertexNum; i++)
	{
		pPoint[i].latitude = pPolygon->stPolygonAreaVertex[i].uVertexLatitude;
		pPoint[i].longtitude = pPolygon->stPolygonAreaVertex[i].uVertexLongtitude;

	}

	unsigned char *pStartBCDTime = pPolygon->szBCDStartTime;
	unsigned char *pEndBCDTime = pPolygon->szBCDEndTime;
	snprintf(pArea->area[0].startTime, sizeof(pArea->area[0].startTime), "%4d-%02d-%02d %02d:%02d:%02d",
		pStartBCDTime[0] + 2000, pStartBCDTime[1], pStartBCDTime[2], pStartBCDTime[3], pStartBCDTime[4], pStartBCDTime[5]);
	snprintf(pArea->area[0].endTime, sizeof(pArea->area[0].endTime), "%4d-%02d-%02d %02d:%02d:%02d",
		pEndBCDTime[0] + 2000, pEndBCDTime[1], pEndBCDTime[2], pEndBCDTime[3], pEndBCDTime[4], pEndBCDTime[5]);
	
	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)))
	{
		Trace("NetTerminal", "send polygon success\n");
		return true;
	}
	else
	{
		Error("NetTerminal", "send polygon fail\n");
		return false;
	}
}

/**
 * @brief 设置路线
 * @param operate :操作
 * @param p :路线信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_line_area_set(int operate, void* p)
{
	/*路线拐点属性结构体*/
	typedef struct
	{
		unsigned int   uInflectionPointId;				/*拐点ID*/
		unsigned int   uSectionId;						/*路段ID*/
		unsigned int   uInflectionPointLatitude;		/*拐点纬度*/
		unsigned int   uInflectionPointLongtitude;		/*拐点经度*/
		
		unsigned char  ucSectionWidth;					/*路段宽度*/
		unsigned char  ucSectionProperty;				/*路段属性*/
		unsigned short usSectionTooEnoughThrehold;	    /*路段行驶过长阈值*/
		
		unsigned short usSectionNotEnoughThrehold;	    /*路段行驶不足阈值*/
		unsigned short usSectionMaxSpeed;				/*路段最高速度*/
		
		unsigned char  ucSectionOverSpeedDuration;		/*路段超时持续时间*/
		unsigned char  szRes[3];
	}ROUTE_INFLECTION_POINT_ITEM_T;/*size:28*/

	/*0x8606-设置路线消息体*/
	typedef struct
	{
		unsigned int   uRouteId;				/*路线ID*/
		unsigned short usRouteProperty;		    /*路线属性*/
		unsigned short usInflectionPointNum;	/*路线总拐点数*/
			
		unsigned char  szBCDStartTime[6];		/*起始时间*/
		unsigned char  szBCDEndTime[6];		    /*结束时间*/
		unsigned char  ucIsUsed;				/*是否被使用 0-未使用,1-已使用*/
		unsigned char  ucCurPointIndex;		    /*当前所处拐点,从0开始*/
		
		ROUTE_INFLECTION_POINT_ITEM_T stInflectionPoint[MAX_INFLECTION_POINT_NUM];/*拐点项*/
	}ROUTE_SET_MSG_T;

	ROUTE_SET_MSG_T* pline = (ROUTE_SET_MSG_T*)p;

	if (pline == NULL)
	{
		return false;
	}
	
	char msg[sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2804;

	PAREA_INFO_T pArea = (PAREA_INFO_T)(msg + sizeof(MSG_HDR_T));
	pArea->areaNum = 1;
	pArea->operate = operate;
	
	pArea->area[0].type = 3;
	pArea->area[0].id = pline->uRouteId;
	pArea->area[0].property = pline->usRouteProperty;
	pArea->area[0].pointNum = pline->usInflectionPointNum;
	

	GPS_POINT* pPoint = pArea->area[0].inflctPoint;
	unsigned int* pWidth = pArea->area[0].lineWidth;
	unsigned int i;
	for (i = 0; i < pline->usInflectionPointNum; i++)
	{
		pPoint[i].latitude = pline->stInflectionPoint[i].uInflectionPointLatitude;
		pPoint[i].longtitude = pline->stInflectionPoint[i].uInflectionPointLongtitude;
		pWidth[i] = pline->stInflectionPoint[i].ucSectionWidth;
	}

	unsigned char *pStartBCDTime = pline->szBCDStartTime;
	unsigned char *pEndBCDTime = pline->szBCDEndTime;
	snprintf(pArea->area[0].startTime, sizeof(pArea->area[0].startTime), "%4d-%02d-%02d %02d:%02d:%02d",
		pStartBCDTime[0] + 2000, pStartBCDTime[1], pStartBCDTime[2], pStartBCDTime[3], pStartBCDTime[4], pStartBCDTime[5]);
	snprintf(pArea->area[0].endTime, sizeof(pArea->area[0].endTime), "%4d-%02d-%02d %02d:%02d:%02d",
		pEndBCDTime[0] + 2000, pEndBCDTime[1], pEndBCDTime[2], pEndBCDTime[3], pEndBCDTime[4], pEndBCDTime[5]);
	
	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)))
	{
		Trace("NetTerminal", "send line success\n");
		return true;
	}
	else
	{
		Error("NetTerminal", "send line fail\n");
		return false;
	}
}

/**
 * @brief 删除电子围栏
 * @param type :电子围栏属性
 * @param total :删除总数
 * @param pId :删除ID列表
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_area_delete(int type, unsigned int total, unsigned int * pId)
{
	if (total > MAX_AREA_NUM)
	{
		Error("NetTerminal", "delete area too many ! \n");
		return false;
	}

	if (pId == NULL)
	{
		Error("NetTerminal", "input area id error ! \n");
		return false;
	}

	char msg[sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2804;

	PAREA_INFO_T pArea = (PAREA_INFO_T)(msg + sizeof(MSG_HDR_T));
	pArea->areaNum = total;
	pArea->operate = 3;
	
	for (size_t i = 0; i < total; i++)
	{
		pArea->area[i].type = type;
		pArea->area[i].id = pId[i];
	}
	
	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(AREA_INFO_T)))
	{
		Trace("NetTerminal", "send delete area success\n");
		return true;
	}
	else
	{
		Error("NetTerminal", "send delete area fail\n");
		return false;
	}
}

#ifdef __cplusplus
}
#endif