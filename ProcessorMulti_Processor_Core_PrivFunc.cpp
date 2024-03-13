// You need to program this file.

#include "../NoEdit/ProcessorMulti_Processor_Core_PrivFunc.h"
#include <cmath>
#include <time.h>

//*******************Please add static libraries in .pro file*******************
// e.g. unix:LIBS += ... or win32:LIBS += ...

bool DECOFUNC(setParamsVarsOpenNode)(QString qstrConfigName, QString qstrNodeType, QString qstrNodeClass, QString qstrNodeName, void *paramsPtr, void *varsPtr)
{
    XMLDomInterface xmlloader(qstrConfigName, qstrNodeType, qstrNodeClass, qstrNodeName);
    ProcessorMulti_Processor_Core_Params *params = (ProcessorMulti_Processor_Core_Params *)paramsPtr;
    ProcessorMulti_Processor_Core_Vars *vars = (ProcessorMulti_Processor_Core_Vars *)varsPtr;
    /*======Please Program below======*/
    /*
    Function: open node.
    Procedure:
    1: load parameters (params). [GetParamValue(xmlloader,params,tag); GetEnumParamValue(xmlloader,params,tag); GetUEnumParamValue(xmlloader,params,tag)]
    2: initialize variables (vars).
    3: If everything is OK, return 1 for successful opening and vice versa.
    */

    return 1;
}

bool DECOFUNC(handleVarsCloseNode)(void *paramsPtr, void *varsPtr)
{
    ProcessorMulti_Processor_Core_Params *params = (ProcessorMulti_Processor_Core_Params *)paramsPtr;
    ProcessorMulti_Processor_Core_Vars *vars = (ProcessorMulti_Processor_Core_Vars *)varsPtr;
    /*======Please Program below======*/
    /*
    Function: close node.
    Procedure:
    1: handle/close variables (vars).
    2: If everything is OK, return 1 for successful closing and vice versa.
    */

    return 1;
}

void DECOFUNC(getInternalTrigger)(void *paramsPtr, void *varsPtr, QObject *&internalTrigger, QString &internalTriggerSignal)
{
    ProcessorMulti_Processor_Core_Params *params = (ProcessorMulti_Processor_Core_Params *)paramsPtr;
    ProcessorMulti_Processor_Core_Vars *vars = (ProcessorMulti_Processor_Core_Vars *)varsPtr;
    internalTrigger = NULL;
    internalTriggerSignal = QString();
    /*======Occasionally Program above======*/
    /*
    Function: get internal trigger [defined in vars] for node.
    You need to program here when you need internal trigger (internalTrigger + internalTriggerSignal) for node.
    E.g.
    internalTrigger=&(vars->trigger);
    internalTriggerSignal=QString(SIGNAL(triggerSignal()));
    */
}

void DECOFUNC(initializeOutputData)(void *paramsPtr, void *varsPtr, boost::shared_ptr<void> &outputDataPtr)
{
    ProcessorMulti_Processor_Core_Params *params = (ProcessorMulti_Processor_Core_Params *)paramsPtr;
    ProcessorMulti_Processor_Core_Vars *vars = (ProcessorMulti_Processor_Core_Vars *)varsPtr;
    outputDataPtr = boost::shared_ptr<void>(new SourceDrainMono_Sensor_EncoderIMU_Order_InputData());
    /*======Occasionally Program below/above======*/
    /*
    Function: initial output data.
    You need to program here when you need to manually initialize output data.
    */
}

void DECOFUNC(getMultiInputDataSize)(void *paramsPtr, void *varsPtr, QList<int> &inputDataSize)
{
    ProcessorMulti_Processor_Core_Params *params = (ProcessorMulti_Processor_Core_Params *)paramsPtr;
    ProcessorMulti_Processor_Core_Vars *vars = (ProcessorMulti_Processor_Core_Vars *)varsPtr;
    inputDataSize = QList<int>();
    /*======Please Program above======*/
    /*
    Function: get input data size to be grabbed from buffer.
    Rules:
    inputDataSize=0: grab and remove all data from buffer.
    inputDataSize>0: grab inputDataSize latest data from buffer.
    inputDataSize<0: grab and remove inputDataSize ancient data from buffer.
    E.g.
    inputDataSize=QList<int>()<<0<<1<<-1...;
    */
}

