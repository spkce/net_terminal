
/*APP -> DEVICE消息ID*/
/****************************************BEGIN****************************************/
/*扩展EHOME协议*/
/*系统类命令*/
#define AE_GET_ALL_CURRENT_SETTINGS             (1)         /*获取所有设置的当前参数*/
#define AE_GET_BATTERY_LEVEL		            (2)         /*获取电池状态*/
#define AE_GET_CAMERAS_STATUS                   (3)         /*获取所有通道接入和录像状态*/
#define AE_GET_GSENSOR_DATA                     (4)         /*获取设备G-sensor数据*/
#define AE_GET_GPS                              (5)         /*获取当前GPS坐标*/
#define AE_GET_DEVICE_INFO                      (6)         /*获取设备信息*/
#define AE_GET_VEHICLE_INFO                     (8)         /*获取车辆相关信息*/
#define AE_SET_VEHICLE_INFO                     (9)         /*设置车辆相关信息*/
#define AE_GET_DRIVER_INFO                      (10)        /*获取驾驶员相关信息*/
#define AE_SET_DRIVER_INFO                      (11)        /*设置驾驶员相关信息*/

#define AE_GET_SATELLITE_INFO                   (19)        /*获取设备当前的搜星信息*/

#define AE_GET_PICTURE_SETTING                  (186)       /*获取图像设置*/
#define AE_SET_PICTURE_SETTING                  (187)       /*设置图像设置*/
#define AE_GET_COMPRESS_SETTING                 (188)       /*获取压缩设置*/
#define AE_SET_COMPRESS_SETTING                 (189)       /*设置压缩设置*/

#define AE_GET_IMAGE_SETTING                    (190)       /*获取图片设置*/
#define AE_SET_IMAGE_SETTING                    (191)       /*设置图片设置*/
#define AE_GET_GENERIC_SETTING                  (192)       /*获取通用设置*/
#define AE_SET_GENERIC_SETTING                  (193)       /*设置通用设置*/
#define AE_GET_PROMPT_SETTING                   (194)       /*获取提醒设置*/
#define AE_SET_PROMPT_SETTING                   (195)       /*设置提醒设置*/
#define AE_GET_ALERT_SETTING                    (196)       /*获取告警设置*/
#define AE_SET_ALERT_SETTING                    (197)       /*设置告警设置*/
#define AE_GET_SENSOR_SETTING                   (198)       /*获取传感设置*/
#define AE_SET_SENSOR_SETTING                   (199)       /*设置传感设置*/

/*媒体命令*/
#define AE_RECORD_START                         (201)       /*开启录像*/
#define AE_RECORD_STOP                          (202)       /*关闭录像*/
#define AE_EVENT_RECORD_START                   (203)       /*开启紧急录像*/
#define AE_AUDIO_RECORD_START                   (204)       /*开启音频录像*/
#define AE_AUDIO_RECORD_STOP                    (205)       /*关闭音频录像*/

/*网络接口类命令*/
#define AE_WIFI_RESTART                         (301)       /*启动wifi*/
#define AE_GET_STA_PARAM                        (302)       /*获取STA参数*/
#define AE_SET_STA_PARAM                        (303)       /*设置STA参数*/
#define AE_GET_AP_PARAM                         (304)       /*获取AP参数*/
#define AE_SET_AP_PARAM                         (305)       /*设置AP参数*/
#define AE_GET_4G_PARAM                         (306)       /*获取4G参数*/
#define AE_SET_4G_PARAM                         (307)       /*设置4G参数*/
#define AE_GET_NETWORK_SETTING                  (398)       /*获取网络设置*/
#define AE_SET_NETWORK_SETTING                  (399)       /*设置网络设置*/

