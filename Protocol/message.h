
/*APP -> DEVICE��ϢID*/
/****************************************BEGIN****************************************/
/*��չEHOMEЭ��*/
/*ϵͳ������*/
#define AE_GET_ALL_CURRENT_SETTINGS             (1)         /*��ȡ�������õĵ�ǰ����*/
#define AE_GET_BATTERY_LEVEL		            (2)         /*��ȡ���״̬*/
#define AE_GET_CAMERAS_STATUS                   (3)         /*��ȡ����ͨ�������¼��״̬*/
#define AE_GET_GSENSOR_DATA                     (4)         /*��ȡ�豸G-sensor����*/
#define AE_GET_GPS                              (5)         /*��ȡ��ǰGPS����*/
#define AE_GET_DEVICE_INFO                      (6)         /*��ȡ�豸��Ϣ*/
#define AE_GET_VEHICLE_INFO                     (8)         /*��ȡ���������Ϣ*/
#define AE_SET_VEHICLE_INFO                     (9)         /*���ó��������Ϣ*/
#define AE_GET_DRIVER_INFO                      (10)        /*��ȡ��ʻԱ�����Ϣ*/
#define AE_SET_DRIVER_INFO                      (11)        /*���ü�ʻԱ�����Ϣ*/

#define AE_GET_SATELLITE_INFO                   (19)        /*��ȡ�豸��ǰ��������Ϣ*/

#define AE_GET_PICTURE_SETTING                  (186)       /*��ȡͼ������*/
#define AE_SET_PICTURE_SETTING                  (187)       /*����ͼ������*/
#define AE_GET_COMPRESS_SETTING                 (188)       /*��ȡѹ������*/
#define AE_SET_COMPRESS_SETTING                 (189)       /*����ѹ������*/

#define AE_GET_IMAGE_SETTING                    (190)       /*��ȡͼƬ����*/
#define AE_SET_IMAGE_SETTING                    (191)       /*����ͼƬ����*/
#define AE_GET_GENERIC_SETTING                  (192)       /*��ȡͨ������*/
#define AE_SET_GENERIC_SETTING                  (193)       /*����ͨ������*/
#define AE_GET_PROMPT_SETTING                   (194)       /*��ȡ��������*/
#define AE_SET_PROMPT_SETTING                   (195)       /*������������*/
#define AE_GET_ALERT_SETTING                    (196)       /*��ȡ�澯����*/
#define AE_SET_ALERT_SETTING                    (197)       /*���ø澯����*/
#define AE_GET_SENSOR_SETTING                   (198)       /*��ȡ��������*/
#define AE_SET_SENSOR_SETTING                   (199)       /*���ô�������*/

/*ý������*/
#define AE_RECORD_START                         (201)       /*����¼��*/
#define AE_RECORD_STOP                          (202)       /*�ر�¼��*/
#define AE_EVENT_RECORD_START                   (203)       /*��������¼��*/
#define AE_AUDIO_RECORD_START                   (204)       /*������Ƶ¼��*/
#define AE_AUDIO_RECORD_STOP                    (205)       /*�ر���Ƶ¼��*/

/*����ӿ�������*/
#define AE_WIFI_RESTART                         (301)       /*����wifi*/
#define AE_GET_STA_PARAM                        (302)       /*��ȡSTA����*/
#define AE_SET_STA_PARAM                        (303)       /*����STA����*/
#define AE_GET_AP_PARAM                         (304)       /*��ȡAP����*/
#define AE_SET_AP_PARAM                         (305)       /*����AP����*/
#define AE_GET_4G_PARAM                         (306)       /*��ȡ4G����*/
#define AE_SET_4G_PARAM                         (307)       /*����4G����*/
#define AE_GET_NETWORK_SETTING                  (398)       /*��ȡ��������*/
#define AE_SET_NETWORK_SETTING                  (399)       /*������������*/

