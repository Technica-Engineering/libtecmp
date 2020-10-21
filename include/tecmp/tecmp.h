/*
	Copyright (c) 2020 Technica Engineering GmbH
	GNU General Public License v3.0+ (see LICENSE or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#pragma once

#include <stdint.h>
#include <time.h>
#if defined(_WIN32)
#include <winsock2.h>
#else
#include <sys/time.h>
#endif

// TECMP Message Types

#define TECMP_TYPE_CONTROL_MESSAGE		0x0
#define TECMP_TYPE_CM_STATUS			0x1
#define TECMP_TYPE_BUS_STATUS			0x2
#define TECMP_TYPE_LOGGING_STREAM		0x3
#define TECMP_TYPE_CONFIG_STATUS		0x4
#define TECMP_TYPE_REPLAY_DATA			0xA

// TECMP Data Types
#define TECMP_DATA_CAN			0x0002
#define TECMP_DATA_CANFD		0x0003
#define TECMP_DATA_LIN			0x0004
#define TECMP_DATA_FLEXRAY		0x0008

#define TECMP_DATA_GPIO			0x000A

#define TECMP_DATA_UART_ASCII	0x0010
#define TECMP_DATA_UART_SLA		0x0012

#define TECMP_DATA_ANALOG		0x0020
#define TECMP_DATA_ANALOG_SLA	0x0021

#define TECMP_DATA_ETHERNET		0x0080


// TECMP CM IDs
#define	TECMP_LIN_COMBO_0	48
#define	TECMP_LIN_COMBO_1	49
#define	TECMP_LIN_COMBO_2	50
#define	TECMP_LIN_COMBO_3	51
#define	TECMP_LIN_COMBO_4	52
#define	TECMP_LIN_COMBO_5	53
#define	TECMP_LIN_COMBO_6	54
#define	TECMP_LIN_COMBO_7	55
#define	TECMP_LIN_COMBO_8	56
#define	TECMP_LIN_COMBO_9	57
#define	TECMP_LIN_COMBO_10	58
#define	TECMP_LIN_COMBO_11	59
#define	TECMP_LIN_COMBO_12	60
#define	TECMP_LIN_COMBO_13	61
#define	TECMP_LIN_COMBO_14	62
#define	TECMP_LIN_COMBO_15	63

#define	TECMP_CAN_COMBO_0	64
#define	TECMP_CAN_COMBO_1	65
#define	TECMP_CAN_COMBO_2	66
#define	TECMP_CAN_COMBO_3	67
#define	TECMP_CAN_COMBO_4	68
#define	TECMP_CAN_COMBO_5	69
#define	TECMP_CAN_COMBO_6	70
#define	TECMP_CAN_COMBO_7	71
#define	TECMP_CAN_COMBO_8	72
#define	TECMP_CAN_COMBO_9	73
#define	TECMP_CAN_COMBO_10	74
#define	TECMP_CAN_COMBO_11	75
#define	TECMP_CAN_COMBO_12	76
#define	TECMP_CAN_COMBO_13	77
#define	TECMP_CAN_COMBO_14	78
#define	TECMP_CAN_COMBO_15	79

#define	TECMP_100_HIGH_0	96
#define	TECMP_100_HIGH_1	97
#define	TECMP_100_HIGH_2	98
#define	TECMP_100_HIGH_3	99
#define	TECMP_100_HIGH_4	100
#define	TECMP_100_HIGH_5	101
#define	TECMP_100_HIGH_6	102
#define	TECMP_100_HIGH_7	103
#define	TECMP_100_HIGH_8	104
#define	TECMP_100_HIGH_9	105
#define	TECMP_100_HIGH_10	106
#define	TECMP_100_HIGH_11	107
#define	TECMP_100_HIGH_12	108
#define	TECMP_100_HIGH_13	109
#define	TECMP_100_HIGH_14	110
#define	TECMP_100_HIGH_15	111

#define	TECMP_ETH_COMBO_0	128
#define	TECMP_ETH_COMBO_1	129
#define	TECMP_ETH_COMBO_2	130
#define	TECMP_ETH_COMBO_3	131
#define	TECMP_ETH_COMBO_4	132
#define	TECMP_ETH_COMBO_5	133
#define	TECMP_ETH_COMBO_6	134
#define	TECMP_ETH_COMBO_7	135
#define	TECMP_ETH_COMBO_8	136
#define	TECMP_ETH_COMBO_9	137
#define	TECMP_ETH_COMBO_10	138
#define	TECMP_ETH_COMBO_11	139
#define	TECMP_ETH_COMBO_12	140
#define	TECMP_ETH_COMBO_13	141
#define	TECMP_ETH_COMBO_14	142
#define	TECMP_ETH_COMBO_15	143

#define	TECMP_1000_HIGH_0	144
#define	TECMP_1000_HIGH_1	145
#define	TECMP_1000_HIGH_2	146
#define	TECMP_1000_HIGH_3	147
#define	TECMP_1000_HIGH_4	148
#define	TECMP_1000_HIGH_5	149
#define	TECMP_1000_HIGH_6	150
#define	TECMP_1000_HIGH_7	151
#define	TECMP_1000_HIGH_8	152
#define	TECMP_1000_HIGH_9	153
#define	TECMP_1000_HIGH_10	154
#define	TECMP_1000_HIGH_11	155
#define	TECMP_1000_HIGH_12	156
#define	TECMP_1000_HIGH_13	157
#define	TECMP_1000_HIGH_14	158
#define	TECMP_1000_HIGH_15	159

#pragma pack(push, 1)

typedef struct tecmp_header {
	// Shared header

	uint16_t cm_id;
	uint16_t counter;

	uint8_t version;
	uint8_t message_type;
	uint16_t data_type;

	uint16_t _reserved;
	uint16_t cm_flags;

	// Packetized header

	uint32_t channel_id;

	uint64_t _timestamp;

	uint16_t length;
	uint16_t data_flags;

} tecmp_header;

typedef struct tecmp_cm_status_vendor
{
	uint8_t _reserved;
	uint8_t sw_version_major;
	uint8_t sw_version_minor;
	uint8_t sw_version_patch;

	uint8_t hw_version_major;
	uint8_t hw_version_minor;

	uint8_t buffer_fill;
	uint8_t buffer_overflow;

	uint32_t buffer_size;
	uint64_t lifecycle;

	uint8_t voltage_int;
	uint8_t voltage_frac;
	uint8_t temperature;

} tecmp_cm_status_vendor;

typedef struct tecmp_cm_status {
	uint8_t _vendor_id;
	uint8_t cm_version;
	uint8_t cm_type;
	uint8_t _reserved;

	uint16_t _vdl;
	uint16_t cm_id;

	uint32_t serial_number;

	tecmp_cm_status_vendor vendor;

} tecmp_cm_status;

typedef struct tecmp_bus_status_vendor
{
	uint8_t link_status;
	uint8_t link_quality;
	uint16_t linkup_time;

} tecmp_bus_status_vendor;

typedef struct tecmp_bus_status {
	uint8_t _vendor_id;
	uint8_t cm_version;
	uint8_t cm_type;
	uint8_t _reserved;

	uint16_t _vdl;
	uint16_t cm_id;

	uint32_t serial_number;

	uint32_t channel_id;

	uint32_t messages_total;
	uint32_t errors_total;

	tecmp_bus_status_vendor vendor;

} tecmp_bus_status;



#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

	/*
	 * Extract the TECMP header and data from the raw frame.
	 *
	 * @param[in]		raw_frame		Original frame captured on the network.
	 * @param[in]		raw_frame_size	Original frame size.
	 * @param[in/out]	iterator		The pointer to iterate next tecmp header/data in same raw_frame.
	 * @param[out]		header			The TECMP header.
	 * @param[out]		data			The TECMP data, see data_type for how to interpret data.
	 * @return 0 if success, error number from errno.h otherwise.
	 */
	int tecmp_next(
		const uint8_t* raw_frame, const int32_t raw_frame_size,
		int32_t* iterator,
		tecmp_header* header, uint8_t** data
	);

	/*
	 * Extract the timestamp from the TECMP header.
	 *
	 * @param[in]  header			The TECMP header.
	 * @return the timestamp as timeval.
	 */
	struct timeval tecmp_get_timeval(const tecmp_header header);

	/*
	 * Extract the timestamp from the TECMP header.
	 *
	 * @param[in]  header			The TECMP header.
	 * @return the timestamp as timespec.
	 */
	struct timespec tecmp_get_timespec(const tecmp_header header);


	/*
	 * @param[in]	header			The TECMP header.
	 * @param[in]	data			The TECMP data.
	 * @param[out]	status			The capture module status.
	 * @return 0 if success, error number from errno.h otherwise.
	 */
	int tecmp_get_cm_status(const tecmp_header header, const uint8_t* data, tecmp_cm_status* status);

	/*
	 * @param[in]		header			The TECMP header.
	 * @param[in]		data			The TECMP data.
	 * @param[in/out]	iterator		The pointer to iterate next tecmp_cm_status in same header/data.
	 * @param[out]		status			The bus status.
	 * @return 0 if success, error number from errno.h otherwise.
	 */
	int tecmp_next_bus_status(
		const tecmp_header header, const uint8_t* data,
		int32_t* iterator,
		tecmp_bus_status* status);


#ifdef __cplusplus
}
#endif