/*存储类命令*/
#define AE_GET_SD_LETTER                        (401)       /*获取已插入盘符*/
#define AE_GET_SD_INFO                          (402)       /*获取SD信息*/
#define AE_SET_SD_LOCK_STATUS                   (403)       /*设置SD锁状态*/
#define AE_SET_SD_PASSWD                        (404)       /*设置SD密码*/
#define AE_FORMAT                               (405)       /*格式化SD卡*/
#define AE_GET_RECORD_SCHEDILE                  (406)       /*获取录像计划*/
#define AE_SET_RECORD_SCHEDILE                  (407)       /*设置录像计划*/
#define AE_COPY_DAY_SCHEDILE                    (408)       /*复制一天的录像计划*/
#define AE_COPY_CHANNEL_SCHEDILE                (409)       /*复制一个通道的录像计划*/
#define AE_GET_STORAGE_SETTING                  (498)       /*获取存储设置*/
#define AE_SET_STORAGE_SETTING                  (499)       /*设置存储设置*/
#define AE_EXPORT_MEDIA_FILE					(410)		/*设备媒体文件导出到外部存储设备*/
#define AE_EXPORT_LOG							(411)		/*设备日志导出到外部存储设备*/
#define AE_EXPORT_CONFIG                        (414)       /*将设备中的配置文件导入到外部设备*/
#define AE_INPORT_CONFIG						(415)		/*将外部设备中的配置文件导入到设备*/
#define AE_CONCEL_EXPORT						(416)		/*取消文件导出*/

/*时间类命令*/
#define AE_GET_DAYLIGHT_TIME                    (501)       /*获取夏令时*/
#define AE_SET_DAYLIGHT_TIME                    (502)       /*设置夏令时*/
#define AE_GET_TIMEZONE                         (503)       /*获取时区*/
#define AE_SET_TIMEZONE                         (504)       /*设置时区*/
#define AE_GET_TIME_SETTING                     (598)       /*获取时间设置*/
#define AE_SET_TIME_SETTING                     (599)       /*设置时间设置*/

/*通知类命令*/
#define AE_NOTIFICATION                         (601)       /*通知类消息*/

/*平台连接类命令*/
#define AE_GET_PLATFORM_CONN_INFO               (701)       /*获取平台信息*/
#define AE_SET_PLATFORM_CONN_INFO               (702)       /*设置平台信息*/
#define AE_GET_808_CONN_INFO                    (703)       /*获取808参数信息*/
#define AE_SET_808_CONN_INFO                    (704)       /*设置808参数信息*/
#define AE_GET_808_CONN_INFO_2                  (705)       /*获取808_2参数信息*/
#define AE_SET_808_CONN_INFO_2                  (706)       /*设置808_2参数信息*/
#define AE_GET_OPERATE_PLATFORM_INFO            (707)       /*获取运维平台参数信息*/
#define AE_SET_OPERATE_PLATFORM_INFO            (708)       /*设置运维平台参数信息*/
#define AE_GET_NTP_PLATFORM_INFO                (709)       /*获取NTP平台参数信息*/
#define AE_SET_NTP_PLATFORM_INFO                (710)       /*设置NTP平台参数信息*/

/*人脸命令*/
#define AE_GET_FACE_INFO                        (922)      /*获取设备存储的人脸信息*/
#define AE_SET_FACE_INFO                        (923)      /*设置设备存储的人脸信息*/
#define AE_GET_OVERTIME_DRIVING_SETTING         (924)      /*用于获取长时间驾驶时间段参数*/
#define AE_SET_OVERTIME_DRIVING_SETTING         (925)      /*用于设置长时间驾驶时间段参数*/

/*IPC配置*/
#define AE_GET_ADDED_IPC_LIST                   (1001)      /*获取已经添加的ipc列表*/
#define AE_GET_ADDABLE_IPC_LIST                 (1002)      /*获取在线的ipc列表*/
#define AE_ADD_IPC                              (1003)      /*快速添加IPC*/
#define AE_DEL_IPC                              (1004)      /*删除IPC*/

/*设备能力集大类*/
#define AE_CAPABILITY_GET                       (1901)      /*获取能力集大类*/
#define AE_CAPABILITY_IMAGE_GET                 (1911)      /*获取图像能力集*/
#define AE_CAPABILITY_BASIC_GET                 (1921)      /*获取基础能力集*/
#define AE_CAPABILITY_NETWORK_GET               (1931)      /*获取网络能力集*/
#define AE_CAPABILITY_STORAGE_GET               (1941)      /*获取存储能力集*/
#define AE_CAPABILITY_INTELLIGENCE_GET          (1951)      /*获取智能驾驶能力集大类*/
#define AE_CAPABILITY_PROMPT_GET                (1952)      /*获取提醒能力集*/
#define AE_CAPABILITY_ALERT_GET                 (1953)      /*获取告警能力集*/
#define AE_CAPABILITY_SENSOR_GET                (1954)      /*获取传感能力集*/
#define AE_CAPABILITY_ADAS_GET                  (1955)      /*获取ADAS能力集*/
#define AE_CAPABILITY_DBA_GET                   (1956)      /*获取DBA能力集*/
#define AE_CAPABILITY_VSD_GET                   (1957)      /*获取VSD能力集, 已弃用，能力集归于DBA*/
#define AE_CAPABILITY_BSD_GET                   (1958)      /*获取BSD能力集*/


