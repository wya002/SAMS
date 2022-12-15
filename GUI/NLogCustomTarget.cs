using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NLog;
using NLog.Targets;

namespace GUI
{
    [Target("WpfTarget")]
    public class NLogCustomTarget : TargetWithLayout
    {
        // 로그 이벤트를 전파할 델리게이트 
        public delegate void LogEventDelegate(string message);
        public LogEventDelegate LogEventListener;

        // 생성자
        public NLogCustomTarget()
        {
        }

        // 로그 이벤트 기록
        protected override void Write(LogEventInfo logEvent)
        {
            // 레이아웃 형식에 맞게 로그 포맷
            string logMessage = this.Layout.Render(logEvent);
            // 로그이벤트를 수신할 델리게이트가 하나이상 지정된 경우에만 함수 호출
            LogEventListener?.Invoke(logMessage);
        }
    }
}
