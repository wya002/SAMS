using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;

namespace GUI
{
    class MyVisualHost : FrameworkElement
    {
        private VisualCollection _children;

        public MyVisualHost()
        {
            _children = new VisualCollection(this);

            // Add the event handler for MouseLeftButtonUp.
            this.MouseLeftButtonUp += new System.Windows.Input.MouseButtonEventHandler(MyVisualHost_MouseLeftButtonUp);

        }

        public void Drawrect(Point pt)
        {
            //_children.Clear();
            if(_children.Count == 3)
            {
                _children.Clear();
            }
            _children.Add(CreateDrawingVisualRectangle(pt));
            //_children.Add(CreateDrawingVisualText());
            //_children.Add(CreateDrawingVisualEllipses());
        }

        public void Drawrect2(Point pt)
        {
            //_children.Clear();
            if (_children.Count == 3)
            {
                _children.Clear();
            }
            _children.Add(CreateDrawingVisualRectangle2(pt));
            //_children.Add(CreateDrawingVisualText());
            //_children.Add(CreateDrawingVisualEllipses());
        }

        public void Drawrect3(Point pt)
        {
            //_children.Clear();
            if (_children.Count == 3)
            {
                _children.Clear();
            }
            _children.Add(CreateDrawingVisualRectangle3(pt));
            //_children.Add(CreateDrawingVisualText());
            //_children.Add(CreateDrawingVisualEllipses());
        }

        private DrawingVisual CreateDrawingVisualRectangle(Point pp)
        {
            DrawingVisual drawingVisual = new DrawingVisual();

            // Retrieve the DrawingContext in order to create new drawing content.
            DrawingContext drawingContext = drawingVisual.RenderOpen();

            // Create a rectangle and draw it in the DrawingContext.
            //Rect rect = new Rect(new System.Windows.Point(160, 100), new System.Windows.Size(320, 80));
            Rect rect = new Rect(pp, new System.Windows.Size(5, 5));
            drawingContext.DrawRectangle(System.Windows.Media.Brushes.Red, (System.Windows.Media.Pen)null, rect);

            // Persist the drawing content.
            drawingContext.Close();

            return drawingVisual;
        }
        private DrawingVisual CreateDrawingVisualRectangle2(Point pp)
        {
            DrawingVisual drawingVisual = new DrawingVisual();

            // Retrieve the DrawingContext in order to create new drawing content.
            DrawingContext drawingContext = drawingVisual.RenderOpen();

            // Create a rectangle and draw it in the DrawingContext.
            //Rect rect = new Rect(new System.Windows.Point(160, 100), new System.Windows.Size(320, 80));
            Rect rect = new Rect(pp, new System.Windows.Size(5, 5));
            drawingContext.DrawRectangle(System.Windows.Media.Brushes.Yellow, (System.Windows.Media.Pen)null, rect);

            // Persist the drawing content.
            drawingContext.Close();

            return drawingVisual;
        }
        private DrawingVisual CreateDrawingVisualRectangle3(Point pp)
        {
            DrawingVisual drawingVisual = new DrawingVisual();

            // Retrieve the DrawingContext in order to create new drawing content.
            DrawingContext drawingContext = drawingVisual.RenderOpen();

            // Create a rectangle and draw it in the DrawingContext.
            //Rect rect = new Rect(new System.Windows.Point(160, 100), new System.Windows.Size(320, 80));
            Rect rect = new Rect(pp, new System.Windows.Size(5, 5));
            drawingContext.DrawRectangle(System.Windows.Media.Brushes.Black, (System.Windows.Media.Pen)null, rect);

            // Persist the drawing content.
            drawingContext.Close();

            return drawingVisual;
        }

        protected override int VisualChildrenCount
        {
            get { return _children.Count; }
        }

        // Provide a required override for the GetVisualChild method.
        protected override Visual GetVisualChild(int index)
        {
            if (index < 0 || index >= _children.Count)
            {
                throw new ArgumentOutOfRangeException();
            }

            return _children[index];
        }

        void MyVisualHost_MouseLeftButtonUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            // Retreive the coordinates of the mouse button event.
            System.Windows.Point pt = e.GetPosition((UIElement)sender);

            Point newpt = new Point(pt.X + 20, pt.Y + 20);
            Drawrect(newpt);

            // Initiate the hit test by setting up a hit test result callback method.
            VisualTreeHelper.HitTest(this, null, new HitTestResultCallback(myCallback), new PointHitTestParameters(pt));
        }

        // If a child visual object is hit, toggle its opacity to visually indicate a hit.
        public HitTestResultBehavior myCallback(HitTestResult result)
        {
            if (result.VisualHit.GetType() == typeof(DrawingVisual))
            {
                if (((DrawingVisual)result.VisualHit).Opacity == 1.0)
                {
                    ((DrawingVisual)result.VisualHit).Opacity = 0.4;
                }
                else
                {
                    ((DrawingVisual)result.VisualHit).Opacity = 1.0;
                }
            }

            // Stop the hit test enumeration of objects in the visual tree.
            return HitTestResultBehavior.Stop;
        }
    }
}
