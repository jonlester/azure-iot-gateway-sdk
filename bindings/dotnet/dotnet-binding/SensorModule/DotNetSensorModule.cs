// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Azure.IoT.Gateway;
using System.Threading;
using Common;

namespace SensorModule
{
    public class DotNetSensorModule : IGatewayModule, IGatewayModuleStart
    {
        private Broker broker;
        private string configuration;

        public void Create(Broker broker, byte[] configuration)
        {
            this.broker = broker;
            this.configuration = System.Text.Encoding.UTF8.GetString(configuration);
        }

        public void Start()
        {
            foreach (var sku in BOM.Skus.Where(x=> x.parts.Any()))
            {
                Thread oThread = new Thread(() => this.threadBody(sku.name));
                // Start the thread
                oThread.Start();
            }
        }

        public void Destroy()
        {
        }

        public void Receive(Message received_message)
        {
            //Just Ignore the Message. Sensor doesn't need to print.
        }

        public void threadBody(string sku)
        {
            Random rand = new Random();
            while (true)
            {
                //since this is a simulation, we need to make sure 
                //the quantity of parts exists to make this sku
                if (BOM.CanMakeSku(sku))
                {
                    var skuData = BOM.Skus.First(x => x.name == sku);
                    Dictionary<string, string> thisIsMyProperty = new Dictionary<string, string>();
                    thisIsMyProperty.Add("source", "sensor");
                    thisIsMyProperty.Add("sku", sku);
                    int qty = 0;
                    if(skuData.avgYieldPerHour > 0)
                        qty = (rand.Next(99) < ((float)(skuData.avgYieldPerHour * 100)) / (float)(skuData.productionRatePerHour)) ? 1 : 0;
                    Message messageToPublish = new Message(qty.ToString(), thisIsMyProperty);

                    this.broker.Publish(messageToPublish);

                    Thread.Sleep(Convert.ToInt32(3600000f/ (float)(skuData.productionRatePerHour)));
                }
            }
        }
    }
}
