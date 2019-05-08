<?php
/* 定义应用目录 */
define('APP_PATH', __DIR__ . '/../application/');
// 默认用户session
define('Define_SESSION_PATH', __DIR__.'/../runtime/session');
// 后台用户session
define('Management_SESSION_PATH', __DIR__.'/../runtime/session_management');
// 默认函数位置
define('Define_Weteoes_PATH', APP_PATH."Weteoes/");
// 后台函数位置
define('operating_Management_path', Define_Weteoes_PATH."management/");

/* 加载框架引导文件 */
require __DIR__ . '/../thinkphp/start.php';