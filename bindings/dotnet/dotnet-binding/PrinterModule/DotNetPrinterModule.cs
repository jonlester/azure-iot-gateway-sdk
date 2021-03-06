﻿// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Azure.IoT.Gateway;


namespace PrinterModule
{
    public class DotNetPrinterModule : IGatewayModule
    {
        private string configuration;
        public void Create(Broker broker, byte[] configuration)
        {
            this.configuration = System.Text.Encoding.UTF8.GetString(configuration);
        }

        public void Destroy()
        {
        }

        public void Receive(Message received_message)
        {
            if(received_message.Properties["source"] == "inventory")
                Console.WriteLine("Inventory Message: SKU=" + received_message.Properties["sku"] + ", Qty=" + System.Text.Encoding.UTF8.GetString(received_message.Content, 0, received_message.Content.Length)
                    + ", QualityScore=" + received_message.Properties["qualityScore"]);
            else if (received_message.Properties["source"] == "sensor")
                Console.WriteLine("Sensor Message: SKU=" + received_message.Properties["sku"] + ", Qty=" + System.Text.Encoding.UTF8.GetString(received_message.Content, 0, received_message.Content.Length));
        }
    }
}
