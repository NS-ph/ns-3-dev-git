/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */            
/*
 * Copyright (c) 2008 IT-SUDPARIS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Providence SALUMU M. <Providence.Salumu_Munga@it-sudparis.eu>
 */

#include <vector>
#include <iostream>
#include <stdint.h>
#include "ns3/core-module.h"
#include "ns3/mih-module.h"

using namespace ns3::mih;
using namespace ns3;

static const uint8_t numberOfResponses = 10;
Ptr<UniformRandomVariable> rng (0, numberOfResponses);
Ptr<UniformRandomVariable> rng2 (0, 500);
const char* vendors[numberOfResponses] = {
  "Samsung", /*0*/
  "Cisco",
  "LG",
  "Texas Instruments",
  "MemUp",
  "Nvidia", /*5*/
  "Broadcom",
  "Intel",
  "Amd",
  "ATI" /*9*/
};

DeviceStatesResponseList responses;
DeviceStatesResponseList responsesDup;

void 
CreateVendor (int num)
{
  if (num % 2 == 0)
    {
      Ptr<BatteryLevel> battery;
      battery = Create<BatteryLevel> (uint8_t(rng->GetValue ()));
      responses.push_back (battery);
    }
  else
    {
      Ptr<DeviceInformation> deviceInformation;
      deviceInformation = Create<DeviceInformation> (std::string(vendors[int (rng->GetValue ())]));
      responses.push_back (deviceInformation);
    }
};

void 
PrintDeviceStatesResponse (Ptr<DeviceStatesResponse> rsp)
{
  NS_ASSERT_MSG (rsp != 0, "Can not print an empty element!");
  if (rsp->GetType () == DeviceInformation::GetClassType ())
    {
      Ptr<DeviceInformation> deviceInformation = DynamicCast<DeviceInformation, DeviceStatesResponse> (rsp);
      deviceInformation->Print (std::cout);
    }
  else if (rsp->GetType () == BatteryLevel::GetClassType ())
    {
      Ptr<BatteryLevel> battery = DynamicCast<BatteryLevel, DeviceStatesResponse> (rsp);
      battery->Print (std::cout);
    }
  else 
    {
      NS_ASSERT (0);
    }
};

int 
main (int argc, char *argv[])
{
  int numberOfIter = 0;
  while (numberOfIter < 5)
    {
      numberOfIter = int (rng2->GetValue ());
    }

  std::cout << "There will be " << numberOfIter << " elements created!" << std::endl;
  for (int i = 0; i < numberOfIter; i++)
    {
      CreateVendor (int (rng2->GetValue ()));
    }
  responsesDup = responses;
  responses.clear ();
  
  for (int i = 0; i < numberOfIter; i++)
    {
      PrintDeviceStatesResponse (responsesDup[i]);
      // responses[i] = 0;
    }

  return 0;
}