#define AE_CAPABILITY_FACE_GET                  (1959)      /*获取人脸识别能力集*/

#define AE_CAPABILITY_TIME_GET                  (1961)      /*获取时间能力集*/

#define AE_CAPABILITY_WHD_GET                   (1962)      /*获取WHD能力集*/

#define AE_CAPABILITY_PICTURE_GET               (1971)      /*获取图片能力集*/
#define AE_CAPABILITY_COMPRESS_GET              (1981)      /*获取压缩能力集*/
#define AE_CAPABILITY_BLUETOOTH_GET             (1991)      /*获取蓝牙能力集*/
#define AE_CAPABILITY_IPC_GET                   (1993)      /*ipc能力集*/

/*智能类命令*/
#define AE_GET_ADAS_SETTING                     (901)       /*获取ADAS设置*/
#define AE_SET_ADAS_SETTING                     (902)       /*设置ADAS设置*/
#define AE_GET_ADAS_CALIBRATION                 (903)       /*获取ADAS标定*/
#define AE_SET_ADAS_CALIBRATION                 (904)       /*设置ADAS标定*/
#define AE_GET_DBA_SETTING                      (905)       /*获取DBA设置*/
#define AE_SET_DBA_SETTING                      (906)       /*设置DBA设置*/
#define AE_ENTER_SPEED_CALIBRATION              (907)       /*进入速度标定*/
#define AE_EXIT_SPEED_CALIBRATION               (908)       /*离开速度标定*/
#define AE_START_SPEED_CALIBRATION              (909)       /*开始速度标定*/
#define AE_GET_SPEED_CALIBRATION_STATUS         (910)       /*获取速度标定状态*/
#define AE_GET_CAR_STATUS                       (911)       /*获取车辆状态*/
#define AE_GET_VSD_SETTING                      (912)       /*获取VSD设置*/
#define AE_SET_VSD_SETTING                      (913)       /*设置VSD设置*/
#define AE_START_ADAS_CALIBRATION               (914)       /*开始ADAS相机标定*/
#define AE_GET_SPEED_CALIBRATION                (915)       /*获取速度标定*/
#define AE_SET_SPEED_CALIBRATION                (916)       /*设置速度标定*/
#define AE_TURN_CALIBRATION                     (917)       /*转弯标定*/
#define AE_BREAK_CALIBRATION                    (918)       /*刹车标定*/
#define AE_GET_SPEED                            (919)       /*获取车速*/
#define AE_GET_BSD_SETTING                      (920)       /*获取BSD设置*/
#define AE_SET_BSD_SETTING                      (921)       /*设置BSD设置*/
#define AE_GET_IO_WARN_INFO                     (928)       /*获取IO报警设置*/
#define AE_SET_IO_WARN_INFO                     (929)       /*设置IO报警通道设置*/
#define AE_GET_PULSE_SETTING                    (930)       /*获取脉冲设置*/
#define AE_SET_PULSE_SETTING                    (931)       /*设置脉冲参数*/
#define AE_GET_IO_OUTPUT_SETTING                (934)       /*获取IO报警输出*/
#define AE_SET_IO_OUTPUT_SETTING                (935)       /*设置IO报警输出*/

#define AE_GET_WHD_SETTING                      (938)       /*获取WHD设置*/
#define AE_SET_WHD_SETTING                      (939)       /*设置WHD设置*/
#define AE_SET_PFS_INFO                      	(940)       /*获取实时客流信息*/

#define AE_GET_CUSTOM_SMART_CHAN_INFO           (941)       /*获取用户自定义智能摄像头信息*/
#define AE_SET_CUSTOM_SMART_CHAN_INFO           (942)       /*设置用户自定义智能摄像头信息*/

