/*
	Copyright (c) 2020 Technica Engineering GmbH
	GNU Lesser General Public License v3.0 or later (see LICENSE or https://www.gnu.org/licenses/lgpl-3.0.txt)
*/

#include <unordered_map>
#include <errno.h>
#include <tecmp/tecmp.h>
#include "PcapFileDevice.h"
#include <time.h>

using namespace pcpp;
using namespace std;

/*
 * Sample app to write packetized TECMP into depacketized TECMP
 * Also removes the TECMP header from Ethernet Data Frames
 */
int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage: %s [infile] [outfile]\n", argv[0]);
		return EINVAL;
	}
	auto reader = IFileReaderDevice::getReader(argv[1]);
	PcapFileWriterDevice writer(argv[2], LINKTYPE_ETHERNET);

	// verify that a reader interface was indeed created
	if (reader == NULL)
	{
		printf("Cannot determine reader for file type\n");
		exit(1);
	}
	if (!reader->open())
	{
		printf("Cannot open file for reading\n");
		exit(1);
	}

	if (!writer.open())
	{
		printf("Cannot open file for writing\n");
		exit(1);
	}

	// the packet container
	RawPacket p;

	// a while loop that will continue as long as there are packets in the input file
	// matching the BPF filter
	while (reader->getNextPacket(p))
	{
		int32_t iterator = 0;
		tecmp_header header;
		uint8_t* data;

		int res = tecmp_next(p.getRawData(), p.getRawDataLen(), &iterator, &header, &data);

		if (res == EINVAL) {

			// Not a TECMP packet
			writer.writePacket(p);
		}
		else {
			while (res == 0) {

				RawPacket newP;
				timeval time = tecmp_get_timeval(header);
				// Capture Module MTU = 1600
				uint8_t buffer[1600];

				// 14 Ethernet header + TECMP header
				const uint16_t head_size = 14 + 12;
				memcpy(buffer, p.getRawData(), head_size);

				// Copy the payload header and data
				const uint16_t hdr_size = 16;
				memcpy(buffer + head_size, data - hdr_size, header.length + hdr_size);


				newP = RawPacket(buffer, header.length + head_size + hdr_size, time, false);

				// Write packet back
				writer.writePacket(newP);

				// Next packet within TECMP
				res = tecmp_next(p.getRawData(), p.getRawDataLen(), &iterator, &header, &data);
			}
		}

	reader->close();
	writer.close();

	// free reader memory because it was created by IFileReaderDevice::getReader()
	delete reader;
}
