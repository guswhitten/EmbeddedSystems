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
        string RxString1;
        string RxString2;
        string t;
        string temp = "30";

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            serialPort1.PortName = "COM6";
            serialPort1.BaudRate = 19200;
            serialPort1.Open();
            if (serialPort1.IsOpen)
            {
                // startSerial.Enabled = false;
                // serialStop.Enabled = true;
                textBox1.ReadOnly = false;
                textBox2.ReadOnly = false;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            //  startSerial.Enabled = true;
            //  serialStop.Enabled = false;
            textBox1.ReadOnly = true;
            textBox2.ReadOnly = true;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            WebClient client = new WebClient();
            label2.Text = client.DownloadString("http://api.thingspeak.com/channels/1563689/field/field1/last.text");
        }
        private void button4_Click(object sender, EventArgs e)
        {
            WebClient client = new WebClient();
            label3.Text = client.DownloadString("http://api.thingspeak.com/channels/1563689/field/field2/last.text");
        }

        private void label1_Click(object sender, EventArgs e)
        {
            textBox1.AppendText(RxString1);
            textBox2.AppendText(RxString2);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!string.Equals(textBox1.Text, ""))
            {
                if (serialPort1.IsOpen) serialPort1.Close();
                try
                {
                    /*  if (RxString[0] == 'B')
                      {
                          flag_sensor = 10;

                      }*/
                    const string WRITEKEY = "N8DQTWVVSJCQGAWH";
                    string strUpdateBase = "http://api.thingspeak.com/update";
                    string strUpdateURI = strUpdateBase + "?api_key=" + WRITEKEY;
                    string strField1 = textBox1.Text;
                    string strField2 = textBox2.Text;

                    HttpWebRequest ThingsSpeakReq;
                    HttpWebResponse ThingsSpeakResp;

                    strUpdateURI += "&field1=" + strField1 + "&field2=" + strField2;

                    //flag_sensor++;
                    ThingsSpeakReq = (HttpWebRequest)WebRequest.Create(strUpdateURI);
                    ThingsSpeakResp = (HttpWebResponse)ThingsSpeakReq.GetResponse();
                    ThingsSpeakResp.Close();
                    if (!(string.Equals(ThingsSpeakResp.StatusDescription, "OK")))
                    {
                        Exception exData = new Exception(ThingsSpeakResp.StatusDescription);
                        throw exData;
                    }
                }
                catch (Exception ex)
                {

                }
                textBox1.Text = "";
                textBox2.Text = "";
                serialPort1.Open();
            }
        }

        private void SerialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            t = serialPort1.ReadExisting();
            RxString1 = t.Split(' ')[0];
            RxString2 = t.Split(' ')[1];
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