/*�洢������*/
#define AE_GET_SD_LETTER                        (401)       /*��ȡ�Ѳ����̷�*/
#define AE_GET_SD_INFO                          (402)       /*��ȡSD��Ϣ*/
#define AE_SET_SD_LOCK_STATUS                   (403)       /*����SD��״̬*/
#define AE_SET_SD_PASSWD                        (404)       /*����SD����*/
#define AE_FORMAT                               (405)       /*��ʽ��SD��*/
#define AE_GET_RECORD_SCHEDILE                  (406)       /*��ȡ¼��ƻ�*/
#define AE_SET_RECORD_SCHEDILE                  (407)       /*����¼��ƻ�*/
#define AE_COPY_DAY_SCHEDILE                    (408)       /*����һ���¼��ƻ�*/
#define AE_COPY_CHANNEL_SCHEDILE                (409)       /*����һ��ͨ����¼��ƻ�*/
#define AE_GET_STORAGE_SETTING                  (498)       /*��ȡ�洢����*/
#define AE_SET_STORAGE_SETTING                  (499)       /*���ô洢����*/
#define AE_EXPORT_MEDIA_FILE					(410)		/*�豸ý���ļ��������ⲿ�洢�豸*/
#define AE_EXPORT_LOG							(411)		/*�豸��־�������ⲿ�洢�豸*/
#define AE_EXPORT_CONFIG                        (414)       /*���豸�е������ļ����뵽�ⲿ�豸*/
#define AE_INPORT_CONFIG						(415)		/*���ⲿ�豸�е������ļ����뵽�豸*/
#define AE_CONCEL_EXPORT						(416)		/*ȡ���ļ�����*/

/*ʱ��������*/
#define AE_GET_DAYLIGHT_TIME                    (501)       /*��ȡ����ʱ*/
#define AE_SET_DAYLIGHT_TIME                    (502)       /*��������ʱ*/
#define AE_GET_TIMEZONE                         (503)       /*��ȡʱ��*/
#define AE_SET_TIMEZONE                         (504)       /*����ʱ��*/
#define AE_GET_TIME_SETTING                     (598)       /*��ȡʱ������*/
#define AE_SET_TIME_SETTING                     (599)       /*����ʱ������*/

/*֪ͨ������*/
#define AE_NOTIFICATION                         (601)       /*֪ͨ����Ϣ*/

/*ƽ̨����������*/
#define AE_GET_PLATFORM_CONN_INFO               (701)       /*��ȡƽ̨��Ϣ*/
#define AE_SET_PLATFORM_CONN_INFO               (702)       /*����ƽ̨��Ϣ*/
#define AE_GET_808_CONN_INFO                    (703)       /*��ȡ808������Ϣ*/
#define AE_SET_808_CONN_INFO                    (704)       /*����808������Ϣ*/
#define AE_GET_808_CONN_INFO_2                  (705)       /*��ȡ808_2������Ϣ*/
#define AE_SET_808_CONN_INFO_2                  (706)       /*����808_2������Ϣ*/
#define AE_GET_OPERATE_PLATFORM_INFO            (707)       /*��ȡ��άƽ̨������Ϣ*/
#define AE_SET_OPERATE_PLATFORM_INFO            (708)       /*������άƽ̨������Ϣ*/
#define AE_GET_NTP_PLATFORM_INFO                (709)       /*��ȡNTPƽ̨������Ϣ*/
#define AE_SET_NTP_PLATFORM_INFO                (710)       /*����NTPƽ̨������Ϣ*/

/*��������*/
#define AE_GET_FACE_INFO                        (922)      /*��ȡ�豸�洢��������Ϣ*/
#define AE_SET_FACE_INFO                        (923)      /*�����豸�洢��������Ϣ*/
#define AE_GET_OVERTIME_DRIVING_SETTING         (924)      /*���ڻ�ȡ��ʱ���ʻʱ��β���*/
#define AE_SET_OVERTIME_DRIVING_SETTING         (925)      /*�������ó�ʱ���ʻʱ��β���*/

/*IPC����*/
#define AE_GET_ADDED_IPC_LIST                   (1001)      /*��ȡ�Ѿ���ӵ�ipc�б�*/
#define AE_GET_ADDABLE_IPC_LIST                 (1002)      /*��ȡ���ߵ�ipc�б�*/
#define AE_ADD_IPC                              (1003)      /*�������IPC*/
#define AE_DEL_IPC                              (1004)      /*ɾ��IPC*/

