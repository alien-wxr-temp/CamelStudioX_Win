using MahApps.Metro.Controls;
using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.IO;
using System.Windows;

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
            //create the project
            string sourceDir = @"example\M2\Hello";
            string targetDir = pLocation.Text + pName.Text;

            try
            {
                // Determine whether the directory exists.
                if (!Directory.Exists(targetDir))
                {
                    // Create the directory it does not exist.
                    Directory.CreateDirectory(targetDir);
                }

                // create .c & .icmsx file
                File.Copy(Path.Combine(sourceDir, "Hello.c"), Path.Combine(targetDir, pName.Text + ".c"));
                File.Copy(Path.Combine(sourceDir, "Hello.icmsx"), Path.Combine(targetDir, pName.Text + ".icmsx"));
            }
            // Catch exception if the file was already copied.
            catch (IOException copyError)
            {
                Console.WriteLine(copyError.Message);
            }

            //launch the mainWindow
            MainWindow mainWindow = new MainWindow(pName.Text, pLocation.Text);
            mainWindow.Show();
            this.Close();
        }

        private void openButton_Click(object sender, RoutedEventArgs e)
        {
            CommonOpenFileDialog dialog = new CommonOpenFileDialog();
            dialog.IsFolderPicker = true;
            if (dialog.ShowDialog() == CommonFileDialogResult.Ok)
            {
                this.pLocation.Text = dialog.FileName;
            }
        }

        private void openProject_Click(object sender, RoutedEventArgs e)
        {
            //launch the mainWindow
            MainWindow mainWindow = new MainWindow(pName.Text, pLocation.Text);
            mainWindow.Show();
            this.Close();
        }

        private void openExample_Click(object sender, RoutedEventArgs e)
        {
            //launch the mainWindow
            MainWindow mainWindow = new MainWindow(pName.Text, pLocation.Text);
            mainWindow.Show();
            this.Close();
        }
    }
}