/* 事件关联类 */
#define AE_GET_EVENT_DISPLAY_SETTING            (950)      /* 获取事件显示 */
#define AE_SET_EVENT_DISPLAY_SETTING            (951)

/*私有协议*/
/*过程控制类命令*/
#define AE_START_SESSION                        (257)       /*握手*/
#define AE_STOP_SESSION                         (258)       /*断开*/

/*系统类命令*/
#define AE_RESET_DEFAULT                        (2201)      /*恢复默认参数*/
#define AE_REBOOT_SYSTEM                        (2202)      /*重启系统*/
#define AE_SHUTDOWN_SYSTEM                      (2203)      /*关机*/
#define AE_UPGRADE                              (2204)      /*升级*/
#define AE_GET_SETTING                          (2205)      /*获取某项设置的当前参数*/
#define AE_SET_SETTING                          (2206)      /*配置某项设置的当前参数*/
#define AE_GET_UPGRADE_PATH                     (2207)      /*获取升级路径*/
#define AE_GET_ACTIVE_STATUS                    (2208)      /*获取设备激活状态*/
#define AE_GET_CHANNEL_INFO                     (2209)      /*获取OSD通道信息*/
#define AE_SET_CHANNEL_INFO                     (2210)      /*设置OSD通道信息*/
#define AE_APK_UPGRADE                          (2211)      /*卡升级安卓*/
#define AE_STARTUP_SYSTEM                       (2212)      /*开机命令*/
#define AE_DOWNLOAD                             (2213)      /*下载*/

/*文件类命令*/
#define AE_GET_VIDEO_FILE_LIST                  (2301)      /*获取录像文件列表*/
#define AE_GET_IMAGE_FILE_LIST                  (2302)      /*获取图像文件列表*/
#define AE_GET_AUDIO_FILE_LIST                  (2303)      /*获取音频文件列表*/
#define AE_DELETE_FILE                          (2304)      /*删除文件*/
#define AE_GET_TOTAL_NUM                        (2305)      /*获取总文件数目*/
#define AE_GET_RECORD_STATUS_BY_MONTH           (2306)      /*获取当月每天的录像状态*/
#define AE_LOCK_FILE                            (2307)      /*文件加锁*/
#define AE_UNLOCK_FILE                          (2308)      /*文件解锁*/
#define AE_GET_VIDEO_TIMETAMP                   (2309)      /*获取录像开始时间点及结束时间点*/
#define AE_GET_VIDEO_FILE_LIST_BY_TIME          (2310)      /*获取某一天的录像时间段*/
#define AE_GET_RECORD_DAYS                      (2311)      /*获取当前设备所有录像的日期*/

/*透传类命令*/
#define AE_GET_CUSTOM                           (2401)      /*获取自定义命令*/
#define AE_SET_CUSTOM                           (2402)      /*设置自定义命令*/

/*媒体类命令*/
#define AE_START_PREVIEW                        (2501)      /*开始预览*/
#define AE_STOP_PREVIEW                         (2502)      /*停止预览*/
#define AE_START_PLAYBACK                       (2503)      /*开始回放*/
#define AE_STOP_PLAYBACK                        (2504)      /*停止回放*/
#define AE_START_AUDIO                          (2505)      /*开始音频回放*/
#define AE_STOP_AUDIO                           (2506)      /*停止音频回放*/
#define AE_TAKE_PHOTO                           (2507)      /*抓图*/
#define AE_SET_RECORD_LOCK_STATUS               (2508)      /*设置录像锁定状态*/
#define AE_GET_RTSP_INFO                        (2509)      /*获取RTSP用户名和密码*/

#define AE_CAPABILITY_CALIBRATION_GET           (4101)      /*获取标定能力*/