/*�豸����������*/
#define AE_CAPABILITY_GET                       (1901)      /*��ȡ����������*/
#define AE_CAPABILITY_IMAGE_GET                 (1911)      /*��ȡͼ��������*/
#define AE_CAPABILITY_BASIC_GET                 (1921)      /*��ȡ����������*/
#define AE_CAPABILITY_NETWORK_GET               (1931)      /*��ȡ����������*/
#define AE_CAPABILITY_STORAGE_GET               (1941)      /*��ȡ�洢������*/
#define AE_CAPABILITY_INTELLIGENCE_GET          (1951)      /*��ȡ���ܼ�ʻ����������*/
#define AE_CAPABILITY_PROMPT_GET                (1952)      /*��ȡ����������*/
#define AE_CAPABILITY_ALERT_GET                 (1953)      /*��ȡ�澯������*/
#define AE_CAPABILITY_SENSOR_GET                (1954)      /*��ȡ����������*/
#define AE_CAPABILITY_ADAS_GET                  (1955)      /*��ȡADAS������*/
#define AE_CAPABILITY_DBA_GET                   (1956)      /*��ȡDBA������*/
#define AE_CAPABILITY_VSD_GET                   (1957)      /*��ȡVSD������, �����ã�����������DBA*/
#define AE_CAPABILITY_BSD_GET                   (1958)      /*��ȡBSD������*/


#define AE_CAPABILITY_FACE_GET                  (1959)      /*��ȡ����ʶ��������*/

#define AE_CAPABILITY_TIME_GET                  (1961)      /*��ȡʱ��������*/

#define AE_CAPABILITY_WHD_GET                   (1962)      /*��ȡWHD������*/

#define AE_CAPABILITY_PICTURE_GET               (1971)      /*��ȡͼƬ������*/
#define AE_CAPABILITY_COMPRESS_GET              (1981)      /*��ȡѹ��������*/
#define AE_CAPABILITY_BLUETOOTH_GET             (1991)      /*��ȡ����������*/
#define AE_CAPABILITY_IPC_GET                   (1993)      /*ipc������*/

/*����������*/
#define AE_GET_ADAS_SETTING                     (901)       /*��ȡADAS����*/
#define AE_SET_ADAS_SETTING                     (902)       /*����ADAS����*/
#define AE_GET_ADAS_CALIBRATION                 (903)       /*��ȡADAS�궨*/
#define AE_SET_ADAS_CALIBRATION                 (904)       /*����ADAS�궨*/
#define AE_GET_DBA_SETTING                      (905)       /*��ȡDBA����*/
#define AE_SET_DBA_SETTING                      (906)       /*����DBA����*/
#define AE_ENTER_SPEED_CALIBRATION              (907)       /*�����ٶȱ궨*/
#define AE_EXIT_SPEED_CALIBRATION               (908)       /*�뿪�ٶȱ궨*/
#define AE_START_SPEED_CALIBRATION              (909)       /*��ʼ�ٶȱ궨*/
#define AE_GET_SPEED_CALIBRATION_STATUS         (910)       /*��ȡ�ٶȱ궨״̬*/
#define AE_GET_CAR_STATUS                       (911)       /*��ȡ����״̬*/
#define AE_GET_VSD_SETTING                      (912)       /*��ȡVSD����*/
#define AE_SET_VSD_SETTING                      (913)       /*����VSD����*/
#define AE_START_ADAS_CALIBRATION               (914)       /*��ʼADAS����궨*/
#define AE_GET_SPEED_CALIBRATION                (915)       /*��ȡ�ٶȱ궨*/
#define AE_SET_SPEED_CALIBRATION                (916)       /*�����ٶȱ궨*/
#define AE_TURN_CALIBRATION                     (917)       /*ת��궨*/
#define AE_BREAK_CALIBRATION                    (918)       /*ɲ���궨*/
#define AE_GET_SPEED                            (919)       /*��ȡ����*/
#define AE_GET_BSD_SETTING                      (920)       /*��ȡBSD����*/
#define AE_SET_BSD_SETTING                      (921)       /*����BSD����*/
#define AE_GET_IO_WARN_INFO                     (928)       /*��ȡIO��������*/
#define AE_SET_IO_WARN_INFO                     (929)       /*����IO����ͨ������*/
#define AE_GET_PULSE_SETTING                    (930)       /*��ȡ��������*/
#define AE_SET_PULSE_SETTING                    (931)       /*�����������*/
#define AE_GET_IO_OUTPUT_SETTING                (934)       /*��ȡIO�������*/
#define AE_SET_IO_OUTPUT_SETTING                (935)       /*����IO�������*/

#define AE_GET_WHD_SETTING                      (938)       /*��ȡWHD����*/
#define AE_SET_WHD_SETTING                      (939)       /*����WHD����*/
#define AE_SET_PFS_INFO                      	(940)       /*��ȡʵʱ������Ϣ*/

#define AE_GET_CUSTOM_SMART_CHAN_INFO           (941)       /*��ȡ�û��Զ�����������ͷ��Ϣ*/
#define AE_SET_CUSTOM_SMART_CHAN_INFO           (942)       /*�����û��Զ�����������ͷ��Ϣ*/

