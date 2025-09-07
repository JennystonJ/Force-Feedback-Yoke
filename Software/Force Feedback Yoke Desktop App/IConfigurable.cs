using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Force_Feedback_Yoke_Desktop_App
{
    public interface IConfigurable<TConfig>
    {
        public void ApplyConfig(TConfig config);
        public TConfig ExportConfig();
    }
}
