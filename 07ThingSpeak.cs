using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;

namespace IES
{
    public partial class Form1 : Form
    {
        int startflag = 0;
        int flag_sensor;
        string RxString1;                           //declare values to be used in program
        string RxString2;
        string t;
        string temp = "30";

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.PortName = "COM6";                      //do this when button 1 is clicked (serialStart)
            serialPort1.BaudRate = 19200;
            serialPort1.Open();                                 //start receiving data serially from port 1 (COM6) @ 19,200 bauds/s
            if (serialPort1.IsOpen)
            {
                // startSerial.Enabled = false;
                // serialStop.Enabled = true;
                textBox1.ReadOnly = false;                      //allow the text in textbox 1 and 2 to be changed or removed
                textBox2.ReadOnly = false;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();                                //do this when button 2 is clicked (serialStop)
            //  startSerial.Enabled = true;
            //  serialStop.Enabled = false;
            textBox1.ReadOnly = true;                           //data in textbox 1 and 2 is not alterable
            textBox2.ReadOnly = true;
        }

        private void button3_Click(object sender, EventArgs e)      //button 3 = Read sensor 1 data from ThingSpeak
        {
            WebClient client = new WebClient();
            label2.Text = client.DownloadString("http://api.thingspeak.com/channels/1563689/field/field1/last.text");
        }
        private void button4_Click(object sender, EventArgs e)      //button 4 = Read sensor 2 data from ThingSpeak
        {
            WebClient client = new WebClient();                     
            label3.Text = client.DownloadString("http://api.thingspeak.com/channels/1563689/field/field2/last.text");
        }

        private void label1_Click(object sender, EventArgs e)       //label 1 = Current Data 
        {
            textBox1.AppendText(RxString1);                         //copy received sensor 1 data into textbox 1
            textBox2.AppendText(RxString2);                         //copy received sensor 2 data into textbox 2
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)        //generate internal timer for Form with interval of 10000
        {
            if (!string.Equals(textBox1.Text, ""))                  //if textbox is not empty
            {
                if (serialPort1.IsOpen) serialPort1.Close();        //stop transmitting data
                try                                                 //do this expecting to get some exceptions back
                {
                    /*  if (RxString[0] == 'B')
                      {
                          flag_sensor = 10;

                      }*/
                    const string WRITEKEY = "N8DQTWVVSJCQGAWH";
                    string strUpdateBase = "http://api.thingspeak.com/update";      
                    string strUpdateURI = strUpdateBase + "?api_key=" + WRITEKEY;  //strUpdateURI has web address and channel WRITEKEY of ThingSpeak channel
                    string strField1 = textBox1.Text;                              //strField1 has sensor 1 data value
                    string strField2 = textBox2.Text;                              //strField2 has sensor 2 data value

                    HttpWebRequest ThingsSpeakReq;
                    HttpWebResponse ThingsSpeakResp;

                    strUpdateURI += "&field1=" + strField1 + "&field2=" + strField2;        //update URI before making request to ThingSpeak
                                                                                            //so it has the data to send to each Sensor Field

                    //flag_sensor++;
                    ThingsSpeakReq = (HttpWebRequest)WebRequest.Create(strUpdateURI);       //make web request to ThingSpeak
                    ThingsSpeakResp = (HttpWebResponse)ThingsSpeakReq.GetResponse();        //get response
                    ThingsSpeakResp.Close();
                    if (!(string.Equals(ThingsSpeakResp.StatusDescription, "OK")))          //check whether ThingSpeak threw exception back
                    {
                        Exception exData = new Exception(ThingsSpeakResp.StatusDescription);
                        throw exData;
                    }
                }
                catch (Exception ex)
                {

                }
                textBox1.Text = "";                                             //clear old data from textbox 1 and 2
                textBox2.Text = "";
                serialPort1.Open();                                             //start transmitting data again
            }
        }

        private void SerialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            t = serialPort1.ReadExisting();                                     //when serial port 1 receives data, do this
            RxString1 = t.Split(' ')[0];                                        //up until the first space characater, read data into RxString1
            RxString2 = t.Split(' ')[1];                                        //read everything after first space character into RxString2
            this.Invoke(new EventHandler(label1_Click));
        }
        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}

