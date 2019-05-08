import app from './app'
import app_main from './app.main'
import login from './views/login'
import main from './views/main'
import main_computer from './views/main_computer'
import main_console from './views/main_console'
import controller_error from '@/w/controller/error'

export default {
    router : {
        path: '/client_apk',
        component: app,
        children:[
          { path: '/', component: controller_error.error_404 },
          { path: 'login', component: login, meta: { title: "登录" } },
          { 
            path: 'main', 
            component: app_main,
            children:[
              { path: '/', component: main, meta: { title: "控制中心" } },
              { path: 'computer', component: main_computer, meta: { title: "电脑管理" } },
              { path: 'console', component: main_console, meta: { title: "控制台" }}
            ]
          },
          controller_error.router
        ]
    }
}