/*工厂测试*/
#define AE_FACTORY                              (5001)      /*工厂测试*/
/****************************************END****************************************/
/*错误码*/
/****************************************BEGIN****************************************/
/*系统类错误码*/
#define AE_SYS_NOERROR                          (0)         /*正常*/
#define AE_SYS_UNKNOWN_ERROR                    (1)         /*操作异常，无法判定原因*/
#define AE_SYS_SESSION_START_FAIL               (2)         /*建立连接失败*/
#define AE_SYS_INVALID_TOKEN                    (3)         /*token错误*/
#define AE_SYS_REACH_MAX_CLINT                  (4)         /*客户端连接数达到上限*/
#define AE_SYS_HDMI_INSERTED                    (5)         /*APP请求建立连接时，HDMI端口有连接其他外设*/
#define AE_SYS_NO_MORE_MEMORY                   (6)         /*设备内存耗尽*/
#define AE_SYS_PIV_NOT_ALLOWED                  (7)         /*当前分辨率和帧率不支持在录像的时候抓拍图片*/
#define AE_SYS_SYSTEM_BUSY                      (8)         /*系统繁忙，无法处理当前请求*/
#define AE_SYS_NOT_READY                        (9)         /*设备初始化未完成*/
#define AE_SYS_RESET_FAILED                     (10)        /*设备复位失败*/
#define AE_SYS_GET_FILE_LIST_FAILED             (11)        /*获取文件列表失败*/
#define AE_SYS_UNACTIVED                        (12)        /*设备未激活*/
#define AE_SYS_DEMO_MODE                        (13)        /*设备处在演示模式，无法设置参数*/
#define AE_NO_BATTERY                           (14)        /*设备未装载电池*/
#define AE_NO_TRAIN_INFO                        (15)        /*未连接外部设备*/

#define AE_SYS_CHAN_NUM_OVER_FLOW     AE_SYS_UNKNOWN_ERROR  /*通道号超出范围*/

/*存储类错误码*/
#define AE_SDCARD_UNKNOWN_ERROR                 (101)       /*SD卡未知错误*/
#define AE_SDCARD_NOT_EXIST                     (102)       /*SD卡不存在*/
#define AE_SDCARD_DAMAGED                       (103)       /*SD卡损坏*/
#define AE_SDCARD_MOUNT_FAILED                  (104)       /*SD卡挂载失败*/
#define AE_SDCARD_LOCK_STATUS_UNKNOWN           (105)       /*SD卡加解锁固件未知错误*/
#define AE_SDCARD_FS_ERROR                      (106)       /*SD卡文件系统错误*/
#define AE_SDCARD_CREATE_FA_FAILED              (107)       /*SD卡文件系统创建失败*/
#define AE_SDCARD_CREATE_PARTITION_FAILED       (108)       /*SD卡创建分区失败*/
#define AE_SDCARD_NO_MORE_SPACE                 (109)       /*SD卡剩余空间不足*/
#define AE_SDCARD_PROTECTED                     (110)       /*SD卡写保护*/
#define AE_SDCARD_DECRYPT_ERROR                 (111)       /*SD卡解锁失败*/
#define AE_FILE_NOT_EXIST                       (112)       /*文件不存在*/
#define AE_USB_DISK_UNKNOWN_ERROR               (116)       /*U盘未知错误*/
#define AE_USB_DISK_NOT_EXIST                   (117)       /*U盘不存在*/
#define AE_SCHEDULE_DUPLICATE                   (118)       /*录像计划时间设置错误*/

/*网络类错误码*/
#define AE_WIFI_UNKNOWN_ERROR                   (201)       /*wifi未知错误*/

/*协议类错误码*/
#define AE_PROT_JSON_PACKAGE_ERROR              (301)       /*json字符串不支持嵌套*/
#define AE_PROT_JSON_PACKAGE_TIMEOUT            (302)       /*5秒内未收到json结束标志*/
#define AE_PROT_JSON_SYNTAX_ERROR               (303)       /*json字符串的键值对包含语法错误*/
#define AE_PROT_INVALID_OPTION_VALUE            (304)       /*AE_SET_SETTING命令的json字符串中包含不支持的选项*/
#define AE_PROT_INVALID_OPERATION               (305)       /*不支持的命令号*/
#define AE_PROT_INVALID_TYPE                    (306)       /*协议命令的type非法*/
#define AE_PROT_INVALID_PARAM                   (307)       /*协议命令的param非法*/
#define AE_PROT_INVALID_PATH                    (308)       /*请求的文件或目录不存在*/
#define AE_TIMEZONE_INTERVAL_ERROR              (309)       /*夏令时间隔小于30天*/
#define AE_TIMEZONE_WEEK_ERROR                  (310)       /*夏令时星期错误*/
#define AE_TIMEZONE_DAY_ERROR                   (311)       /*夏令时日期错误*/
#define AE_VOLTAGE_ERROR						(312)		/*设置失败，当前电压小于设置电压*/
#define AE_VOLTAGE_NOT_CONNECTED				(313)		/*设置失败，未连接降压线*/
#define AE_SET_VALUE_TOO_LOW				    (314)		/*设置参数过低*/
#define AE_SET_VALUE_TOO_HIGH				    (314)		/*设置参数过高*/
/****************************************END****************************************/

