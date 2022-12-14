#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#include <microsoft.ui.xaml.window.h>
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.
struct winrt::Windows::UI::Color myCol = winrt::Microsoft::UI::Colors::Green();
namespace winrt::PaintSave_Final::implementation
{
    MainWindow::MainWindow()
    {
        InitializeComponent();
        flag = false;
        px = 100;
        py = 100;
        mySize = 16;

        auto windowNative{ this->try_as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);
        SetWindowPos(hWnd, NULL, 200, 200, 1070, 690, NULL);
        this->Title(L"Andong Nation University");
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

}


void winrt::PaintSave_Final::implementation::MainWindow::Button2_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (IsChecked2)
    {
        IsChecked2 = FALSE;
        Button2().Label(L"Disable");

        colorPanel().Visibility(Visibility::Collapsed);
    }
    else
    {
        IsChecked2 = TRUE;
        Button2().Label(L"Enable");

        colorPanel().Visibility(Visibility::Visible);
    }
}


void winrt::PaintSave_Final::implementation::MainWindow::myClear_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    vx.clear();
    vy.clear();
    col.clear();
    size.clear();
    flag = false;
}


void winrt::PaintSave_Final::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    int n = vx.size();
    if (n <= 2) return;

    for (int i = 1; i < n; i++) {
        if (vx[i] == 0.0 && vy[i] == 0.0) {
            i++; continue;
        }
        args.DrawingSession().DrawLine(vx[i - 1], vy[i - 1], vx[i], vy[i], col[i], size[i]);
        args.DrawingSession().FillCircle(vx[i - 1], vy[i - 1], size[i] / 2, col[i]);
        args.DrawingSession().FillCircle(vx[i], vy[i], size[i] / 2, col[i]);
    }
    canvas.Invalidate();
}


void winrt::PaintSave_Final::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    px = e.GetCurrentPoint(canvas).Position().X;
    py = e.GetCurrentPoint(canvas).Position().Y;
    if (flag) {
        vx.push_back(px);
        vy.push_back(py);
        col.push_back(myCol);
        size.push_back(mySize);
        canvas.Invalidate();
    }
}


void winrt::PaintSave_Final::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = false;
    px = py = 0.0;
    vx.push_back(px);
    vy.push_back(py);
    col.push_back(myCol);
    size.push_back(mySize);
}


void winrt::PaintSave_Final::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = true;
}


void winrt::PaintSave_Final::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    myCol = args.NewColor();
}




void winrt::PaintSave_Final::implementation::MainWindow::MenuFlyoutItem_Click_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //저장
    FILE* fp;
    fopen_s(&fp, "C:\\Users\\VisualS2\\Desktop\\ANU\\my.txt", "w");

    if (fp)
    {
        int n = vx.size();
        for (int i = 0; i < n; i++)
        {
            fprintf(fp, "%f %f %d %d %d %d %f ", vx[i], vy[i], col[i].R, col[i].G, col[i].B, col[i].A, size[i]);
        }
        fclose(fp);
    }
}


void winrt::PaintSave_Final::implementation::MainWindow::MenuFlyoutItem_Click_2(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    //불러오기
    FILE* fp;
    fopen_s(&fp, "C:\\Users\\VisualS2\\Desktop\\ANU\\my.txt", "r");

    if (fp)
    {
        vx.clear(); vy.clear(); size.clear(); col.clear();

        float x, y, s;
        int r, g, b, a;
        while (EOF != fscanf_s(fp, "%f %f %d %d %d %d %f", &x, &y, &r, &g, &b, &a, &s))
        {
            vx.push_back(x);
            vy.push_back(y);
            Windows::UI::Color tCol;
            tCol.R = r; tCol.G = g; tCol.B = b; tCol.A = a;
            col.push_back(tCol);
            size.push_back(s);
        }
        fclose(fp);
        CanvasControl_PointerReleased(NULL, NULL);
    }
}


void winrt::PaintSave_Final::implementation::MainWindow::MenuFlyoutItem_Click_3(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    this->Close();
}


void winrt::PaintSave_Final::implementation::MainWindow::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    mySize = e.NewValue();
}
