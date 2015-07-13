using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using Microsoft.Win32;
using System.Drawing;
using System.IO;
using System.Drawing.Imaging;

namespace Utiliterrific
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            bool? result = openFileDialog.ShowDialog();

            if(result.HasValue && result.Value)
            {
                BitmapImage img = new BitmapImage();
                img.BeginInit();
                img.UriSource = new Uri(openFileDialog.FileName);
                img.EndInit();
                displayedImage.Width = img.Width;
                displayedImage.Height = img.Height;
                displayedImage.Source = img;
            }
        }

        private void displayedImage_MouseWheel(object sender, MouseWheelEventArgs e)
        {
            displayedImage.Width += e.Delta;
            displayedImage.Height += e.Delta;
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            bool? result = openFileDialog.ShowDialog();

            if(result.HasValue && result.Value)
            {
                Bitmap img1 = BitmapImage2Bitmap(displayedImage.Source as BitmapImage);
                BitmapImage temp = new BitmapImage();
                temp.BeginInit();
                temp.UriSource = new Uri(openFileDialog.FileName);
                temp.EndInit();

                Bitmap img2 = BitmapImage2Bitmap(temp);

                Bitmap final = new Bitmap((int)(img1.Width + img2.Width), (int)Math.Max(img1.Height, img2.Height));
                using(Graphics g = Graphics.FromImage(final))
                {
                    g.DrawImage(img1, 0, 0);
                    g.DrawImage(img2, img1.Width,0);
                }
                displayedImage.Width = final.Width;
                displayedImage.Height = final.Height;
                displayedImage.Source = BitmapToBitmapImage(final);
            }
        }
        private Bitmap BitmapImage2Bitmap(BitmapImage bitmapImage)
        {
            // BitmapImage bitmapImage = new BitmapImage(new Uri("../Images/test.png", UriKind.Relative));

            using (MemoryStream outStream = new MemoryStream())
            {
                BitmapEncoder enc = new BmpBitmapEncoder();
                enc.Frames.Add(BitmapFrame.Create(bitmapImage));
                enc.Save(outStream);
                System.Drawing.Bitmap bitmap = new System.Drawing.Bitmap(outStream);

                return new Bitmap(bitmap);
            }
        }

        private BitmapImage BitmapToBitmapImage(Bitmap bitmap)
        {
            using (var memory = new MemoryStream())
            {
                bitmap.Save(memory, ImageFormat.Png);
                memory.Position = 0;

                var bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();

                return bitmapImage;
            }
        }

        bool rectangleGrabbed;
        System.Windows.Point mouseDownPos;
        private void displayedImage_MouseDown(object sender, MouseButtonEventArgs e)
        {
            rectangleGrabbed = true;
            mouseDownPos = e.GetPosition(displayedImage);
            Canvas.SetLeft(selectionBox, mouseDownPos.X);
            Canvas.SetTop(selectionBox, mouseDownPos.Y);
            selectionBox.Width = 0;
            selectionBox.Height = 0;
        }

        private void displayedImage_MouseUp(object sender, MouseButtonEventArgs e)
        {
            rectangleGrabbed = false;
        }

        private void displayedImage_MouseMove(object sender, MouseEventArgs e)
        {
            if(rectangleGrabbed)
            {
                System.Windows.Point mousePos = e.GetPosition(displayedImage);
                if (mouseDownPos.X < mousePos.X)
                {
                    Canvas.SetLeft(selectionBox, mouseDownPos.X);
                    selectionBox.Width = mousePos.X - mouseDownPos.X;
                }
                else
                {
                    Canvas.SetLeft(selectionBox, mousePos.X);
                    selectionBox.Width = mouseDownPos.X - mousePos.X;
                }

                if (mouseDownPos.Y < mousePos.Y)
                {
                    Canvas.SetTop(selectionBox, mouseDownPos.Y);
                    selectionBox.Height = mousePos.Y - mouseDownPos.Y;
                }
                else
                {
                    Canvas.SetTop(selectionBox, mousePos.Y);
                    selectionBox.Height = mouseDownPos.Y - mousePos.Y;
                }
            }
        }
    }
}