#if 0


/**
 * @brief  处理远程客户端的连接握手请求
 * @param  pstReqJson   网络请求JSON数据包
 * @return 成功，返回消息ID；失败，返回错误码
 * @see
 * @note   内部使用。iSockFd为服务端实际通信套接字。数据流向：设备-->APP。
 */
static INT32 net_app_session_start(SYS_JSON_OBJ_T *pstReqJson, SYS_JSON_OBJ_T *pstRespJson)
{
    INT32  iRet = AE_SYS_NOERROR;
    UINT32 uIdx = 0;
    UINT8  *pAesKey = NULL;
    CHAR   *sFirst = NULL;
    CHAR   *sSecond = NULL;
    CHAR   pRsaKey[1024] = {0};
    CHAR   sRsaEncodeKey[300] = {0};
    CHAR   sKeyStr[100] = {0};
    CHAR   sVersion[32] = {0};
    CHAR   sAppVer[32] = {0};

    //NET_APP_NOTE("net_app_session_start: 1 sys_time = %d ms\n", sys_msec_get());

    do
    {
        iRet = sys_json_get_string(pstReqJson, "rsaKey", pRsaKey, sizeof(pRsaKey));
        if(ERROR == iRet)
        {
            NET_APP_ERROR("get rsa key failed\n");
            iRet = AE_SYS_SESSION_START_FAIL;
            break;
        }

        pAesKey = g_stHandleCtrl.sAesKey;
        NET_APP_CHECK_PTR_BREAK(pAesKey, NET_APP_ERROR, iRet, AE_SYS_SESSION_START_FAIL);

        RAND_pseudo_bytes(pAesKey, AES_KEY_LENGTH);
        for(uIdx = 0; uIdx < AES_KEY_LENGTH; uIdx++)
        {
            sprintf(sKeyStr + uIdx * 2, "%02x", pAesKey[uIdx]);
        }

        iRet = app_rsa_encode(pRsaKey, sKeyStr, (UINT8 *)sRsaEncodeKey);
        if(iRet < 0)
        {
            NET_APP_ERROR("encode failed!\n");
            iRet = AE_SYS_SESSION_START_FAIL;
            break;
        }

        net_app_version(sVersion, sizeof(sVersion));
        sFirst = strtok_r(sVersion, " ", &sSecond);
        NET_APP_CHECK_PTR_BREAK(sFirst, NET_APP_ERROR, iRet, ERROR);
        snprintf(sAppVer, sizeof(sAppVer), "%s", sFirst);

        iRet = sys_json_add_string(pstRespJson, "version", sAppVer);
        NET_APP_CHECK_VALUE_BREAK(iRet, NET_APP_ERROR);

        iRet = sys_json_add_string(pstRespJson, "aesCode", sRsaEncodeKey);
        NET_APP_CHECK_VALUE_BREAK(iRet, NET_APP_ERROR);
    }while(0);

    if(OK != iRet)
    {
        return (iRet == ERROR) ? (AE_SYS_SESSION_START_FAIL) : (iRet);
    }

    return AE_SYS_NOERROR;
}

#endif

#if 0
/**
 * @brief 处理消息
 * @param iServFd 通信套接字
 * @param iTokenID 令牌ID
 * @return 成功，返回OK；失败，返回ERROR
 */
