/*
	Copyright (c) 2020 Technica Engineering GmbH
	GNU General Public License v3.0+ (see LICENSE or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include <errno.h>
#include <string.h>

#include "tecmp/tecmp.h"
#include "endianness.h"

void ntoh_tecmp_header(tecmp_header* header)
{
	// Shared header
	header->cm_id = ntoh16(header->cm_id);
	header->counter = ntoh16(header->counter);

	header->data_type = ntoh16(header->data_type);

	header->_reserved = ntoh16(header->_reserved);
	header->cm_flags = ntoh16(header->cm_flags);

	// Packetized header

	header->channel_id = ntoh32(header->channel_id);

	header->_timestamp = ntoh64(header->_timestamp);

	header->length = ntoh16(header->length);
	header->data_flags = ntoh16(header->data_flags);
}

#define ETH_SIZE 14
#define TECMP_H1_SIZE 12
#define TECMP_H2_SIZE 16

int tecmp_next(
	const uint8_t* raw_frame, const int32_t raw_frame_size,
	int32_t* iterator,
	tecmp_header* header, uint8_t** data
)
{
	// No Frame
	if (raw_frame == NULL) {
		return EINVAL;
	}

	// Frame too small
	if (raw_frame_size < ETH_SIZE + TECMP_H1_SIZE + TECMP_H2_SIZE) {
		return ENODATA;
	}

	uint16_t ether = ntoh16(*((uint16_t*)(raw_frame + 12)));

	// Ethertype mismatch
	if (!(ether == 0x2090 || ether == 0x99FE)) {
		return EINVAL;
	}

	int32_t h2_offset;
	if (iterator == NULL || *iterator == 0) {
		h2_offset = ETH_SIZE + TECMP_H1_SIZE;
	}
	else {
		h2_offset = (int32_t)*iterator;
	}

	// We don't have enough remaining bytes to read more
	if (raw_frame_size < h2_offset + (int64_t)TECMP_H2_SIZE) {
		return ENODATA;
	}

	memcpy(header, raw_frame + ETH_SIZE, 12);
	memcpy(&header->channel_id, raw_frame + h2_offset, TECMP_H2_SIZE);

	ntoh_tecmp_header(header);

	int32_t data_offset = h2_offset + TECMP_H2_SIZE;

	// Possible Ethernet padding
	if (!header->length) {
		return ENODATA;
	}

	// Data overflow raw_frame
	if (raw_frame_size < data_offset + header->length) {
		return EINVAL;
	}

	*data = (uint8_t*)raw_frame + data_offset;

	if (iterator != NULL) {
		*iterator = data_offset + header->length;
	}

	return 0;
}

struct timeval tecmp_get_timeval(const tecmp_header header)
{
	uint64_t t = header._timestamp & 0x7FFFFFFFFFFFFFFF;
	uint64_t sec = t / 1000000000;
	uint64_t nsec = t % 1000000000;
	struct timeval time = { sec, nsec / 1000 };
	return time;
}

struct timespec tecmp_get_timespec(const tecmp_header header)
{
	uint64_t t = header._timestamp & 0x7FFFFFFFFFFFFFFF;
	uint64_t sec = t / 1000000000;
	uint64_t nsec = t % 1000000000;
	struct timespec time = { sec, nsec };
	return time;
}

int tecmp_get_cm_status(const tecmp_header header, const uint8_t* data, tecmp_cm_status* status)
{
	if (header.message_type != TECMP_TYPE_CM_STATUS) {
		return EINVAL;
	}
	if (header.length < sizeof(tecmp_cm_status)) {
		return EINVAL;
	}
	memcpy(status, data, sizeof(tecmp_cm_status));

	status->_vdl = ntoh16(status->_vdl);
	status->cm_id = ntoh16(status->cm_id);
	status->serial_number = ntoh32(status->serial_number);

	status->vendor.buffer_size = ntoh32(status->vendor.buffer_size);
	status->vendor.lifecycle = ntoh64(status->vendor.lifecycle);

	return 0;
}

#define BUS_STATUS_H1_SIZE 12
#define BUS_STATUS_H2_SIZE 12
int tecmp_next_bus_status(
	const tecmp_header header, const uint8_t* data,
	int32_t* iterator,
	tecmp_bus_status* status)
{
	if (header.message_type != TECMP_TYPE_BUS_STATUS) {
		return EINVAL;
	}
	if (header.length < sizeof(tecmp_bus_status)) {
		return EINVAL;
	}

	// We need to set it to 0, since some vendor data my be ommitted
	memset(status, 0, sizeof(tecmp_bus_status));
	memcpy(status, data, BUS_STATUS_H1_SIZE);
	status->_vdl = ntoh16(status->_vdl);
	status->cm_id = ntoh16(status->cm_id);
	status->serial_number = ntoh32(status->serial_number);

	int32_t h2_offset;
	if (iterator == NULL || *iterator == 0) {
		h2_offset = BUS_STATUS_H1_SIZE;
	}
	else {
		h2_offset = (int32_t)*iterator;
	}

	int32_t h2_size;
	if (status->_vdl < 4) {
		h2_size = BUS_STATUS_H2_SIZE + status->_vdl;
	}
	else {
		h2_size = BUS_STATUS_H2_SIZE + 4;
	}

	// We don't have enough remaining bytes to read more
	if (header.length < h2_offset + h2_size) {
		return ENODATA;
	}


	memcpy(&status->channel_id, data + h2_offset, h2_size);

	uint32_t channel_id;

	uint32_t messages_total;
	uint32_t errors_total;

	status->channel_id = ntoh32(status->channel_id);
	status->messages_total = ntoh32(status->messages_total);
	status->errors_total = ntoh32(status->errors_total);

	status->vendor.linkup_time = ntoh16(status->vendor.linkup_time);

	if (iterator != NULL) {
		*iterator = h2_offset + h2_size;
	}

	return 0;
}