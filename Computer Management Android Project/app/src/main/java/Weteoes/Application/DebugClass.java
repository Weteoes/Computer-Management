package Weteoes.Application;

import android.content.Context;
import android.content.pm.ApplicationInfo;

public class DebugClass {

    // 判断当前应用是否是debug状态
    public static boolean isInDebug(Context context) {
        try {
            ApplicationInfo info = context.getApplicationInfo();
            return (info.flags & ApplicationInfo.FLAG_DEBUGGABLE) != 0;
        } catch (Exception e) {
            return false;
        }
    }

}
