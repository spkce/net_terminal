
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
 * @brief ��ʼ����׿��
 */
void net_termianl_init()
{
	//��ʼ����־����
	CLog* p = CLogManager::instance()->getLog("NetTerminal");
	p->setLogType(CLog::type_modMsg);
	p->setLogLevel(CLog::logLevel_5);
	
	Debug("NetTerminal", "screen init\n");
	//��׿������
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
 * @brief ��ȡ������ָ��
 * @return ������ָ��
 */
PADAPTER_T net_terminal_adapter_get()
{
	return CAdapter::instance()->getAdapter();
}

/**
 * @brief ��ȡ��׿������״̬
 * @return ���ߣ�true�����ߣ�false
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
 * @brief ��ȡ������ָ��
 * @param mod ģ������
 * @param level �ȼ� 4:�رգ�3:���еȼ� 2:trace������ 1:warning������ 0:error
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief ��ȡ�汾��Ϣ
 * @param buf ������ 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief �������Ƿ�Ϸ�
 * @param url ������·�� 
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief ��Ϣ����
 * @param buf ��Ϣ������ 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief GPS��������
 * @param buf GPS���ݻ����� 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief �����ԱȽ������
 * @param result �ԱȽ��
 * @param similarity ���ƶ�
 * @return �ɹ�������true��ʧ�ܣ�����false
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
 * @brief ����Բ�ε���Χ��
 * @param operate :����
 * @param p :����Χ����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_circle_area_set(int operate, void* p)
{
	/*Բ���������Խṹ��*/
	typedef struct
	{
		unsigned int uAreaId;		   /*����ID*/
		unsigned short usAreaProperty; /*��������*/
		unsigned char ucIsUsed;		   /*�Ƿ�ʹ��0-δʹ��,1-��ʹ��*/
		unsigned char ucIsInArea;	   /*�Ƿ���������,0-����,1-��*/

		unsigned int uCenterLatitude;	/*���ĵ�γ��*/
		unsigned int uCenterLongtitude; /*���ĵ㾭��*/

		unsigned int uRadius;			 /*�뾶*/
		unsigned char szBCDStartTime[6]; /*��ʼʱ��*/
		unsigned char szBCDEndTime[6];	 /*����ʱ��*/

		unsigned short usMaxSpeed;		   /*����ٶ�*/
		unsigned char ucOverSpeedDuration; /*���ٳ���ʱ��*/
		unsigned char ucRes;
	} CIRCLE_AREA_ITEM_T; /*size:40*/

	/*0x8600-����Բ��������Ϣ*/
	typedef struct
	{
		unsigned char ucSettingProperty;			   /*��������*/
		unsigned char ucTotalAreaNum;				   /*��������*/
		CIRCLE_AREA_ITEM_T stCircleArea[MAX_AREA_NUM]; /*������*/
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
 * @brief ���þ��ε���Χ��
 * @param operate :����
 * @param p :����Χ����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_rect_area_set(int operate, void* p)
{
	/*�����������Խṹ��*/
	typedef struct
	{
		unsigned int    uAreaId;			   /*����ID*/
		unsigned short   usAreaProperty;		   /**��������*/
		unsigned char    ucIsUsed;			   /*�Ƿ�ʹ��0-δʹ��,1-��ʹ��*/
		unsigned char    ucIsInArea;			   /*�Ƿ���������,0-����,1-��*/

		unsigned int    uLeftUpperLatitude;	   /*���ϵ�γ��*/
		unsigned int    uLeftUpperLongtitude;  /*���ϵ㾭��*/
		unsigned int    uRightLowerLatitude;   /*���µ�γ��*/
		unsigned int    uRightLowerLongtitude; /*���µ㾭��*/

		unsigned char   szBCDStartTime[6];		/*��ʼʱ��*/
		unsigned char   szBCDEndTime[6];		/*����ʱ��*/

		unsigned short  usMaxSpeed;			    /*����ٶ�*/
		unsigned char   ucOverSpeedDuration;	/*���ٳ���ʱ��*/
		unsigned char   ucRes;
	}RECTANGLE_AREA_ITEM_T;/*size:44*/

	/*0x8602-���þ���������Ϣ*/
	typedef struct
	{
		unsigned char ucSettingProperty;		/*��������*/
		unsigned char ucTotalAreaNum;			/*��������*/
		RECTANGLE_AREA_ITEM_T stRectangleArea[MAX_AREA_NUM];/*������*/
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
 * @brief ���ö���ε���Χ��
 * @param operate :����
 * @param p :����Χ����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_polygon_area_set(int operate, void* p)
{

	/*��������򶥵������Խṹ��*/
	typedef struct
	{
		unsigned int uVertexLatitude; 		/* ����γ��*/
		unsigned int uVertexLongtitude;		/*���㾭��*/
	}POLYGON_AREA_VERTEX_ITEM_T;/*size:8*/

	/*0x8604-���ö����������Ϣ*/
	typedef struct
	{
		unsigned int   uAreaId;				    /*����ID*/
		unsigned short usAreaProperty;		    /**��������*/
		unsigned short usTotalVertexNum;		/*�����ܶ�����*/

		unsigned char  szBCDStartTime[6];		/*��ʼʱ��*/
		unsigned char  szBCDEndTime[6];		    /*����ʱ��*/
		
		unsigned short usMaxSpeed;			    /*����ٶ�*/
		unsigned char  ucOverSpeedDuration;	    /*���ٳ���ʱ��*/
		unsigned char  ucIsUsed;				/*�Ƿ�ʹ��0-δʹ��,1-��ʹ��*/

		unsigned char  ucIsInArea;				/*�Ƿ���������,0-����,1-��*/
		unsigned char  szRes[3];
		
		POLYGON_AREA_VERTEX_ITEM_T stPolygonAreaVertex[MAX_POLYGON_VERTEX_NUM];/*������*/
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
 * @brief ����·��
 * @param operate :����
 * @param p :·����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_line_area_set(int operate, void* p)
{
	/*·�߹յ����Խṹ��*/
	typedef struct
	{
		unsigned int   uInflectionPointId;				/*�յ�ID*/
		unsigned int   uSectionId;						/*·��ID*/
		unsigned int   uInflectionPointLatitude;		/*�յ�γ��*/
		unsigned int   uInflectionPointLongtitude;		/*�յ㾭��*/
		
		unsigned char  ucSectionWidth;					/*·�ο��*/
		unsigned char  ucSectionProperty;				/*·������*/
		unsigned short usSectionTooEnoughThrehold;	    /*·����ʻ������ֵ*/
		
		unsigned short usSectionNotEnoughThrehold;	    /*·����ʻ������ֵ*/
		unsigned short usSectionMaxSpeed;				/*·������ٶ�*/
		
		unsigned char  ucSectionOverSpeedDuration;		/*·�γ�ʱ����ʱ��*/
		unsigned char  szRes[3];
	}ROUTE_INFLECTION_POINT_ITEM_T;/*size:28*/

	/*0x8606-����·����Ϣ��*/
	typedef struct
	{
		unsigned int   uRouteId;				/*·��ID*/
		unsigned short usRouteProperty;		    /*·������*/
		unsigned short usInflectionPointNum;	/*·���ܹյ���*/
			
		unsigned char  szBCDStartTime[6];		/*��ʼʱ��*/
		unsigned char  szBCDEndTime[6];		    /*����ʱ��*/
		unsigned char  ucIsUsed;				/*�Ƿ�ʹ�� 0-δʹ��,1-��ʹ��*/
		unsigned char  ucCurPointIndex;		    /*��ǰ�����յ�,��0��ʼ*/
		
		ROUTE_INFLECTION_POINT_ITEM_T stInflectionPoint[MAX_INFLECTION_POINT_NUM];/*�յ���*/
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
 * @brief ɾ������Χ��
 * @param type :����Χ������
 * @param total :ɾ������
 * @param pId :ɾ��ID�б�
 * @return �ɹ�������true��ʧ�ܣ�����false
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