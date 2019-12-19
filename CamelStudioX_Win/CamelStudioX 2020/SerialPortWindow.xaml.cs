using MahApps.Metro.Controls;
using System;
using System.IO.Ports;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace CamelStudioX_2020
{
    /// <summary>
    /// Interaction logic for SerialPortWindow.xaml
    /// </summary>
    public partial class SerialPortWindow : MetroWindow
    {
        public SerialPortWindow()
        {
            InitializeComponent();

            string[] ports = SerialPort.GetPortNames();//获取当前计算机的串行端口名的数组。
            for (int index = 0; index < ports.Length; index++)
            {
                cb_SerialPortNumber.Items.Add(ports[index]);//添加item
                cb_SerialPortNumber.SelectedIndex = index; //设置显示的item索引
            }
            bt_send.IsEnabled = false;
            bt_stopSend.IsEnabled = false;
        }

        public SerialPort _serialPort = new SerialPort();

        public void initialize()//初始化
        {
            //关闭串口时回抛异常
            try
            {
                _serialPort.PortName = cb_SerialPortNumber.SelectedItem.ToString();//串口号
                ComboBoxItem seletedItem = (ComboBoxItem)this.cb_BaudRate.SelectedItem;
                _serialPort.BaudRate = Convert.ToInt32(seletedItem.Content.ToString());//波特率
                _serialPort.DataBits = 8;//数据位
                _serialPort.StopBits = StopBits.One;//停止位
                _serialPort.Parity = Parity.None;//校验位
            }
            catch
            {

            }

        }
        private void bt_ClearSendData_Click(object sender, RoutedEventArgs e)//清空发送区域
        {
            tb_SendData.Text = "";
        }

        private void ClearReceiveData_Click(object sender, RoutedEventArgs e)//清空接受数据
        {
            tb_receiveData.Text = "";
        }

        private void bt_SerialSwitch_Click(object sender, RoutedEventArgs e)//串口开关
        {
            initialize();//初始化
            string strContent = this.bt_SerialSwitch.Content.ToString();
            if (strContent == "打开串口")
            {
                try
                {
                    _serialPort.Open();
                    _serialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);//添加数据接收事件
                    //_serialPort.DataReceived += DataReceivedHandler;
                    bt_SerialSwitch.Content = "关闭串口";
                    tb_switchStatus.Text = "串口为打开状态";
                    bt_send.IsEnabled = true;
                    bt_stopSend.IsEnabled = true;
                    e_status.Fill = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FF0000"));
                }
                catch { }
            }
            else
            {
                try
                {
                    _serialPort.DataReceived -= DataReceivedHandler;
                    _serialPort.Close();
                    bt_SerialSwitch.Content = "打开串口";
                    tb_switchStatus.Text = "串口为关闭状态";
                    e_status.Fill = new SolidColorBrush((Color)ColorConverter.ConvertFromString("#000000"));
                    bt_send.IsEnabled = false;
                    bt_stopSend.IsEnabled = false;
                }
                catch
                {

                }
            }
        }
        public void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)//读取下位机的数据，显示在textBlock中
        {
            int len = this._serialPort.BytesToRead;
            byte[] buffer = new byte[len];
            this._serialPort.Read(buffer, 0, len);
            string strData = BitConverter.ToString(buffer, 0, len);
            Dispatcher.Invoke(() =>
            {
                this.tb_receiveData.Text += strData;
                this.tb_receiveData.Text += "-";
            });
        }

        private void bt_send_Click(object sender, RoutedEventArgs e)//发送按钮
        {
            string SendData = tb_SendData.Text;
            byte[] Data = new byte[20];
            for (int i = 0; i < SendData.Length / 2; i++)
            {
                //每次取两位字符组成一个16进制
                Data[i] = Convert.ToByte(tb_SendData.Text.Substring(i * 2, 2), 16);
            }
            this._serialPort.Write(Data, 0, Data.Length);
        }
        private void bt_stopSend_Click(object sender, RoutedEventArgs e)//停止接收数据
        {
            string strContent = this.bt_stopSend.Content.ToString();
            if (strContent == "停止接收")
            {
                byte[] data = { 0x99 };
                _serialPort.DataReceived -= DataReceivedHandler;
                this._serialPort.Write(data, 0, data.Length);
                bt_stopSend.Content = "继续接收";
            }
            else
            {
                byte[] data = { 0x66 };
                this._serialPort.Write(data, 0, data.Length);
                _serialPort.DataReceived += DataReceivedHandler;
                bt_stopSend.Content = "停止接收";
            }
        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            string strContent = this.bt_SerialSwitch.Content.ToString();
            if (strContent == "关闭串口")
            {
                _serialPort.Close();
            }
        }
    }
}