/* �¼������� */
#define AE_GET_EVENT_DISPLAY_SETTING            (950)      /* ��ȡ�¼���ʾ */
#define AE_SET_EVENT_DISPLAY_SETTING            (951)

/*˽��Э��*/
/*���̿���������*/
#define AE_START_SESSION                        (257)       /*����*/
#define AE_STOP_SESSION                         (258)       /*�Ͽ�*/

/*ϵͳ������*/
#define AE_RESET_DEFAULT                        (2201)      /*�ָ�Ĭ�ϲ���*/
#define AE_REBOOT_SYSTEM                        (2202)      /*����ϵͳ*/
#define AE_SHUTDOWN_SYSTEM                      (2203)      /*�ػ�*/
#define AE_UPGRADE                              (2204)      /*����*/
#define AE_GET_SETTING                          (2205)      /*��ȡĳ�����õĵ�ǰ����*/
#define AE_SET_SETTING                          (2206)      /*����ĳ�����õĵ�ǰ����*/
#define AE_GET_UPGRADE_PATH                     (2207)      /*��ȡ����·��*/
#define AE_GET_ACTIVE_STATUS                    (2208)      /*��ȡ�豸����״̬*/
#define AE_GET_CHANNEL_INFO                     (2209)      /*��ȡOSDͨ����Ϣ*/
#define AE_SET_CHANNEL_INFO                     (2210)      /*����OSDͨ����Ϣ*/
#define AE_APK_UPGRADE                          (2211)      /*��������׿*/
#define AE_STARTUP_SYSTEM                       (2212)      /*��������*/
#define AE_DOWNLOAD                             (2213)      /*����*/

/*�ļ�������*/
#define AE_GET_VIDEO_FILE_LIST                  (2301)      /*��ȡ¼���ļ��б�*/
#define AE_GET_IMAGE_FILE_LIST                  (2302)      /*��ȡͼ���ļ��б�*/
#define AE_GET_AUDIO_FILE_LIST                  (2303)      /*��ȡ��Ƶ�ļ��б�*/
#define AE_DELETE_FILE                          (2304)      /*ɾ���ļ�*/
#define AE_GET_TOTAL_NUM                        (2305)      /*��ȡ���ļ���Ŀ*/
#define AE_GET_RECORD_STATUS_BY_MONTH           (2306)      /*��ȡ����ÿ���¼��״̬*/
#define AE_LOCK_FILE                            (2307)      /*�ļ�����*/
#define AE_UNLOCK_FILE                          (2308)      /*�ļ�����*/
#define AE_GET_VIDEO_TIMETAMP                   (2309)      /*��ȡ¼��ʼʱ��㼰����ʱ���*/
#define AE_GET_VIDEO_FILE_LIST_BY_TIME          (2310)      /*��ȡĳһ���¼��ʱ���*/
#define AE_GET_RECORD_DAYS                      (2311)      /*��ȡ��ǰ�豸����¼�������*/

/*͸��������*/
#define AE_GET_CUSTOM                           (2401)      /*��ȡ�Զ�������*/
#define AE_SET_CUSTOM                           (2402)      /*�����Զ�������*/

/*ý��������*/
#define AE_START_PREVIEW                        (2501)      /*��ʼԤ��*/
#define AE_STOP_PREVIEW                         (2502)      /*ֹͣԤ��*/
#define AE_START_PLAYBACK                       (2503)      /*��ʼ�ط�*/
#define AE_STOP_PLAYBACK                        (2504)      /*ֹͣ�ط�*/
#define AE_START_AUDIO                          (2505)      /*��ʼ��Ƶ�ط�*/
#define AE_STOP_AUDIO                           (2506)      /*ֹͣ��Ƶ�ط�*/
#define AE_TAKE_PHOTO                           (2507)      /*ץͼ*/
#define AE_SET_RECORD_LOCK_STATUS               (2508)      /*����¼������״̬*/
#define AE_GET_RTSP_INFO                        (2509)      /*��ȡRTSP�û���������*/

#define AE_CAPABILITY_CALIBRATION_GET           (4101)      /*��ȡ�궨����*/