INT32 net_app_msg_handle(INT32 iServFd, INT32 iTokenID)
{
    INT32 iRet = OK;
    INT32 iRecvLen = 0;
    INT32 iBaseLen = 0;
    INT32 iAesLen = 0;
    INT32 iBodyLen = 0;
    UINT32 uReqIdx = 0;
    UINT32 uDataLen = 0;
    UINT32 uUserIdx = 0;
    UINT32 uHeaderLen = 0;
    CHAR sHeader[MSG_HEADER_LENGTH + 4] = {0};
    CHAR sRecvBuf[NET_APP_RECV_SIZE] = {0};
    CHAR sBaseBuf[NET_APP_RECV_SIZE] = {0};/*存放解码之后的消息*/
    CHAR sDataBuf[NET_APP_RECV_SIZE] = {0};/*存放解密之后的消息*/
    NET_APP_QUEUE_T stQueue = {0};
    uHeaderLen = sizeof(sHeader);

    memset(sRecvBuf, 0, NET_APP_RECV_SIZE);
    iRecvLen = sys_socket_read(iServFd, sRecvBuf, NET_APP_RECV_SIZE);
    if(iRecvLen <= 0)
    {
        NET_APP_ERROR("recv start session msg failed!\n");
        SYS_SOCKET_SAFE_CLOSE(iServFd);
        return ERROR;
    }

    iRet = net_app_session_start_handle(iServFd, sRecvBuf, iRecvLen, iTokenID);
    if(iRet != OK)
    {
        NET_APP_ERROR("start session failed!\n");
        SYS_SOCKET_SAFE_CLOSE(iServFd);
        return ERROR;
    }

    /*握手成功，传输套接字入队列，连接状态置位1*/
    memset(&stQueue, 0, sizeof(NET_APP_QUEUE_T));
    stQueue.iServFd = iServFd;
    stQueue.uOnline = 1;
    iRet = net_app_user_enqueue(&stQueue, &uUserIdx);
    if(iRet != OK)
    {
        NET_APP_ERROR("set user[%d] state failed!\n", iServFd);
        /*通知APP断开连接*/
        net_app_send_user_notification(NOTE_DISCONNECT_DOWN, NULL, 0, iServFd);/*告知用户退出*/
        SYS_SOCKET_SAFE_CLOSE(iServFd);
        return ERROR;
    }

    /*握手成功之后接收其他消息*/
    while(1)
    {
        memset(sHeader, 0, uHeaderLen);
        iRecvLen = sys_socket_read(iServFd, sHeader, MSG_HEADER_LENGTH);
        if(iRecvLen <= 0)
        {
            NET_APP_ERROR("timeout or peer closed, %d!\n", iRecvLen);
            iRet = ERROR;
            break;
        }
        if(MSG_HEADER_LENGTH != iRecvLen)
        {
            NET_APP_ERROR("recv header failed, %d!\n", iRecvLen);
            continue;
        }

        /*检验头部，获取请求索引以及数据长度*/
        iRet = net_app_msg_header_judge(sHeader, &uReqIdx, &uDataLen);
        if(iRet == ERROR)
        {
            NET_APP_ERROR("data header error!\n");
            continue;
        }

        if(uDataLen >= NET_APP_RECV_SIZE)
        {
            NET_APP_ERROR("data too large!\n");
            continue;
        }

        memset(sRecvBuf, 0, NET_APP_RECV_SIZE);
        iRecvLen = sys_socket_read(iServFd, sRecvBuf, uDataLen);
        if(iRecvLen != uDataLen)
        {
            NET_APP_ERROR("recv data body failed!\n");
            continue;
        }

        /* Base64解码 */
        memset(sBaseBuf, 0, NET_APP_RECV_SIZE);
        iBaseLen = EVP_DecodeBlock((UINT8 *)sBaseBuf, (UINT8 *)sRecvBuf, uDataLen);
        iAesLen = ROUND_UP(iBaseLen, AES_KEY_LENGTH);

        /* AES解密 */
        memset(sDataBuf, 0, NET_APP_RECV_SIZE);
        iRet = aes_decrypt(sBaseBuf, iAesLen, sDataBuf, NET_APP_RECV_ADD, (INT32 *)&uDataLen, g_stHandleCtrl.sAesKey);
        if(iRet < 0)
        {
            NET_APP_ERROR("aes decrypt failed\n");
            continue;
        }

        iBodyLen = net_app_msg_check_complete(sDataBuf, uDataLen);
        if(iBodyLen <= 0)
        {
            NET_APP_ERROR("body not complete\n");
            continue;
        }

        //NET_APP_INFO("data: %d, body: %d, iIdx: %d\n", uDataLen, iBodyLen, uReqIdx);
        iRet = net_app_single_msg_handle(iServFd, sDataBuf, iBodyLen, iTokenID, uReqIdx);
        //NET_APP_ERROR("net_app_msg_handle: 1 %d %d.\n", iRet, iTokenID);
        if(iRet == ERROR)
        {
            NET_APP_ERROR("handle msg failed\n");
        }
    }

    /*断开连接，套接字出列，释放资源，连接状态置位0*/
    net_app_user_dequeue(uUserIdx);

    return iRet;
}






