using System.Windows.Input;

namespace CamelStudioX_2020
{
    public class CustomCommands
    {
        public static RoutedUICommand OpenFile = new RoutedUICommand(
            "OpenFile",//text
            "OpenFile",//name
            typeof(CustomCommands),//owner type
            new InputGestureCollection()//gesture collection
            {
                new KeyGesture(Key.O, ModifierKeys.Control)
            }
        );

        public static RoutedUICommand FullScreen = new RoutedUICommand(
            "FullScreen",
            "FullScreen",
            typeof(CustomCommands),
            new InputGestureCollection()
            {
                new KeyGesture(Key.Enter,ModifierKeys.Shift|ModifierKeys.Control,"Ctrl+Shift+Enter")
            }
        );
    }
}
