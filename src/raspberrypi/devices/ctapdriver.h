//---------------------------------------------------------------------------
//
//	SCSI Target Emulator RaSCSI (*^..^*)
//	for Raspberry Pi
//
//	Powered by XM6 TypeG Technology.
//	Copyright (C) 2016-2020 GIMONS
//  Copyright (C) akuker
//
//	Imported NetBSD support and some optimisation patch by Rin Okuyama.
//
//	[ TAP Driver ]
//
//---------------------------------------------------------------------------

#pragma once

#include <pcap/pcap.h>
#include "filepath.h"
#include <vector>
#include <string>

#ifndef ETH_FRAME_LEN
#define ETH_FRAME_LEN 1514
#endif

//===========================================================================
//
//	Linux Tap Driver
//
//===========================================================================
class CTapDriver
{
public:
	CTapDriver(const std::string&);
	~CTapDriver() {};

	bool Init();
	void OpenDump(const Filepath& path);
										// Capture packets
	void Cleanup();						// Cleanup
	void GetMacAddr(BYTE *mac);					// Get Mac Address
	int Rx(BYTE *buf);						// Receive
	int Tx(const BYTE *buf, int len);					// Send
	BOOL PendingPackets();						// Check if there are IP packets available
	bool Enable();						// Enable the ras0 interface
	bool Disable();				// Disable the ras0 interface
	BOOL Flush();				// Purge all of the packets that are waiting to be processed

private:
	BYTE m_MacAddr[6];							// MAC Address
	BOOL m_bTxValid;							// Send Valid Flag
	int m_hTAP;								// File handle

	BYTE m_garbage_buffer[ETH_FRAME_LEN];

	pcap_t *m_pcap;
	pcap_dumper_t *m_pcap_dumper;

	// Prioritized comma-separated list of interfaces to create the bridge for
	std::vector<std::string> interfaces;
};

