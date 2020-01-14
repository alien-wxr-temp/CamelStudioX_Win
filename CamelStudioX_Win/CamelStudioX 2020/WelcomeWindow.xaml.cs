using MahApps.Metro.Controls;
using System.Windows;
using System.Windows.Forms;
using Microsoft.WindowsAPICodePack.Dialogs;

namespace CamelStudioX_2020
{
    /// <summary>
    /// Interaction logic for WelcomeWindow.xaml
    /// </summary>
    public partial class WelcomeWindow : MetroWindow
    {
        public WelcomeWindow()
        {
            InitializeComponent();
        }


        private void closeButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void newProject_Click(object sender, RoutedEventArgs e)
        {
            this.tabControl1.SelectedIndex = 1;
        }

        private void backButton_Click(object sender, RoutedEventArgs e)
        {
            this.pName.Text = "";
            this.pLocation.Text = "";
            this.tabControl1.SelectedIndex = 0;
        }

        private void createButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = new MainWindow();
            mainWindow.Show();
            this.Close();
        }

        private void openButton_Click(object sender, RoutedEventArgs e)
        {   
            CommonOpenFileDialog dialog = new CommonOpenFileDialog();
            dialog.IsFolderPicker = true;//设置为选择文件夹
            if(dialog.ShowDialog() == CommonFileDialogResult.Ok)
            {
                this.pLocation.Text = dialog.FileName;
            }
        }
    }
}