**
 * @brief  将JSON数据包发送给远程客户端APP
 * @param  iServFd 网络通信套接字
 * @param  pstRespJson   网络JSON数据包指针
 * @return 成功，返回OK；失败，返回ERROR
 * @see
 * @note   模块内使用。iSockFd为服务端实际通信套接字。数据流向：设备-->APP。
 */
INT32 net_app_send_json(const INT32 iServFd, SYS_JSON_OBJ_T *pstRespJson, NET_APP_RET_T *pstNetApp)
{
    INT32 iRet = OK;
    CHAR  *pRespStr = NULL;
    UINT8 *pAesKey = NULL;
    CHAR  *pMsgBody = NULL;
    INT32 iAesOutLen = 0;
    INT32 iBase64OutLen = 0;
    INT32 iDataLen = 0;
    UINT32 uInLen = 0;
    CHAR sAesOut[AES_MAX_OUT_LEN] = {0};
    CHAR sEncOut[AES_MAX_OUT_LEN_BASE64] = {0};
    APP_MSG_PRIVATE stRespMsg;

    NET_APP_CHECK_PTR_RET(pstRespJson, NET_APP_ERROR, ERROR);

    pRespStr = sys_json_to_string(pstRespJson);
    NET_APP_CHECK_PTR_RET(pRespStr, NET_APP_ERROR, ERROR);

    NET_APP_INFO("%s\n", pRespStr);

    uInLen = strlen(pRespStr);
    memset(&stRespMsg, 0, sizeof(APP_MSG_PRIVATE));
    stRespMsg.uMsgConstant = BigLittleSwap32(MSG_HEADER_CONS);
    stRespMsg.uMsgIndex = BigLittleSwap32(pstNetApp->uReqIdx);
    stRespMsg.uMsgLength = BigLittleSwap32(uInLen);
    pMsgBody = (sEncOut + MSG_HEADER_LENGTH);

    pAesKey = g_stHandleCtrl.sAesKey;
    NET_APP_CHECK_PTR_RET(pAesKey, NET_APP_ERROR, ERROR);
    if(uInLen > AES_MAX_IN_LEN)
    {
        NET_APP_ERROR("encrypt str too large\n");
        return ERROR;
    }

    iRet = aes_encrypt((UINT8 *)pRespStr, AES_MAX_IN_LEN, uInLen, (UINT8 *)sAesOut, AES_MAX_OUT_LEN, &iAesOutLen, pAesKey);
    if(iRet < 0)
    {
        NET_APP_ERROR("app_aes_encrypt ERR: %d", iRet);
        return ERROR;
    }

    if(iAesOutLen > AES_MAX_IN_LEN)
    {
        NET_APP_ERROR("encode str too large\n");
        return ERROR;
    }

    iBase64OutLen = EVP_EncodeBlock((UINT8 *)pMsgBody, (UINT8 *)sAesOut, iAesOutLen); //base64编码
    stRespMsg.uMsgLength = BigLittleSwap32(iBase64OutLen);
    iDataLen = strlen(pMsgBody) + MSG_HEADER_LENGTH;
    memcpy(sEncOut, &stRespMsg, MSG_HEADER_LENGTH);
    //sys_mutex_lock(&g_stHandleCtrl.mLock, WAIT_FOREVER);/*加锁*/
    if(sys_socket_writen(iServFd, sEncOut, iDataLen) != iDataLen)
    {
        NET_APP_ERROR("socket write failed!\n");
        //sys_mutex_unlock(&g_stHandleCtrl.mLock);/*解锁*/
        return ERROR;
    }
    //sys_mutex_unlock(&g_stHandleCtrl.mLock);/*加锁*/

    return iRet;
}
#endif