/*��������*/
#define AE_FACTORY                              (5001)      /*��������*/
/****************************************END****************************************/
/*������*/
/****************************************BEGIN****************************************/
/*ϵͳ�������*/
#define AE_SYS_NOERROR                          (0)         /*����*/
#define AE_SYS_UNKNOWN_ERROR                    (1)         /*�����쳣���޷��ж�ԭ��*/
#define AE_SYS_SESSION_START_FAIL               (2)         /*��������ʧ��*/
#define AE_SYS_INVALID_TOKEN                    (3)         /*token����*/
#define AE_SYS_REACH_MAX_CLINT                  (4)         /*�ͻ����������ﵽ����*/
#define AE_SYS_HDMI_INSERTED                    (5)         /*APP����������ʱ��HDMI�˿���������������*/
#define AE_SYS_NO_MORE_MEMORY                   (6)         /*�豸�ڴ�ľ�*/
#define AE_SYS_PIV_NOT_ALLOWED                  (7)         /*��ǰ�ֱ��ʺ�֡�ʲ�֧����¼���ʱ��ץ��ͼƬ*/
#define AE_SYS_SYSTEM_BUSY                      (8)         /*ϵͳ��æ���޷�����ǰ����*/
#define AE_SYS_NOT_READY                        (9)         /*�豸��ʼ��δ���*/
#define AE_SYS_RESET_FAILED                     (10)        /*�豸��λʧ��*/
#define AE_SYS_GET_FILE_LIST_FAILED             (11)        /*��ȡ�ļ��б�ʧ��*/
#define AE_SYS_UNACTIVED                        (12)        /*�豸δ����*/
#define AE_SYS_DEMO_MODE                        (13)        /*�豸������ʾģʽ���޷����ò���*/
#define AE_NO_BATTERY                           (14)        /*�豸δװ�ص��*/
#define AE_NO_TRAIN_INFO                        (15)        /*δ�����ⲿ�豸*/

#define AE_SYS_CHAN_NUM_OVER_FLOW     AE_SYS_UNKNOWN_ERROR  /*ͨ���ų�����Χ*/

/*�洢�������*/
#define AE_SDCARD_UNKNOWN_ERROR                 (101)       /*SD��δ֪����*/
#define AE_SDCARD_NOT_EXIST                     (102)       /*SD��������*/
#define AE_SDCARD_DAMAGED                       (103)       /*SD����*/
#define AE_SDCARD_MOUNT_FAILED                  (104)       /*SD������ʧ��*/
#define AE_SDCARD_LOCK_STATUS_UNKNOWN           (105)       /*SD���ӽ����̼�δ֪����*/
#define AE_SDCARD_FS_ERROR                      (106)       /*SD���ļ�ϵͳ����*/
#define AE_SDCARD_CREATE_FA_FAILED              (107)       /*SD���ļ�ϵͳ����ʧ��*/
#define AE_SDCARD_CREATE_PARTITION_FAILED       (108)       /*SD����������ʧ��*/
#define AE_SDCARD_NO_MORE_SPACE                 (109)       /*SD��ʣ��ռ䲻��*/
#define AE_SDCARD_PROTECTED                     (110)       /*SD��д����*/
#define AE_SDCARD_DECRYPT_ERROR                 (111)       /*SD������ʧ��*/
#define AE_FILE_NOT_EXIST                       (112)       /*�ļ�������*/
#define AE_USB_DISK_UNKNOWN_ERROR               (116)       /*U��δ֪����*/
#define AE_USB_DISK_NOT_EXIST                   (117)       /*U�̲�����*/
#define AE_SCHEDULE_DUPLICATE                   (118)       /*¼��ƻ�ʱ�����ô���*/

/*�����������*/
#define AE_WIFI_UNKNOWN_ERROR                   (201)       /*wifiδ֪����*/

/*Э���������*/
#define AE_PROT_JSON_PACKAGE_ERROR              (301)       /*json�ַ�����֧��Ƕ��*/
#define AE_PROT_JSON_PACKAGE_TIMEOUT            (302)       /*5����δ�յ�json������־*/
#define AE_PROT_JSON_SYNTAX_ERROR               (303)       /*json�ַ����ļ�ֵ�԰����﷨����*/
#define AE_PROT_INVALID_OPTION_VALUE            (304)       /*AE_SET_SETTING�����json�ַ����а�����֧�ֵ�ѡ��*/
#define AE_PROT_INVALID_OPERATION               (305)       /*��֧�ֵ������*/
#define AE_PROT_INVALID_TYPE                    (306)       /*Э�������type�Ƿ�*/
#define AE_PROT_INVALID_PARAM                   (307)       /*Э�������param�Ƿ�*/
#define AE_PROT_INVALID_PATH                    (308)       /*������ļ���Ŀ¼������*/
#define AE_TIMEZONE_INTERVAL_ERROR              (309)       /*����ʱ���С��30��*/
#define AE_TIMEZONE_WEEK_ERROR                  (310)       /*����ʱ���ڴ���*/
#define AE_TIMEZONE_DAY_ERROR                   (311)       /*����ʱ���ڴ���*/
#define AE_VOLTAGE_ERROR						(312)		/*����ʧ�ܣ���ǰ��ѹС�����õ�ѹ*/
#define AE_VOLTAGE_NOT_CONNECTED				(313)		/*����ʧ�ܣ�δ���ӽ�ѹ��*/
#define AE_SET_VALUE_TOO_LOW				    (314)		/*���ò�������*/
#define AE_SET_VALUE_TOO_HIGH				    (314)		/*���ò�������*/
/****************************************END****************************************/