int loc_person_idx(short int *data, int start, int end)
{
    int min_idx = 0;
    double min_avg = 100000;
    for (int i = start; i <= end; i++)
    {
        double avg = 0;
        int valid_cnt = 0;
        for (int j = -5; j <= 5; j++)
        {
            if (i + j < 0 || i + j > 360 || data[i + j] == 0)
                continue;
            avg += data[i + j];
            valid_cnt++;
        }
        if (valid_cnt == 0)
            continue;
        avg /= valid_cnt;
        if (avg < min_avg)
        {
            min_avg = avg;
            min_idx = i;
        }
    }
    return min_idx;
}

// Input Port #0: Buffer_Size = 10, Params_Type = SourceDrainMono_Sensor_EncoderIMU_Params, Data_Type = SourceDrainMono_Sensor_EncoderIMU_Data
// Input Port #1: Buffer_Size = 10, Params_Type = SensorTimer_Sensor_URG_Params, Data_Type = SensorTimer_Sensor_URG_Data
// Input Port #2: Buffer_Size = 10, Params_Type = SensorTimer_Sensor_xtion_Params, Data_Type = SensorTimer_Sensor_xtion_Data
bool DECOFUNC(processMultiInputData)(void *paramsPtr, void *varsPtr, QVector<QVector<void *> > inputParams, QVector<QVector<void *> > inputData, void *outputData, QList<int> &outputPortIndex)
{
    ProcessorMulti_Processor_Core_Params *params = (ProcessorMulti_Processor_Core_Params *)paramsPtr;
    ProcessorMulti_Processor_Core_Vars *vars = (ProcessorMulti_Processor_Core_Vars *)varsPtr;
    QVector<SourceDrainMono_Sensor_EncoderIMU_Params *> inputparams_0;
    copyQVector(inputparams_0, inputParams[0]);
    QVector<SensorTimer_Sensor_URG_Params *> inputparams_1;
    copyQVector(inputparams_1, inputParams[1]);
    QVector<SensorTimer_Sensor_xtion_Params *> inputparams_2;
    copyQVector(inputparams_2, inputParams[2]);
    QVector<SourceDrainMono_Sensor_EncoderIMU_Data *> inputdata_0;
    copyQVector(inputdata_0, inputData[0]);
    QVector<SensorTimer_Sensor_URG_Data *> inputdata_1;
    copyQVector(inputdata_1, inputData[1]);
    QVector<SensorTimer_Sensor_xtion_Data *> inputdata_2;
    copyQVector(inputdata_2, inputData[2]);
    SourceDrainMono_Sensor_EncoderIMU_Order_InputData *outputdata = (SourceDrainMono_Sensor_EncoderIMU_Order_InputData *)outputData;
    outputPortIndex = QList<int>();
    if (inputdata_0.size() == 0)
    {
        return 0;
    }
    if (inputdata_1.size() == 0)
    {
        return 0;
    }
    if (inputdata_2.size() == 0)
    {
        return 0;
    }
    /*======Please Program below======*/
    short steer = 0;   // [-400, 400]
    short speed = 0; // [-180, 180]
    /*
    global_status:
    0: 放松，中间态
    1: 探索，走两步退一步，向四周探索
    2: 开心，快速靠近转圈，可以跟着人走
    3: 紧张，缓慢、摇摆后退
    4: 生气，快速向人冲去，蜂鸣
    5: 亲近，靠近人并且允许人触碰
    6: 跟着人走
    */
    static int global_status = 1; // 初始状态为放松
    printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n");

    printf("global status: %d\n", global_status);
    switch (global_status)
    {
    case 0:
    {
        printf("case 0: 放松，只有人靠很近才会慢慢行动\n");
        const int MAX_STOP_CNT = 1500;    // 最多再休息 MAX_STOP_CNT 次，然后进入探索模式
        static int case_0_stop_cnt = 0; // 已经休息 case_0_stop_cnt 次
        printf("case 0: 休息，已经休息了 %d 次\n", case_0_stop_cnt);

        int loc_person = loc_person_idx(inputdata_1.front()->data, 0, 360);
        int person_dis = inputdata_1.front()->data[loc_person];
        int nervous_thresh = 150;
        // 利用xtion信息决定进入哪个状态

        // 开心，手高于肘
        int head_y = inputdata_2.front()->jointPos2D[0].y;
        int left_hand_x = inputdata_2.front()->jointPos2D[6].x;
        int left_hand_y = inputdata_2.front()->jointPos2D[6].y;
        int right_hand_x = inputdata_2.front()->jointPos2D[7].x;
        int right_hand_y = inputdata_2.front()->jointPos2D[7].y;
        int left_elbow_y = inputdata_2.front()->jointPos2D[4].y;
        int right_elbow_y = inputdata_2.front()->jointPos2D[5].y;
        int left_knee_y = inputdata_2.front()->jointPos2D[11].y;
        int right_knee_y = inputdata_2.front()->jointPos2D[12].y;
        int left_foot_x = inputdata_2.front()->jointPos2D[13].x;
        int left_foot_y = inputdata_2.front()->jointPos2D[13].y;
        int right_foot_x = inputdata_2.front()->jointPos2D[14].x;
        int right_foot_y = inputdata_2.front()->jointPos2D[14].y;
        if ((left_elbow_y - left_hand_y > 35) && (right_elbow_y - right_hand_y >35))
        {
            printf("case 0: 休息中，然后遇到情况两只手高于肘，现在进入 2开心 状态\n");
            case_0_stop_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 2;   // 进入开心模式
            break;
        }
        if (person_dis < nervous_thresh)
        {
            printf("case 0: 休息中，然后遇到情况3m内有人靠近，现在进入 3紧张 状态\n");
            case_0_stop_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 3;   // 进入紧张模式
            break;
        }
        // if (abs(right_foot_y - left_foot_y) > 50) 人做出踢小车动作，双脚纵坐标之差
        if (abs(right_foot_x - left_foot_x) > 100)
        {
            printf("case 0: 休息中，然后遇到情况人将双脚岔开，现在进入 4生气 状态\n");
            case_0_stop_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 4;   // 进入生气模式
            break;
        }
        if (left_hand_y > left_knee_y && right_hand_y > right_knee_y)
        {
            printf("case 0: 休息中，然后遇到情况人蹲下，现在进入 5亲近 状态\n");
            case_0_stop_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 5;   // 进入亲近模式
            break;
        }
        if (abs(right_hand_x - left_hand_x) > 210)
        {
            printf("case 0: 休息中，然后遇到情况人张开双手，现在进入 6跟随 状态\n");
            case_0_stop_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 6;   // 进入跟随模式
            break;
        }

        // 以上情况均未出现
        case_0_stop_cnt++;
        if (case_0_stop_cnt == MAX_STOP_CNT)
        {
            printf("case 0: 休息中，然后遇到情况：休息了 MAX_STOP_CNT 次，现在进入 1 状态\n");
            case_0_stop_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 1;   // 进入探索模式
            break;
        }
        break;
    }

    case 1:
    {
        printf("case 1: 探索，走两步退一步，向四周探索\n");
        const int MAX_MOVE_CNT = 5;         // 最多探索 MAX_MOVE_CNT 次，然后进入放松模式
        static int case_1_move_cnt = 0;      // 已经行动了 case_1_move_cnt 次
        static int case_1_forward_cnt = 0;   // 已经向前探索 case_1_forward_cnt 次
        static int case_1_backward_cnt = 0;  // 已经向后探索 case_1_backward_cnt 次
        if (case_1_move_cnt == MAX_MOVE_CNT) // 行动完成
        {
            printf("case 1: 探索完成，现在进入放松状态\n");
            case_1_move_cnt = 0;     // 重置这个 case 所有的静态变量
            case_1_forward_cnt = 0;  // 重置这个 case 所有的静态变量
            case_1_backward_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 0;       // 进入放松模式
            break;
        }
        // 然后四周探索，case_1_forward_cnt 先增加到 MAX_FORWARD_CNT，然后 case_1_backward_cnt 增加到 MAX_BACKWARD_CNT，然后两者都变成 0 ，然后重复
        printf("case 1: 探索中，还要探索 %d 次\n", case_1_move_cnt);
        const int MAX_FORWARD_CNT = 40;  // 最多向前探索 MAX_FORWARD_CNT 次，然后向后探索
        const int MAX_BACKWARD_CNT = 30; // 最多向后探索 MAX_BACKWARD_CNT 次，然后向前探索

        if (case_1_forward_cnt < MAX_FORWARD_CNT)
        {
            printf("case 1: 向前探索，已经向前探索了 %d 次\n", case_1_forward_cnt);
            case_1_forward_cnt++;
            steer = 400; // 不要转太多
            speed = 120;  // 慢慢向前探索
        }
        else if (case_1_backward_cnt < MAX_BACKWARD_CNT)
        {
            printf("case 1: 向后探索，已经向后探索了 %d 次\n", case_1_backward_cnt);
            case_1_backward_cnt++;
            steer = -400; // 不要转太多
            speed = -120;  // 慢慢向后探索
        }
        else
        {
            case_1_move_cnt++;
            case_1_forward_cnt = 0;
            case_1_backward_cnt = 0;
        }
        break;
    }

    case 2:
    {
        printf("case 2: 开心，快速靠近逆时针转圈，可以跟着人走\n");
        const int MAX_MOVE_CNT = 500;                  // 最多开心 MAX_MOVE_CNT 次，然后进入放松模式
        static int case_2_move_cnt = 0;                // 已经开心了 case_2_move_cnt 次
        static int case_2_near_person = 0;             // 人是否在 1m 以内
        static int case_2_near_person_prepare_cnt = 0; // 人在 1m 以内已经右转的次数
        if (case_2_move_cnt == MAX_MOVE_CNT)
        {
            printf("case 2: 开心完成，现在进入放松状态\n");
            case_2_move_cnt = 0;                // 重置这个 case 所有的静态变量
            case_2_near_person = 0;             // 重置这个 case 所有的静态变量
            case_2_near_person_prepare_cnt = 0; // 重置这个 case 所有的静态变量
            global_status = 0;                  // 进入放松模式
            break;
        }
        printf("case 2: 开心中，还要开心 %d 次\n", MAX_MOVE_CNT - case_2_move_cnt);

        const int MAX_NEAR_PERSON_PREPARE_CNT = 100; // 人在 1m 以内需要右转才能准备左转的次数

        if (case_2_near_person == 0)
        {
            printf("case 2: 开心中，人不在 1m 以内，现在直行靠近人\n");
            // 然后检测人是否在 1m 以内，设置静态变量 case_2_near_person
            int is_near_person = 0;

            for (int i = 120; i <= 240; i++) //扫描前方60度
            {
                double avg = 0;
                int valid_cnt = 0;
                for (int j = -5; j <= 5; j++)
                {
                    if (i + j < 0 || i + j > 360 || inputdata_1.front()->data[i + j] == 0)
                        continue;
                    avg += inputdata_1.front()->data[i + j];
                    valid_cnt++;
                }
                if (valid_cnt == 0)
                    continue;
                avg /= valid_cnt;
                if (avg < 300)
                {
                    is_near_person = 1;
                    break;
                }
            }
            if (is_near_person)
            {
                printf("case 2: 突然发现有人在 1m 以内，现在从直行变为逆时针绕圈\n");
                case_2_near_person = 1;
                steer = 400;
                speed = 180;
                break;
            }
            else
            {
                printf("case 2: 仍然没有人在 1m 以内，现在直行靠近人\n");
                steer = 0;
                speed = 180;
                break;
            }
        }
        else
        {
            if (case_2_near_person_prepare_cnt < MAX_NEAR_PERSON_PREPARE_CNT)
            {
                printf("case 2: 开心中，人在 1m 以内，但是还没有准备好，现在右转\n");
                case_2_near_person_prepare_cnt++;
                steer = 400;
                speed = 180;
                break;
            }
            else
            {
                printf("case 2: 开心中，人在 1m 以内，已经准备好，现在逆时针绕圈\n");
                steer = -400;
                speed = 180;
                case_2_move_cnt++; // 绕圈一定时间后回归放松状态
                break;
            }
        }
        break;
    }

    case 3:
    {
        printf("case3: 紧张\n");
        const int MAX_MOVE_CNT = 30; // 在无人时最多紧张 MAX_MOVE_CNT 次，然后进入放松模式
        static int case_3_move_cnt = 0;
        if (case_3_move_cnt == MAX_MOVE_CNT)
        {
            printf("case 3: 紧张结束，现在进入放松状态\n");
            case_3_move_cnt = 0;
            global_status = 0;
            break;
        }
        int nervous_thresh1 = 150, nervous_thresh2 = 100;
        int person_loc = loc_person_idx(inputdata_1.front()->data, 60, 300);
        int person_dis = inputdata_1.front()->data[person_loc];
        printf("case3: 紧张中，人在 %d 度方向，距离 %d\n", person_loc, person_dis);
        if (person_dis < nervous_thresh1 && person_dis > nervous_thresh2)
        {
            speed = -90;                      // 抖动方向慢速后退
            steer = (rand() % 800 - 400) / 2; // 抖动幅度不必太大
        }
        else if (person_dis < nervous_thresh2)
        {
            speed = -180;                            // 较为明显快速的后退
            steer = -(400 - person_loc / 360.0 * 800); // 直接远离人所在方向

        }
        else
        { // 在无人状态下待够一定时间就会进入放松状态
            speed = 0;
            steer = 0;
            case_3_move_cnt++;
            printf("case3:nervous left %d times\n", case_3_move_cnt);
        }
        break;
    }

    case 4:
    {
        printf("case4: 生气，快速向人冲去");
        const int MAX_MOVE_CNT = 50; // 最多生气 MAX_MOVE_CNT 次，然后进入放松模式
        const int MAX_NEAR_PERSON_CNT = 30;
        static int case_4_move_cnt = 0;
        static int case_4_near_person = 0; // 人是否在 safe_thresh 以内
        if (case_4_move_cnt == MAX_MOVE_CNT)
        {
            printf("case 4: 生气结束，现在进入放松状态\n");
            case_4_move_cnt = 0;
            global_status = 0;
            case_4_near_person = 0;
            break;
        }
        // 还是需要设一个 angre_thresh ，这样只要人远离了就不再生气了
        int angry_thresh = 250, safe_thresh = 80;
        int person_loc = loc_person_idx(inputdata_1.front()->data, 90, 270);
        int person_dis = inputdata_1.front()->data[person_loc];
        if ((case_4_near_person != 0) && (case_4_near_person < MAX_NEAR_PERSON_CNT))
        {
            printf("case 4:离人过近，后退中\n");
            speed = -100;
            steer = 400 - person_loc / 360.0 * 800;
            case_4_near_person++;
            break;
        }
        if (person_dis < angry_thresh && person_dis > safe_thresh)
        {
            printf("case 4: 生气中，人在 %d 度方向，距离 %lf\n", person_loc, person_dis);
            speed = 180;
            steer = 400 - person_loc / 360.0 * 800;
            case_4_near_person = 0;
        }
        else if (person_dis < safe_thresh)
        {
            if (case_4_near_person == 0)
            {
                speed = -100;
                steer = 400 - person_loc / 360.0 * 800;
                case_4_near_person++;
            }
            // 若退出safe_thresh之后会继续向人冲去
        }
        else
        { // 在无人状态下待够一定时间就会进入放松状态
            speed = 0;
            steer = 0;
            case_4_move_cnt++;
        }
        break;
    }

    case 5: // 亲近，靠近人并且允许人触碰
    {
        const int MAX_MOVE_CNT = 200; // 最多亲近 MAX_MOVE_CNT 次，然后进入放松模式
        static int case_5_move_cnt = 0;
         static int is_stopped=0;

        if (case_5_move_cnt == MAX_MOVE_CNT)
        {
            printf("case 5: 亲近结束，现在进入放松状态\n");
            case_5_move_cnt = 0;
            global_status = 0;
            is_stopped=0;
            break;
        }
        int intimate_thresh1 = 150; // 进入这个范围速度要变慢
        int intimate_thresh2 = 40;  // 距离人足够近的时候停下
        int person_loc = loc_person_idx(inputdata_1.front()->data, 150, 210);
        int person_dis = inputdata_1.front()->data[person_loc];
        printf("case 5: 亲近中，人在 %d 度方向，距离 %d\n", person_loc, person_dis);
        if(is_stopped && person_dis < intimate_thresh1)
        {
            speed = 0;
            steer = 0;
            break;
        }
        else if(is_stopped && person_dis > intimate_thresh1){
            case_5_move_cnt++;
            break;
        }
        if (person_dis > intimate_thresh1)
        {
            speed = 150;
            steer = 400 - person_loc / 360.0 * 800;
            // case_5_move_cnt++;
        }
        else if (person_dis < intimate_thresh1 && person_dis > intimate_thresh2)
        {
            speed = 90; // 减速靠近
            steer = 400 - person_loc / 360.0 * 800;
            // case_5_move_cnt++;
        }
        else if (person_dis < intimate_thresh2)
        {
            is_stopped=1;
            speed = 0;
            steer = 0;
        }
        break;
    }

    /*case6跟着人走*/
    case 6:
    {
        const int MAX_MOVE_CNT = 600; // 最多跟随 MAX_MOVE_CNT 次，然后进入放松模式
        static int case_6_move_cnt = 0;
        if (case_6_move_cnt == MAX_MOVE_CNT)
        {
            printf("case 6: 跟随结束，现在进入放松状态\n");
            case_6_move_cnt = 0;
            global_status = 0;
            break;
        }
        int person_loc = loc_person_idx(inputdata_1.front()->data, 60, 300);
        int person_dis = inputdata_1.front()->data[person_loc];
        printf("case 6: 跟着人走, 人在 %d 度方向，距离 %d\n", person_loc, person_dis);
        speed = 180;
        steer = 400 - person_loc / 360.0 * 800;
        case_6_move_cnt++;
        break;
    }
    default:
        break;
    }


    steer*=8;
    int maxSpeed = 180;
    if (speed > maxSpeed)
        speed = maxSpeed;
    if (speed < -maxSpeed)
        speed = -maxSpeed;
    if (steer > 400)
        steer = 400;
    if (steer < -400)
        steer = -400;
    printf("speed=%d, steer=%d\n", speed, steer);

    //--------------------------------------------
    // 输出xtion数据
    for (int i = 0; i < 15; i++)
    {
        printf("2D[%d].x=%d\n", i, inputdata_2.front()->jointPos2D[i].x);
        printf("2D[%d].y=%d\n", i, inputdata_2.front()->jointPos2D[i].y);
    }


    char dataput[20];
    dataput[0] = 0xF8;
    dataput[1] = 4;
    *(short *)&dataput[2] = (short)steer;
    *(short *)&dataput[4] = -(short)speed;
    dataput[6] = 0x8F;
    outputdata->datagram = QByteArray(dataput, 7);
    return 1;
}
