#ifndef PROTOCOL_H
#define PROTOCOL_H



typedef enum
{
    CMD_SET_SPEED = 10,
    CMD_SET_TSPEED = 11,
    CMD_GET_SPEED_LIM = 12,
    CMD_GET_SPEED_LIM_ANS = 13,

    CMD_SET_LED = 20,

} cmd_type_t;


/** Command:
 *  1 byte header (cmd_type_t) | payload
 *
 *  Motor commands:
 *    Set speed:
 *      CMD_SET_SPEED   (uint8) 
 *      speed_value     (uint8)
 *        between MT_MIN_SPEED & MT_MAX_SPEED
 *
 *    Set speed during a given time:
 *      CMD_SET_TSPEED
 *      speed_value     (uint8)
 *        between local min speed & max speed or 0
 *        see CMD_GET_SPEED_LIM
 *      length        (uint16)
 *        in PWM timer tick
 *
 *    Get motor speed limits:
 *      CMD_GET_SPEED_LIM
 *        request motor speed limits
 *
 *    Speed limits answer:
 *      CMD_GET_SPEED_LIM_ANS
 *      min     (uint8)
 *        min motor speed
 *      max     (uint8)
 *        max motor speed
 *   
 *
 *  LED commands:
 *    Set led:
 *      CMD_SET_LED     (uint8) 
 *      status          (uint8)
 *        0 -> LED OFF, other value -> LED ON
 *
 *
 *
 *  CMD_SET_TSPEED | speed_value (uint8) | length (uint16)
 */


#endif