#if 0


/**
 * @brief  ����Զ�̿ͻ��˵�������������
 * @param  pstReqJson   ��������JSON���ݰ�
 * @return �ɹ���������ϢID��ʧ�ܣ����ش�����
 * @see
 * @note   �ڲ�ʹ�á�iSockFdΪ�����ʵ��ͨ���׽��֡����������豸-->APP��
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
 * @brief ������Ϣ
 * @param iServFd ͨ���׽���
 * @param iTokenID ����ID
 * @return �ɹ�������OK��ʧ�ܣ�����ERROR
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
    CHAR sBaseBuf[NET_APP_RECV_SIZE] = {0};/*��Ž���֮�����Ϣ*/
    CHAR sDataBuf[NET_APP_RECV_SIZE] = {0};/*��Ž���֮�����Ϣ*/
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

    /*���ֳɹ��������׽�������У�����״̬��λ1*/
    memset(&stQueue, 0, sizeof(NET_APP_QUEUE_T));
    stQueue.iServFd = iServFd;
    stQueue.uOnline = 1;
    iRet = net_app_user_enqueue(&stQueue, &uUserIdx);
    if(iRet != OK)
    {
        NET_APP_ERROR("set user[%d] state failed!\n", iServFd);
        /*֪ͨAPP�Ͽ�����*/
        net_app_send_user_notification(NOTE_DISCONNECT_DOWN, NULL, 0, iServFd);/*��֪�û��˳�*/
        SYS_SOCKET_SAFE_CLOSE(iServFd);
        return ERROR;
    }

    /*���ֳɹ�֮�����������Ϣ*/
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

        /*����ͷ������ȡ���������Լ����ݳ���*/
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

        /* Base64���� */
        memset(sBaseBuf, 0, NET_APP_RECV_SIZE);
        iBaseLen = EVP_DecodeBlock((UINT8 *)sBaseBuf, (UINT8 *)sRecvBuf, uDataLen);
        iAesLen = ROUND_UP(iBaseLen, AES_KEY_LENGTH);

        /* AES���� */
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

    /*�Ͽ����ӣ��׽��ֳ��У��ͷ���Դ������״̬��λ0*/
    net_app_user_dequeue(uUserIdx);

    return iRet;
}






**
 * @brief  ��JSON���ݰ����͸�Զ�̿ͻ���APP
 * @param  iServFd ����ͨ���׽���
 * @param  pstRespJson   ����JSON���ݰ�ָ��
 * @return �ɹ�������OK��ʧ�ܣ�����ERROR
 * @see
 * @note   ģ����ʹ�á�iSockFdΪ�����ʵ��ͨ���׽��֡����������豸-->APP��
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

    iBase64OutLen = EVP_EncodeBlock((UINT8 *)pMsgBody, (UINT8 *)sAesOut, iAesOutLen); //base64����
    stRespMsg.uMsgLength = BigLittleSwap32(iBase64OutLen);
    iDataLen = strlen(pMsgBody) + MSG_HEADER_LENGTH;
    memcpy(sEncOut, &stRespMsg, MSG_HEADER_LENGTH);
    //sys_mutex_lock(&g_stHandleCtrl.mLock, WAIT_FOREVER);/*����*/
    if(sys_socket_writen(iServFd, sEncOut, iDataLen) != iDataLen)
    {
        NET_APP_ERROR("socket write failed!\n");
        //sys_mutex_unlock(&g_stHandleCtrl.mLock);/*����*/
        return ERROR;
    }
    //sys_mutex_unlock(&g_stHandleCtrl.mLock);/*����*/

    return iRet;
}
#endif